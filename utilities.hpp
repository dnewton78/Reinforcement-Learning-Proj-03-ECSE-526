#ifndef UTILITIES_H
#define UTILITIES_H

#include <ale_interface.hpp>

using namespace std;

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
  void extractCoord(const ALEScreen& screen, vector<Coord>& vOut);

private:
  // Ignore the top and bottom part of the screen as they are not relavant
  // Only used for extractCoord
  static const int SCREEN_START_HEIGHT = 3;
  static const int SCREEN_END_HEIGHT = 170;

  static const int IDX_PACMAN = 0;
  static const int NUMOFOBJECTS = 5;
  // We only care about the velocity of the ghost because we our action determines
  // the pacman's velocity
  static const int NUMCOORDFEATURE = 9;

  // Pixel color of each objects
  static unsigned int PXLS[NUMOFOBJECTS];

  ScreenObject so[NUMOFOBJECTS];
};


#endif