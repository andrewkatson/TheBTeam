#pragma once

#include "Obstacle.hpp"

class CafeteriaTable : public Obstacle{
public:
  CafeteriaTable(int row, int col, int price);
};
