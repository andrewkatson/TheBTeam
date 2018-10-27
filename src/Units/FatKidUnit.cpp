//
// Created by jeremy on 10/26/18.
//

#include "../include/Units/FatKidUnit.hpp"

FatKidUnit::FatKidUnit(int hitpoint, int damage, int armor, int speed, int armorPenetration, int attackRadius){
  this->hitpoints=hitpoint;
  this->damage=damage;
  this->armor=armor;
  this->speed=speed;
  this->armorPenetration=armorPenetration;
  this->attackRadius=attackRadius;
}
