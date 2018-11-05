#pragma once
#include "TextLoader.hpp"
#include "MeleeTower.hpp"
#include "../include/Units/NormalFryUnit.hpp"

class NormalFry : public MeleeTower{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
public:
  NormalFry(shared_ptr<TextLoader> textLoader, string towerTypeID,int maxMeleeUnits);

  virtual void upgrade();
  virtual void setUpUnits();
  void setProjectile(){}

};
