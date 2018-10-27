#pragma once

#include "RangeTower.hpp"

class PeanutMMS : public RangeTower{
public:
  PeanutMMS(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
