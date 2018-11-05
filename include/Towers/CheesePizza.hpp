#pragma once

#include "RangeTower.hpp"
#include "../include/Projectiles/CheesePizzaProjectile.hpp"
class CheesePizza : public RangeTower{
public:
  CheesePizza(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();

  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  void setProjectile();
  void setUpUnits(){}
};
