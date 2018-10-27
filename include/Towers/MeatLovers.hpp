#pragma once
#include "RangeTower.hpp"
#include "../include/Projectiles/MeatLoversProjectile.hpp"
class MeatLovers : public RangeTower{
public:
  MeatLovers(shared_ptr<TextLoader> textLoader, string towerTypeID);

  void upgrade();
  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  void setProjectile();
};
