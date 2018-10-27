#include "../include/Units/NormalFryUnit.hpp"
NormalFryUnit::NormalFryUnit(int hitpoint, int damage, int armor, int speed, int armorPenetration, int attackRadius){
  this->hitpoints=hitpoint;
  this->damage=damage;
  this->armor=armor;
  this->speed=speed;
  this->armorPenetration=armorPenetration;
  this->attackRadius=attackRadius;
}
