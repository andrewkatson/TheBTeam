#pragma once

#include "Projectile.hpp"
class SlushieProjectile : public Projectile{
public:
  SlushieProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
