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
  sf::FloatRect boundsOfSprite = sprite.getLocalBounds();
  sprite.setOrigin(boundsOfSprite.left + (boundsOfSprite.width)/2.0,
  boundsOfSprite.top + (boundsOfSprite.height)/2.0);
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

void MeleeUnit::move(float deltaS){
  this->x+=(speed*cos(direction))*ActorInterface::getXScale();
  this->y+=(speed*sin(direction)*-1)*ActorInterface::getYScale();

  //keep the box2d body updated
  body -> SetTransform(b2Vec2(x,y), body->GetAngle());
  b2Vec2 pos = body -> GetPosition();
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
  return radius;
}

void MeleeUnit::setAttackRadius(int attackRadius) {
  radius = attackRadius;
}

void MeleeUnit::setFixtures(){
  cout << " pos " << x << " " << y << endl;
  cout << "is this " << isActor << " " << isTower << endl;
  sf::FloatRect boundingBox = sprite.getGlobalBounds();
  b2PolygonShape boxShape;
  boxShape.SetAsBox(boundingBox.width*xScale, boundingBox.height*yScale);

  b2FixtureDef boxFixtureDef;
  boxFixtureDef.shape = &boxShape;
  boxFixtureDef.density = 1;
  fixture = body->CreateFixture(&boxFixtureDef);
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
