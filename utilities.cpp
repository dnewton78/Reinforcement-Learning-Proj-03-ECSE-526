#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdio> //

#include "utilities.hpp"

using namespace std;

ScreenObject::ScreenObject()
{
  m_last_i = 0;
  m_last_j = 0;
  m_cur_i = 0;
  m_cur_j = 0;
  reset_1();
}

void ScreenObject::accumulate(int i, int j)
{
  isPresent = true;
  m_sum_i += i;
  m_sum_j += j;
  m_numOfPoints++;
}

void ScreenObject::getAvgValues(int& rI, int& rJ)
{
  if (isPresent)
  {
    m_last_i = m_cur_i;
    m_last_j = m_cur_j;

    m_cur_i = m_sum_i / m_numOfPoints;
    m_cur_j = m_sum_j / m_numOfPoints;

    rI = m_cur_i;
    rJ = m_cur_j;
    reset_2();
  }
}

void ScreenObject::getVelocity(int& rI, int& rJ)
{
  if (isPresent)
  {
    rI = (m_cur_i - m_last_i) / m_timeDiff;
    rJ = (m_cur_j - m_last_j) / m_timeDiff;
    reset_3();
  }
  else
  {
    m_timeDiff++;
  }

}

void ScreenObject::reset_1()
{
  reset_2();
  reset_3();
}

void ScreenObject::reset_2()
{
  m_sum_i = 0;
  m_sum_j = 0;
  m_numOfPoints = 0;
}

void ScreenObject::reset_3()
{
  m_timeDiff = 1;
  isPresent = false;
}



Coord::Coord()
{
  i = 0;
  j = 0;
}

void Coord::updatePos(ScreenObject& so)
{
  so.getAvgValues(i, j);
}

void Coord::updateVelo(ScreenObject& so)
{
  so.getVelocity(i, j);
}

bool Coord::doesCoordMatch(int _i , int _j)
{
  if (i == _i && j == _j)
  {
    return true;
  }
  return false;
}


const int Feature::SCREEN_START_HEIGHT;
const int Feature::SCREEN_END_HEIGHT;

const int Feature::IDX_PACMAN;
const int Feature::NUMOFOBJECTS;
const int Feature::NUMCOORDFEATURE;


unsigned int Feature::PXLS[5] = {42, 38, 70, 88, 184};

Feature::Feature() {}

void Feature::extractCoord(const ALEScreen& screen, vector<Coord>& vOut)
{  
  // Uncomment to output the current screen
  // char buffer[20];
  // ofstream ofs_ref;
  // sprintf(buffer, "screen_%d_.ppm", fileNum);
  // ofs_ref.open(buffer);
  // ofs_ref << "P3\n160 167\n8\n";

  for (int i = SCREEN_START_HEIGHT; i < SCREEN_END_HEIGHT; i++)
  {
    for (int j = 0; j < screen.width(); j++)
    {
      unsigned int pxl = screen.get(i,j);
      // bool isObjFound = false;

      for (int k = 0; k < NUMOFOBJECTS; k++)
      {
        if (pxl == PXLS[k])
        {
          // isObjFound = true;
          so[k].accumulate(i, j);
          break;
        }
      }

      // if (isObjFound)
      // {
      //   unsigned int b_3 = (pxl & 0xE0) >> 5;
      //   unsigned int b_2 = (pxl & 0x1C) >> 2;
      //   unsigned int b_1 = (pxl & 0x3);
      //   ofs_ref << b_3 << " " << b_2 << " " << b_1 << " ";
      // }
      // else
      // {
      //   ofs_ref << 0 << " " << 0 << " " << 0 << " ";
      // }
    }
    // ofs_ref << "\n";
  }

  // ofs_ref.close();

  // Update position
  for (int i = 0; i < NUMOFOBJECTS; i++)
  {
    vOut[i].updatePos(so[i]);
  }

  for (int i = NUMOFOBJECTS; i < NUMCOORDFEATURE; i++)
  {
    vOut[i].updateVelo(so[i - NUMOFOBJECTS + 1]);
  }
}
