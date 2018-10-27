#pragma once
#include "Projectile.hpp"
class SodaProjectile : public Projectile{
public:
  SodaProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
