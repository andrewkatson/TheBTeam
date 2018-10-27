#pragma once
#include "Projectile.hpp"
class PepperoniPizzaProjectile : public Projectile{
public:
  PepperoniPizzaProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect);
};
