#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include "utilities.hpp"

using namespace std;

const int Background::WIDTH;
const int Background::HEIGHT;
const string Background::PATH_BACKGROUND = "ms_pacman.bg";

Background::Background()
{
  string line;
  char delimiter = ',';

  //Open background file
  ifstream backgroundFile(PATH_BACKGROUND);

  if (! backgroundFile.is_open() )
  {
    throw runtime_error("The background file could not be opened. Please check paths and permissions");
  }

  int i = 0;
  int j = 0;
  string val;
  while( std::getline(backgroundFile, line) )
  {
    stringstream ss(line);
    j = 0;
    while( std::getline(ss, val, delimiter))
    {
      // cout << "[" << i  << "]" << "[" << j  << "]:" << val << " ";
      background[i][j] = stoi(val);
      j++;
    }
    i++;
  }

  // They must have matching dimension!
  assert(i == HEIGHT && j == WIDTH);
  backgroundFile.close();
}

int Background::pixelAt(int i, int j)
{
  return background[i][j];
}

void Background::print()
{
  for (int i = 0; i < HEIGHT; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      cout << background[i][j];
      if (j < WIDTH - 1)
      {
        cout << ",";
      } 
    }
    cout << endl;
  }
}


const int Feature::TILE_WIDTH;
const int Feature::TILE_HEIGHT;
const int Feature::NUMOFCOLORS;
const int Feature::BIT_SHIFT;
const int Feature::NUMOFBASICFEATURE;

Feature::Feature() {}

void Feature::extractFeature(const ALEScreen& screen, vector<int>& vOut)
{
  assert(screen.height() == Background::HEIGHT && screen.width() == Background::WIDTH);

  if (vOut.size() != 0)
  {
    vOut.clear();
  }

  // It's okay to integer division because we choose tile size that is divisible
  int pixelPerTile_row = Background::HEIGHT / TILE_HEIGHT;
  int pixelPerTile_col = Background::WIDTH / TILE_WIDTH;

  int blkIdx = 0;
  // Iterate over the tiles
  for(int i = 0; i < TILE_HEIGHT; i++)
  {
    int firstPositionRow =  i * pixelPerTile_row;
    int lastPositionRow  = (i + 1) * pixelPerTile_row;
    for(int j = 0; j < TILE_WIDTH; j++)
    {
      int firstPositionCol =  j * pixelPerTile_col;
      int lastPositionCol  = (j + 1) * pixelPerTile_col;

      // Iterate the screen pixels that belong to a given tile index
      for(int x = firstPositionRow; x < lastPositionRow; x++)
      {
        for(int y = firstPositionCol; y < lastPositionCol; y++)
        {
          // NTSC format uses 128 colors --> 7 bits
          // According to the paper, it also support SECAM which uses 8 colors --> 3 bits
          // We can find 3 bits in interest by shifting bits to the right by 4
          unsigned char pixel = (screen.get(x, y) >> BIT_SHIFT);
          unsigned char pixel_bg = (m_bg.pixelAt(x, y) >> BIT_SHIFT);

          if (pixel != pixel_bg)
          {
            vOut.push_back(pixel + blkIdx);
          }
        }
      }
      blkIdx += NUMOFCOLORS;
    }
  }

  // Done with basic features. Add pairwise interaction (BASS feature)
  int curStateSize = vOut.size();

  // Now form 2D matrix of pairwise comparision. Row/column have length of 
  // basic feature size. Note that we need to convert matrix index i, j into single 
  // index on the feature.
  for(int i = 0; i < curStateSize; i++)
  {
    for(int j = i + 1; j < curStateSize; j++)
    {
      // vectorization of a matrix index:
      int offset = NUMOFBASICFEATURE * vOut[i] + vOut[j];

      // We only care bout comparision of tiles above the  diagonal because it we don't need
      // 1. Comparision against itself (diagonal)
      // 2. Same comparison but in different order (tile a vs tile b, tile b vs tile a)
      offset = offset - ((vOut[i] + 1) * (vOut[i] + 2)) / 2;
      // Note that we need to offset by the number of basic features so that they are not
      // overwritten.
      vOut.push_back(NUMOFBASICFEATURE + offset);
    }
  }

}
