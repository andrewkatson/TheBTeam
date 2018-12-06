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
  this -> isProjectile = false;
  this -> overshooting = false;
  this -> overshoot = 0;
  this -> current_sprite = 0 ;
  this -> walk_cycle_position = 0;
}

void MeleeUnit::update(float delta){

  if(speed==0){

    current_sprite=2;
    this->sprite.setTexture(textures->at(current_sprite));

  }else {

    s_elapsed += delta;

    if (s_elapsed > 1/speed) {
      s_elapsed = 0;

      if (walk_cycle_position == 0) { //first walking frame
        walk_cycle_position = 1;
        current_sprite = 2; //standing
      }else if(walk_cycle_position == 1){ // second walking frame
        walk_cycle_position = 2;
        current_sprite = 1;
      } else if(walk_cycle_position == 2) {
        walk_cycle_position = 3;
        current_sprite = 2;
      }else{
        walk_cycle_position = 0;
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


void MeleeUnit::setToCenter(){
  sf::FloatRect boundsOfSprite = sprite.getGlobalBounds();
  sprite.setOrigin(boundsOfSprite.left + (boundsOfSprite.width)/2.0,
  boundsOfSprite.top + (boundsOfSprite.height)/2.0);
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

void MeleeUnit::move(float deltaS){
  this->x+=(speed*cos(direction))*ActorInterface::getXScale()*deltaS;
  this->y+=(speed*sin(direction)*-1)*ActorInterface::getYScale()*deltaS;
  if(isnan(x) || isnan(y)){
    //cout << "position after " << x << " " << y << endl;
    //cout << "direction was " << direction << endl;
  }
}

void MeleeUnit::vectorMove(float delta){
  //the weird subtraction here is to make it so that if a staistic "speed" is a high number
  //in the xml it will cause the unit to be faster while also having a similar calculation
  //to the normal unit move function
  //float newX = xVector / (abs(speed-25)) *delta *ActorInterface::getXScale() + x;
  //float newY = yVector / (abs(speed-25)) *delta *ActorInterface::getYScale() + y;

  float newX = xVector * speed * delta + x;
  float newY = yVector * speed  * delta + y;

  /*
  cout << "currently at " << x << " "<< y <<endl;
  cout << "x target is " << xTarget << " " << yTarget << endl;
  cout << "vec is " << xVector << " " << yVector << endl;
  cout << "go unit ! " << endl;
  cout << "new x " << newX << " " << newY << endl;
  cout << "xVector / speed " << xVector/speed <<  endl;
  cout << "yVector/ speed " << yVector/speed << endl;
  cout << "add deltax " << xVector/speed*delta << endl;
  cout << "add deltay " << yVector/speed*delta << endl;
  */
  //cout << "move to intended " << newX << " " << newY << endl;
  //we check to see if the projectile has overshot the target
  if(xVector > 0 ){
    if(newX > xTarget - e){
      newX = xTarget;
    }
  }
  else{
    if(newX < xTarget + e){
      newX = xTarget;
    }
  }

  if(yVector > 0){
    if(newY > yTarget - e){
      newY = yTarget;
    }
  }
  else{
    if(newY < yTarget + e){
      newY = yTarget;
    }
  }
  x = newX;
  y = newY;
  //cout << " move to " << x << endl;
  //cout << " move to " << y << endl;
}

/*
 * used to compare the position of a unit and its target
 * @return bool: if the coordinates passed are equivalent
 */
bool MeleeUnit::atTarget(){
  if(xTarget - e <= x && xTarget + e >= x){
    if(yTarget - e <= y && yTarget + e >=y){
      return true;
    }
  }
  return false;
}

bool MeleeUnit::isCollision(sf::FloatRect colliding_with){

}

int MeleeUnit::getLunchMoney() const {
  return lunchMoney;
}

void MeleeUnit::setLunchMoney(int lunchMoney) {
  this -> lunchMoney = lunchMoney;
}

void MeleeUnit::setHitpoints(float hitpoints) {
  this -> hitpoints = hitpoints;
}

int MeleeUnit::getDamage() const {
  return damage;
}

void MeleeUnit::setDamage(int damage) {
  this -> damage = damage;
}

int MeleeUnit::getArmor() const {
  return armor;
}

void MeleeUnit::setArmor(int armor) {
  assert(false);
  this-> armor = armor;
}

int MeleeUnit::getAttackRadius() const {
  return radius;
}

void MeleeUnit::setAttackRadius(int attackRadius) {
  this -> radius = attackRadius;
}


double MeleeUnit::getOvershoot() const {
  return overshoot;
}

void MeleeUnit::setOvershoot(double overshoot) {
  MeleeUnit::overshoot = overshoot;
}

bool MeleeUnit::isOvershooting() const {
  return overshooting;
}

void MeleeUnit::setOvershooting(bool overshooting) {
  MeleeUnit::overshooting = overshooting;
}

void MeleeUnit::attackEngagedUnit(){
  float enemyHP = engagedUnit->getHitpoints();
  int enemyArmor = engagedUnit->getArmor();

  assert(armor>0);
  enemyHP -= (float)damage *(float)(armorPenetration/enemyArmor);
  engagedUnit->updateHitpoints(enemyHP);
}

void MeleeUnit::updateAttack(float delta){
  if(attackPossible(delta)){
    attackEngagedUnit();
  }
}
bool MeleeUnit::attackPossible(float delta){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in seconds for the time
  auto nowInSec = duration_cast<seconds>(now.time_since_epoch()).count();
  //time -last attack < (delta/attackrate)
  assert(attackRate>0);
  long long diff = nowInSec - lastAttack;
  if((diff)<= (long long)(delta/attackRate)){
    return false;
  }
  lastAttack = nowInSec;
  return true;
}
