#pragma once
#include "RangeTower.hpp"

class NormalMMS : public RangeTower{
public:
  NormalMMS(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
