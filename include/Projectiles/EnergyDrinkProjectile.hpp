#pragma once
#include "Projectile.hpp"
class EnergyDrinkProjectile : public Projectile{
  public:
  EnergyDrinkProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
