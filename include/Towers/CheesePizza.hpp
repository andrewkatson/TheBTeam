#pragma once

#include "RangeTower.hpp"
class CheesePizza : public RangeTower{
public:
  CheesePizza(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
