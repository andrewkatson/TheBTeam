#pragma once
#include "Projectile.hpp"
class NormalMMSProjectile : public Projectile{
public:
  NormalMMSProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
