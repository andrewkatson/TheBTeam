#pragma once

#include "RangeTower.hpp"

class PeanutButterMMS : public RangeTower{
public:
  PeanutButterMMS(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
