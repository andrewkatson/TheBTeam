#pragma once
#include "MeleeTower.hpp"
#include "TextLoader.hpp"
#include "../include/Units/SpicyFryUnit.hpp"
class SpicyFry : public MeleeTower{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;

public:
  SpicyFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits);

  virtual void upgrade();
  virtual void setUpUnits();
  void setProjectile(){}

};
