#pragma once

#include "Obstacle.hpp"

class CafeteriaTable : public Obstacle{
public:
  CafeteriaTable(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void setProjectile(){}
  void setUpUnits(){}
};
