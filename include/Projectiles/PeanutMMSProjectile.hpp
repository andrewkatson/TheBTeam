#pragma once
#include "Projectile.hpp"
class PeanutMMSProjectile : public Projectile{
public:
  PeanutMMSProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
