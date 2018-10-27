#pragma once
#include "RangeTower.hpp"
class DeepDish : public RangeTower{
public:
  DeepDish(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
