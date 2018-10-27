//
// Created by jeremy on 10/20/18.
//

#include "Projectile.hpp"

int Projectile::getArmorPenetration() const {
  return armorPenetration;
}

int Projectile::getDamage() const {
  return damage;
}

void Projectile::move(float deltaS){

}

void Projectile::setVector(int x, int y){
  this -> x = x;
  this -> y = y;
}

void Projectile::setProjectileID(int ID){
  this -> projectileID = ID;
}
