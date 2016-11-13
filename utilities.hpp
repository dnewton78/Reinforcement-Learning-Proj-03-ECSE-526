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

class Feature
{
public:
  Feature();
  void extractFeature(const ALEScreen& screen, vector<int>& vOut);

private:
  static const int TILE_WIDTH = 16;
  static const int TILE_HEIGHT = 21;
  static const int NUMOFCOLORS = 8;
  static const int BIT_SHIFT = 4;
  static const int NUMOFBASICFEATURE = TILE_WIDTH * TILE_HEIGHT * NUMOFCOLORS + 1;

  Background m_bg;
};


#endif