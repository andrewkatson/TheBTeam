#pragma once
#include "RangeTower.hpp"
class MiniMMS : public RangeTower{
public:
  MiniMMS(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
