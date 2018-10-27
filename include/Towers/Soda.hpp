#pragma once
#include "RangeTower.hpp"

class Soda : public RangeTower{
public:
  Soda(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
