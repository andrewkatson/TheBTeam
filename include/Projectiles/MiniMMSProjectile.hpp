#pragma once
#include "Projectile.hpp"
class MiniMMSProjectile : public Projectile{
public:
  MiniMMSProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
