#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
// #include <cstdlib>
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
      cout << "[" << i  << "]" << "[" << j  << "]:" << val << " ";
      background[i][j] = stoi(val);
      j++;
    }
    i++;
  }

  // They must have matching dimension!
  assert(i == HEIGHT && j == WIDTH);
  backgroundFile.close();
}

int pixelAt(int x, int y)
{
  return background[x][y];
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
