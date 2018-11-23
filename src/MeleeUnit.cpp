/*
 * MeleeUnit.cpp
 *
 * Purpose: Handle all operations for melee based units
 *
 * @author Jeremy Elkayam
 */
#include "MeleeUnit.hpp"

MeleeUnit::MeleeUnit(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader) : ActorInterface(){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> s_elapsed = 0;
  this ->current_sprite = 0;
}

void MeleeUnit::update(float delta){

  if(speed==0 && current_sprite!=2){

    current_sprite=2;
    this->sprite.setTexture(textures->at(current_sprite));
    
  }else {

    s_elapsed += delta;

    if (s_elapsed > .5) {
      s_elapsed = 0;

      if (current_sprite == 0) {
        current_sprite = 1;
      } else {
        current_sprite = 0;
      }

      this->sprite.setTexture(textures->at(current_sprite));

    }
  }
}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void MeleeUnit::initSprite(){
  (this->sprite).setTexture(textures -> at(current_sprite));
}

void MeleeUnit::updateHitpoints(int damage){
  hitpoints-=damage;
}

void MeleeUnit::updateArmor(int damage) {
  armor-=damage;
}

bool MeleeUnit::canAttack() {
  //TODO - check if enemy in attack radius, return true if there's someone to attack
  //maybe leave this to using Box2D?
  //wait for animation to finish before initiate new attack
}

void MeleeUnit::attack() {
  engagedUnit->updateHitpoints(damage);
  //TODO - handle attacking animation with userview, initiate attack.
}

HitpointBar MeleeUnit::getHpBar() {
  return this->hpBar;
}

void MeleeUnit::move(float deltaS, float xmult, float ymult){
  this->x+=speed*deltaS*xmult;
  this->y+=speed*deltaS*ymult;

}

bool MeleeUnit::isCollision(sf::FloatRect colliding_with){

}

int MeleeUnit::getLunchMoney() const {
  return lunchMoney;
}

void MeleeUnit::setLunchMoney(int lunchMoney) {
  MeleeUnit::lunchMoney = lunchMoney;
}

void MeleeUnit::setHitpoints(int hitpoints) {
  MeleeUnit::hitpoints = hitpoints;
}

int MeleeUnit::getDamage() const {
  return damage;
}

void MeleeUnit::setDamage(int damage) {
  MeleeUnit::damage = damage;
}

int MeleeUnit::getArmor() const {
  return armor;
}

void MeleeUnit::setArmor(int armor) {
  MeleeUnit::armor = armor;
}

int MeleeUnit::getAttackRadius() const {
  return attackRadius;
}

void MeleeUnit::setAttackRadius(int attackRadius) {
  MeleeUnit::attackRadius = attackRadius;
}
