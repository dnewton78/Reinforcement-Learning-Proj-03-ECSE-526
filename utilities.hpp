#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using namespace std;

class Background
{
public:

  static const int WIDTH = 160;
  static const int HEIGHT = 210;
  
  Background();
  int pixelAt(int x, int y);
  void print();

private:
  static const string PATH_BACKGROUND;
  int background[HEIGHT][WIDTH];
};


#endif