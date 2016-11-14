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
  bool doesCoordMatch(int i , int j);
  void getAvgValues(int& rI, int& rJ);
  void getVelocity(int& rI, int& rJ);

private:
  // Variables for velocity calculation
  int m_last_i;
  int m_last_j;
  int m_cur_i;
  int m_cur_j;
  int m_timeDiff;

  int m_sum_i;
  int m_sum_j;
  int m_numOfPoints;
  bool isPresent;

  // Different types of reset. The first one calls the rest
  void reset_1();
  void reset_2();
  void reset_3();
};

class Coord
{
public:
  Coord();
  void updatePos(ScreenObject& so);
  void updateVelo(ScreenObject& so);
  bool doesCoordMatch(int _i, int _j);

  void print()
  {
    cout << "i:" << i << " j:" << j << endl;
  }

  int i;
  int j;
};

class Feature
{
public:
  Feature();
  void extractCoord(const ALEScreen& screen, vector<Coord*>& vOut);
  void extractFeature(const ALEScreen& screen, vector<int>& vOut);

private:
  // Ignore the top and bottom part of the screen as they are not relavant
  // Only used for extractCoord
  static const int SCREEN_START_HEIGHT = 3;
  static const int SCREEN_END_HEIGHT = 170;

  static const int IDX_PACMAN = 0;
  static const int NUMOFOBJECTS = 5;
  static const int NUMCOORDFEATURE = 9;

  // Pixel color of each objects
  static unsigned int PXLS[NUMOFOBJECTS];

  static const int TILE_WIDTH = 16;
  static const int TILE_HEIGHT = 21;
  static const int NUMOFCOLORS = 8;
  static const int BIT_SHIFT = 4;
  static const int NUMOFBASICFEATURE = TILE_WIDTH * TILE_HEIGHT * NUMOFCOLORS + 1;

  ScreenObject so[5];
  Background m_bg;
};


#endif