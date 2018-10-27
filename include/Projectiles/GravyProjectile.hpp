#pragma once
#include "Projectile.hpp"
class GravyProjectile : public Projectile{
public:
  GravyProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
