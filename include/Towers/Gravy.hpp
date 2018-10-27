#pragma once
#include "RangeTower.hpp"

class Gravy : public RangeTower{
public:
  Gravy(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
