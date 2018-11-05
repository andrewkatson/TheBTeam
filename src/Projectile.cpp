//
// Created by jeremy on 10/20/18.
//

#include "Projectile.hpp"

Projectile::Projectile(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}

int Projectile::getArmorPenetration() const {
  return armorPenetration;
}

int Projectile::getDamage() const {
  return damage;
}

void Projectile::move(float delta){

}

void Projectile::setVector(int x, int y){
  this -> x = x;
  this -> y = y;
}

void Projectile::setProjectileID(int ID){
  this -> projectileID = ID;
}

void Projectile::update(float delta){

}
