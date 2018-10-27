#pragma once
#include "RangeTower.hpp"

class Slushie : public RangeTower{
public:
  Slushie(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
};
