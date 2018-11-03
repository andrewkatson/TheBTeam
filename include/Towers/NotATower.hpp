#pragma once

/*
 * A stand in for a tile without a tower
 * @author Andrew Katson
 */

#include "RangeTower.hpp"
#include "../include/Projectiles/CheesePizzaProjectile.hpp"
class NotATower : public RangeTower{
public:
  NotATower(string towerTypeID);

  void upgrade();

  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  void setProjectile();
};
