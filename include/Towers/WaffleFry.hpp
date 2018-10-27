#pragma once
#include "MeleeTower.hpp"
#include "TextLoader.hpp"
#include "../include/Units/WaffleFryUnit.hpp"
class WaffleFry : public MeleeTower{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
public:
  WaffleFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits);

  virtual void upgrade();
  virtual void setUpUnits();
};
