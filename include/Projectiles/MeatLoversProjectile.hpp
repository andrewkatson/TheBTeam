#pragma once
#include "Projectile.hpp"
class MeatLoversProjectile : public Projectile{
public:
  MeatLoversProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
