#pragma once
#include "RangeTower.hpp"

class EnergyDrink : public RangeTower{
public:
  EnergyDrink(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
