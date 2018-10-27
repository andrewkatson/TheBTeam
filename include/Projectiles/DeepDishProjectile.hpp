#pragma once
#include "Projectile.hpp"
class DeepDishProjectile : public Projectile{
  public:
  DeepDishProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
