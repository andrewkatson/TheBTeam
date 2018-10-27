#pragma once
#include "RangeTower.hpp"

class MeatLovers : public RangeTower{
public:
  MeatLovers(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
