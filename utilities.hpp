#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <ale_interface.hpp>

using namespace std;

class Background
{
public:

  static const int WIDTH = 160;
  static const int HEIGHT = 210;
  
  Background();
  int pixelAt(int i, int j);
  void print();

private:
  static const string PATH_BACKGROUND;
  int background[HEIGHT][WIDTH];
};

class ScreenObject
{
public:
  ScreenObject();
  void accumulate(int i, int j);
  void takeAverage();
  bool doesCoordMatch(int i , int j);
  void getAvgValues(int& rI, int& rJ);

private:
  int m_sum_i;
  int m_sum_j;
  int m_avg_i;
  int m_avg_j;
  int m_numOfPoints;
  bool m_isPresent;
  bool m_isAvgCalculated;
};

class Coord
{
public:
  Coord();
  void update(ScreenObject& so);

  int i;
  int j;
};

class Feature
{
public:
  Feature();
  void extractCoord(const ALEScreen& screen, Coord coords[]);
  void extractFeature(const ALEScreen& screen, vector<int>& vOut);

private:
  // Ignore the top and bottom part of the screen as they are not relavant
  // Only used for extractCoord
  static const int SCREEN_START_HEIGHT = 3;
  static const int SCREEN_END_HEIGHT = 170;

  static const int IDX_PACMAN = 0;
  static const int NUMOFOBJECTS = 5;

  // Pixel color of each objects
  static const unsigned int PXL_PACMAN = 42;
  static const unsigned int PXL_GHOST_1 = 70;
  static const unsigned int PXL_GHOST_2 = 38;
  static const unsigned int PXL_GHOST_3 = 184;
  static const unsigned int PXL_GHOST_4 = 88;

  static const int TILE_WIDTH = 16;
  static const int TILE_HEIGHT = 21;
  static const int NUMOFCOLORS = 8;
  static const int BIT_SHIFT = 4;
  static const int NUMOFBASICFEATURE = TILE_WIDTH * TILE_HEIGHT * NUMOFCOLORS + 1;

  Background m_bg;
};


#endif