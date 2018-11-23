#include "RangeTower.hpp"

//empty constructor used for derived classes to call
RangeTower::RangeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> isMelee = false;
  this -> radiusVisible = false;
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
  shared_ptr<ActorInterface> firedProjectile = createProjectile();
  assert(firedProjectile != NULL);
  assert(firedProjectile -> getType() == currentProjectile -> getType());

  //set the row and col of the projetile created to be the same as the tower's
  firedProjectile -> setRow(row);
  firedProjectile -> setCol(col);
  //set the x and y coordinate of the projectile to the same as the firing tower's
  firedProjectile -> setXCoordinate(this -> xCoordinate);
  firedProjectile -> setYCoordinate(this -> yCoordinate);

  //set up the vector that the projectile will be fired on
  calcAttackVector(firedProjectile, enemyInRange);

  //Create ActorCreatedEvent and attach the created projectile
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
  bool isProjectile = true;
  shared_ptr<EventInterface> projectileFiredEvent = make_shared<ActorCreatedEvent>(firedProjectile, isProjectile, nowInNano);
  this -> eventManager -> queueEvent(projectileFiredEvent);
}

/*
 * Caclulates the x and y of the vector that the projectile will travel on.
 * Uses the speed, direction and distance to the enemy unit as a guide
 */
void RangeTower::calcAttackVector(shared_ptr<ActorInterface> projectileToFire, shared_ptr<ActorInterface> enemyInRange){
  float xvec = enemyInRange -> getXCoordinate() - this -> xCoordinate;
  float yvec = enemyInRange -> getYCoordinate() - this -> yCoordinate;

  //cast to projectile before calling set vector
  Projectile* projectile = dynamic_cast<Projectile*>(projectileToFire.get());

  projectile -> setVector(xvec,yvec);
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

/*
 * Generic version of the way to create aprojectile
 * should never be called so it returns NULL
 */
shared_ptr<ActorInterface> RangeTower::createProjectile(){
  return NULL;
}
