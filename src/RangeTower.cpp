#include "RangeTower.hpp"

//empty constructor used for derived classes to call
RangeTower::RangeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader) : TowerInterface(){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> isMelee = false;
  this -> isTower = true;
  this -> radiusVisible = false;
  //set the tower interface scaling factor for the rate of fire
  rateOfFireScale = textLoader -> getDouble(string("IDS_Rate_Of_Fire_Scaler"));
  lastTimeFired = 0.0;
  this -> setToCenter();
}

void RangeTower::update(float delta){

  //the time object of the class
  auto time = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto currTime = duration_cast<seconds>(time.time_since_epoch()).count();

  //if time has passed between the last shot and the current shot
  //and the sprite is set to open then we reset it
  if(currentTexture != 0 && currTime - lastTimeFired > (delta/(rateOfFire))){
    (this->sprite).setTexture(textures -> at(0));
    currentTexture = 0;
  }
}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void RangeTower::initSprite(){
  (this->sprite).setTexture(textures -> at(0));
  currentTexture = 0;
}

void RangeTower::upgrade(){}

void RangeTower::setProjectile(){}

int RangeTower::getPrice(){
  return this -> price;
}

bool RangeTower::canAttack(){}

void RangeTower::attack(shared_ptr<ActorInterface> enemyInRange, float delta){

  //the time object of the class
  auto time = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto timeToShoot = duration_cast<seconds>(time.time_since_epoch()).count();
  //if we are firing too quickly we ignore this enemy
  if(timeToShoot - lastTimeFired < (delta/rateOfFire)){
    //cout << "time " << timeToShoot << endl;
    //cout << "last time " << lastTimeFired << endl;
    //cout << "diff " << timeToShoot - lastTimeFired << endl;
    //cout << "rate of fire " << rateOfFire << endl;
    return;
  }

  //cout << "fire " << endl;

  if(textures -> size() > 1){
    //switch to the open texture if there is one
    (this->sprite).setTexture(textures -> at(1));
    currentTexture = 1;
  }


  shared_ptr<ActorInterface> firedProjectile = createProjectile();

  //send the size of a tile in the x and y to the projectile
  firedProjectile -> setTileSize(xTileSize, yTileSize);
  //send the scaling to the projectile for use when it explodes
  firedProjectile -> setTowerScale(xScale, yScale);

  //modify the statistics of the firedProjectile so they match any upgrades in the stored projectile
  modifyToIncludeUpgrades(firedProjectile);

  assert(firedProjectile != NULL);
  assert(firedProjectile -> getType() == currentProjectile -> getType());
  //firedProjectile -> setWorld(world);

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

  //update the time of the last fired shot
  lastTimeFired = duration_cast<seconds>(now.time_since_epoch()).count();


  bool isProjectile = true;
  shared_ptr<EventInterface> projectileFiredEvent = make_shared<ActorCreatedEvent>(firedProjectile, isProjectile, nowInNano);
  this -> eventManager -> queueEvent(projectileFiredEvent);
}

/*
 * Update all statistics for the fired projectile to reflect the upgrades bought
 * for the stored projectile
 */
void RangeTower::modifyToIncludeUpgrades(shared_ptr<ActorInterface> firedProjectile){
  firedProjectile->updateDamage(currentProjectile->getDamage());
  firedProjectile->updateArmorPenetration(currentProjectile->getArmorPenetration());
  firedProjectile->updateRadius(currentProjectile->getRadius());
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

  //set the target of the projectile to the be x,y of the enemy being fired at
  projectile -> setTargetPos(enemyInRange -> getXCoordinate(), enemyInRange -> getYCoordinate());

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
  stats->push_back(currentProjectile -> getAreaOfEffect());
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
