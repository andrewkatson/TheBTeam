#pragma once
#include "Projectile.hpp"
class CheesePizzaProjectile : public Projectile{
public:
  CheesePizzaProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
