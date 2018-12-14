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
  this -> attack_cycle_position = 0;
  this->timeSinceLastAttack = 0;

}

//update animation for our main unit
void MeleeUnit::update(float delta){

  if(speed==0){

    current_sprite=2;
    this->sprite.setTexture(textures->at(current_sprite));

  }else {
    updateWalkAnim(delta, textLoader->getDouble("IDS_Enemy_Animation_Speed_Factor")/speed);
  }
}

void MeleeUnit::updateWalkAnim(float delta, float timeBetweenFrames){

  s_elapsed += delta;
  if (s_elapsed > timeBetweenFrames) {

    //cout << "swap frame" << endl;

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

  float deltaX = xVector * speed * delta;
  float deltaY = yVector * speed  * delta;

  float newX = deltaX + x;
  float newY = deltaY + y;




  if(abs(deltaX) > .1 || abs(deltaY) > .1) { //if our movement is above a certain threshold, change angle
    double angle = atan2(xTarget - x, yTarget - y) - M_PI / 2;
    setDirection(angle);
    //cout << "time between frames " << textLoader->getDouble("IDS_Fry_Animation_Speed_Factor")/speed << endl;
    updateWalkAnim(delta,textLoader->getDouble("IDS_Fry_Animation_Speed_Factor")/speed);
  }else{
    current_sprite=2;
    this->sprite.setTexture(textures->at(current_sprite));
  }


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
  if(engagedUnit == NULL){
    return;
  }
  timeSinceLastAttack = 0;


  float enemyHP = engagedUnit->getHitpoints();
  int enemyArmor = engagedUnit->getArmor();

  assert(armor>0);
  enemyHP -= (float)damage *(float)(armorPenetration/enemyArmor);
  engagedUnit->updateHitpoints(enemyHP);
  //cout<<" I AM "  << getType()<<endl;
  //cout<<"enemy has " << enemyHP<<endl;
  engagedUnit->flickerUnit();
  s_elapsed=0;
  if(attack_cycle_position==0){
    attack_cycle_position=1;
    current_sprite=3;
  }else{//attack cycle position must be the last spot in the cycle
    attack_cycle_position=3;
    current_sprite = 4;
  }
  this->sprite.setTexture(textures->at(current_sprite));
}

void MeleeUnit::updateAttack(float delta){
  s_elapsed+=delta;
  timeSinceLastAttack+=delta;

  if(s_elapsed > textLoader->getDouble("IDS_Unit_Punch_Time_Between_Frames") && current_sprite!=2){
    cout << "i set my sprite back to standing" << endl;
    current_sprite = 2;
    if(attack_cycle_position==1){
      attack_cycle_position=2;
    }else{
      attack_cycle_position=0;
    }

    this->sprite.setTexture(textures->at(current_sprite));

  }

  if(attackPossible()){
    attackEngagedUnit();

    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

    shared_ptr<EventInterface> playSound = make_shared<PlaySoundEvent>("", textLoader->getString(
            "IDS_Unit_Punch_Noise"), nowInNano);
    eventManager->queueEvent(playSound);

    //cout<<" my name is "  << getType()<<endl;
    //cout << "and i am in a punching frame" << endl;

  }
}
bool MeleeUnit::attackPossible(){
  assert(attackRate>0);

  cout << "i am " << typeID << " can i attack? " << (timeSinceLastAttack > 1.0/(float)attackRate) << endl;

  cout << "time between attacks  " << 1.0/(float)attackRate << endl;
  cout << "time is " << timeSinceLastAttack << endl;

  return timeSinceLastAttack > 1.0/(float)attackRate;
}
