//
// Created by jeremy on 10/20/18.
//

#include "Projectile.hpp"

Projectile::Projectile(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void Projectile::initSprite(){
  (this->sprite).setTexture(textures -> at(0));
}

int Projectile::getArmorPenetration() const {
  return armorPenetration;
}

int Projectile::getDamage() const {
  return damage;
}

void Projectile::move(float delta, float xmult, float ymult){

}

void Projectile::setVector(float x, float y){
  this -> x = x;
  this -> y = y;
}

void Projectile::setProjectileID(int ID){
  this -> projectileID = ID;
}

void Projectile::update(float delta){

}
