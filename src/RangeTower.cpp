#include "RangeTower.hpp"

//empty constructor used for derived classes to call
RangeTower::RangeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> isMelee = false;
}

void RangeTower::update(float delta){

}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void RangeTower::initSprite(){
  (this->sprite).setTexture(textures -> at(0));
}

void RangeTower::upgrade(){}

void RangeTower::setProjectile(){}

int RangeTower::getPrice(){
  return this -> price;
}

bool RangeTower::canAttack(){
  return false;
}

void RangeTower::attack(shared_ptr<ActorInterface> enemyInRange){

}

/*
 * Return basic statistics about this type of tower
 */
shared_ptr<vector<int>>  RangeTower::getStatistics(){
  shared_ptr<vector<int>> stats = make_shared<vector<int>>();

  //push back the projectile damage
  stats->push_back(currentProjectile -> getDamage());
  //push back the projectile armor penetration
  stats->push_back(currentProjectile -> getArmorPenetration());
  //area of effect
  stats->push_back(currentProjectile -> areaOfEffect);
  //rate of fire of tower
  stats->push_back(rateOfFire);

  return stats;
}
