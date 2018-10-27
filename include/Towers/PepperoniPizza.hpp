#pragma once
#include "RangeTower.hpp"

class PepperoniPizza : public RangeTower{
public:
  PepperoniPizza(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
