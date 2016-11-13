#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdio> //

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


ScreenObject::ScreenObject()
{
  m_sum_i = 0;
  m_sum_j = 0;
  m_avg_i = 0;
  m_avg_j = 0;
  m_numOfPoints = 0;
  m_isPresent = false;
  m_isAvgCalculated = false;
}

void ScreenObject::accumulate(int i, int j)
{
  m_isPresent = true;
  m_sum_i += i;
  m_sum_j += j;
  m_numOfPoints++;
}

bool ScreenObject::doesCoordMatch(int i , int j)
{
  if (m_isPresent)
  {
    if (! m_isAvgCalculated)
    {
      m_avg_i = m_sum_i / m_numOfPoints;
      m_avg_j = m_sum_j / m_numOfPoints;
      m_isAvgCalculated = true;
    }
    if (m_avg_i == i && m_avg_j == j)
    {
      return true;
    }
  }
  return false;
}

void ScreenObject::getAvgValues(int& rI, int& rJ)
{
  rI = m_avg_i;
  rJ = m_avg_j;
}

Coord::Coord() {}
void Coord::update(ScreenObject& so)
{
  so.getAvgValues(i, j);
}


const int Feature::SCREEN_START_HEIGHT;
const int Feature::SCREEN_END_HEIGHT;

const int Feature::IDX_PACMAN;

const unsigned int Feature::PXL_PACMAN;
const unsigned int Feature::PXL_GHOST_1;
const unsigned int Feature::PXL_GHOST_2;
const unsigned int Feature::PXL_GHOST_3;
const unsigned int Feature::PXL_GHOST_4;

const int Feature::TILE_WIDTH;
const int Feature::TILE_HEIGHT;
const int Feature::NUMOFCOLORS;
const int Feature::BIT_SHIFT;
const int Feature::NUMOFBASICFEATURE;

Feature::Feature() {}

void Feature::extractCoord(const ALEScreen& screen, Coord coords[])
{
  // Uncomment to output the current screen
  // ofstream ofs_ppm;
  // ofstream ofs_ref;

  // char buffer[20];
  // sprintf(buffer, "screen_%d.ppm", fileNum);
  // ofs_ppm.open(buffer);
  // sprintf(buffer, "screen_%d_.ppm", fileNum);
  // ofs_ref.open(buffer);

  // ofs_ppm << "P3\n160 167\n8\n";
  // ofs_ref << "P3\n160 167\n8\n";

  ScreenObject pacman;
  ScreenObject ghost_1;
  ScreenObject ghost_2;
  ScreenObject ghost_3;
  ScreenObject ghost_4;

  for (int i = SCREEN_START_HEIGHT; i < SCREEN_END_HEIGHT; i++)
  {
    for (int j = 0; j < screen.width(); j++)
    {
      unsigned int pxl = screen.get(i,j);
      // unsigned int b_3 = (pxl & 0xE0) >> 5;
      // unsigned int b_2 = (pxl & 0x1C) >> 2;
      // unsigned int b_1 = (pxl & 0x3);

      // if (pxl == PXL_PACMAN || pxl == PXL_GHOST_1 || pxl == PXL_GHOST_2 || pxl == PXL_GHOST_3 || pxl == PXL_GHOST_4)
      // {
        // ofs_ref << b_3 << " " << b_2 << " " << b_1 << " ";
        if (pxl == PXL_PACMAN)
        {
          pacman.accumulate(i, j);
        }
        else if (pxl == PXL_GHOST_1)
        {
          ghost_1.accumulate(i, j);
        }
        else if (pxl == PXL_GHOST_2)
        {
          ghost_2.accumulate(i, j);
        }
        else if (pxl == PXL_GHOST_3)
        {
          ghost_3.accumulate(i, j);
        }
        else if (pxl == PXL_GHOST_4)
        {
          ghost_4.accumulate(i, j);
        }
      // }
      // else
      // {
      //   ofs_ref << 0 << " " << 0 << " " << 0 << " ";
      // }
    }
    // ofs_ref << "\n";
  }

  // for (int i = SCREEN_START_HEIGHT; i < SCREEN_END_HEIGHT; i++)
  // {
  //   for (int j = 0; j < screen.width(); j++)
  //   {
  //     unsigned int pxl = 0;
  //     if (pacman.doesCoordMatch(i, j))
  //     {
  //       pxl = PXL_PACMAN;
  //     }
  //     else if (ghost_1.doesCoordMatch(i, j))
  //     {
  //       pxl = PXL_GHOST_1;
  //     }
  //     else if (ghost_2.doesCoordMatch(i, j))
  //     {
  //       pxl = PXL_GHOST_2;
  //     }
  //     else if (ghost_3.doesCoordMatch(i, j))
  //     {
  //       pxl = PXL_GHOST_3;
  //     }
  //     else if (ghost_4.doesCoordMatch(i, j))
  //     {
  //       pxl = PXL_GHOST_4;
  //     }

  //     if (pxl == 0)
  //     {
  //       ofs_ppm << 0 << " " << 0 << " " << 0 << " ";
  //     }
  //     else
  //     {
  //       unsigned int b_3 = (pxl & 0xE0) >> 5;
  //       unsigned int b_2 = (pxl & 0x1C) >> 2;
  //       unsigned int b_1 = (pxl & 0x3);
  //       ofs_ppm << b_3 << " " << b_2 << " " << b_1 << " ";
  //     }
  //   }
  //   ofs_ppm << "\n";
  // }

  // ofs_ppm.close();
  // ofs_ref.close();

  coords[0].update(pacman);
  coords[1].update(ghost_1);
  coords[2].update(ghost_2);
  coords[3].update(ghost_3);
  coords[4].update(ghost_4);
}

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
