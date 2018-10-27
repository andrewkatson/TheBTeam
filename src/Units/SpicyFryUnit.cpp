#include "../include/Units/SpicyFryUnit.hpp"
SpicyFryUnit::SpicyFryUnit(int hitpoint, int damage, int armor, int speed, int armorPenetration){
  this->hitpoints=hitpoint;
  this->damage=damage;
  this->armor=armor;
  this->speed=speed;
  this->armorPenetration=armorPenetration;
}
