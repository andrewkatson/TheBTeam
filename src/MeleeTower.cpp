#include "MeleeTower.hpp"
//empty constructor used for derived classes to call
MeleeTower::MeleeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader) : TowerInterface(){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  //all rally points initilaized to this number so that if we try to spawn them without
  //reseting the rally point they will not spawn
  this -> xRally = 0xFFFFFFFF;
  this -> yRally = 0xFFFFFFFF;
  this -> e = 0.00001;
  this -> timeOfDeath = {-1, -1, -1};
  this -> isMelee = true;
  this -> isTower = true;
  this -> radiusVisible = false;
  this -> registerDelegates();
  this -> setToCenter();
}

MeleeTower::~MeleeTower(){
  this -> deregisterDelegates();
}

void MeleeTower::update(float delta){
  int unitIndex = 0;
  //always reset units engaged
  unitsEngaged = 0;

  //if we can respawn units then respawn them
  //respawnUnits(delta);

  //if a unit does not have an engaged enemy unit then send it back towards
  //a point situated around the rally point
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    //cout << "unit id " << unit -> getID() << endl;
    if(isnan(unit->getXCoordinate()) || isnan(unit->getYCoordinate())){
      cerr << "is nan here " << unit->getXCoordinate() << " " << unit -> getYCoordinate() << endl;
      assert(false);
    }

    if(unit -> getHitpoints() > 0){
      if(unit -> getEngagedUnit() == NULL){
        //sets the unit position to the center of the tower if there is no set rally point
        //or moves it closer to the rally point position
        float startPos = unit->getXCoordinate();
        float otherPos = unit->getYCoordinate();
        resetUnitPosition(unit, unitIndex, delta);
      }
      else{
        if(unit->getEngagedUnit()->getEngagedUnit() == unit){
          unitsEngaged++;
        }
        if(unit -> getEngagedUnit() -> getHitpoints() < 0){
          if(unit -> getEngagedUnit()->getEngagedUnit() == unit){
            unit -> getEngagedUnit() -> setEngagedUnit(NULL);
          }
          unit -> setEngagedUnit(NULL);
          break;
        }

        //check if my unit is at destination, if so move towards xtarget and ytarget
        //else move to the enemy BUT before set the xvec and yVect
        if (unit->atTarget()){
          unit->updateAttack(delta);
        }
        else{

          //recalcualte their attack vector so that they move slowly as they get closer to the target
          float angle = 360/currentUnits.size();
          float enemyX = unit->getEngagedUnit()->getXCoordinate();
          float enemyY = unit->getEngagedUnit()->getYCoordinate();
          sf::FloatRect dimensions = unit->getEngagedUnit()->getSprite().getGlobalBounds();
          float unitCombatDistance = textLoader->getInteger(string("IDS_Unit_Combat_Distance"));
          //the x and y for the unit that is its resting position around the rally point flag
          float newX = (unitCombatDistance) * xScale * cos(angle * unitIndex * (M_PI / 180.0)) + enemyX;
          float newY = (unitCombatDistance) * yScale * sin(angle * unitIndex * (M_PI / 180.0)) + enemyY;

          unit->setEngagedUnit(unit->getEngagedUnit());// x targ and y tart
          unit->setTargetPos(newX, newY);
          unit->setVector(newX - unit->getXCoordinate(), newY - unit->getYCoordinate());
          unit->vectorMove(delta);
        }
      }

    }
    else{
      handleDeadUnit(unitIndex);
    }
    unitIndex++;
  }
}


/*
 * Initialize all the units that will spawn for this tower with a position
 */
void MeleeTower::setUpUnits(){
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  //use a pseudo random generator to make the speeds of the units a bit different
  std::default_random_engine generator(seed);
  std::exponential_distribution<double> distribution(textLoader->getDouble(string("IDS_Melee_Tower_Unit_Speed_Lamba")));


  for(int unitIndex = 0; unitIndex < currentUnits.size(); unitIndex++){
    currentUnits.at(unitIndex) -> setXCoordinate(xCoordinate);
    currentUnits.at(unitIndex) -> setYCoordinate(yCoordinate);

    //fry guys given slightly differnet speeds
    float currSpeed = currentUnits.at(unitIndex)->getSpeed();
    float modifiedSpeed = currSpeed + distribution(generator);
    modifiedSpeed = modifiedSpeed > 0 ? modifiedSpeed : 1;

    currentUnits.at(unitIndex) -> setSpeed(modifiedSpeed);
  }
}

/*
 * Set all units to the positions passed
 * @param x: the x position to set the units to
 * @param y: the y position to set the units to
 */
void MeleeTower::setUpUnitCoordinates(float x, float y){
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    unit->setXCoordinate(x);
    unit->setYCoordinate(y);
  }
}

/*
 * Set the unit's position in the grid
 */
void MeleeTower::setUpUnitPositions(int row, int col){
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    unit -> setRow(row);
    unit -> setCol(col);
  }
}

void MeleeTower::setUpUnitTileSize(float x, float y){
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    unit->setTileSize(x,y);
  }
}

/*
 * Make events to signal that all the units were created
 */
void MeleeTower::logUnitsForCollisionManager(){
  //Create ActorCreatedEvent and attach the created projectile
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  for(shared_ptr<MeleeUnit> unit : currentUnits){

    //make an event to mark the unit's creation
    //Create ActorCreatedEvent and attach the created actor
    bool isProjectile = false;
    shared_ptr<EventInterface> alliedUnitCreatedEvent = make_shared<ActorCreatedEvent>(unit, isProjectile, nowInNano);
    this -> eventManager -> queueEvent(alliedUnitCreatedEvent);
  }
}

/*
 * Check that all unit row, col reflect their current position in x,y
 */
void MeleeTower::verifyUnitPositions(float tileXSize, float tileYSize){
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    if(unit->getRow() != unit->getYCoordinate()/tileYSize){
      unit->setRow(unit->getYCoordinate()/tileYSize);
    }
    if(unit->getCol() != unit->getXCoordinate()/tileXSize){
      unit->setCol(unit->getXCoordinate()/tileXSize);
    }
  }
}

/*
 * Set all the unit positions to a point on the circle surrounding the rally point corresponding
 * to their index (unless the rally point is the tower's center in which case we set all positions to tower pos)
 * @param unit: the unit to reset
 * @param unitIndex: the index in the vector of units of this unit
 * @param delta: the time used to keep the adaptive frame rate (default is 1.0)
 */
void MeleeTower::resetUnitPosition(shared_ptr<MeleeUnit> unit, int unitIndex, float delta){
  if(xRally == xCoordinate && yRally == yCoordinate){
    unit->setXCoordinate(xRally);
    unit->setYCoordinate(yRally);
  }
  else{
    //the angle to use to stagger each unit around the rally point flag
    float angle = 360.0 / totalUnits;

    //the radius without scaling of the circle to place the units on
    float radiusOfUnitCircle = (textLoader -> getInteger(string("IDS_Button_Radius"))
                    + textLoader -> getInteger(string("IDS_Rally_Flag_Unit_Offset")));

    //the x and y for the unit that is its resting position around the rally point flag
    float newX = (radiusOfUnitCircle) * xScale * cos(angle*unitIndex * (M_PI/180.0)) + xRally;
    float newY = (radiusOfUnitCircle) * yScale * sin(angle*unitIndex * (M_PI/180.0)) + yRally;

    //set the target for the unit to be the rally point
    unit -> setTargetPos(newX, newY);

    float xvec = newX -  unit->getXCoordinate();
    float yvec = newY -  unit->getYCoordinate();

    //set the vector the unit will move along
    unit -> setVector(xvec,yvec);

    //cout << "unit " << unitIndex << endl;
    //cout << "go to " << newX << " " << newY << endl;
    //cout << "along " << xvec << " " << yvec << endl;

    //move the unit
    unit -> vectorMove(delta);
    /*
    if(isnan(newX) || isnan(newY)){
      //cout << "oh my naaan " << newX << " " << newY << endl;
    }


    /*
    //if the unit is already at its correct resting poisiton nothing needs to be done
    if(!(withinRange(newX, newY, unit->getXCoordinate(), unit->getYCoordinate()))){

      //the vector components of the movement this unit needs to make
      float xVector = newX - unit -> getXCoordinate();
      float yVector = newY - unit -> getYCoordinate();
      //cout << "unit x position"<<endl;
      //cout<< unit -> getXCoordinate()<<endl;
      //cout<<"unit y position"<< endl;
      //cout<< unit -> getYCoordinate()<<endl;
      //cout<< "unit hp"<< endl;
      //cout<< unit -> getHitpoints()<<endl;

      //if the x vector of the y vector of the unit are nan set the units position to be its reset position
      if(isnan(xVector) || isnan(yVector)){
        unit->setXCoordinate(newX);
        unit->setYCoordinate(newY);
        return;
      }

      //convert the vector into radians for the direction
      double direction = atan2((-1)*yVector, xVector);

      //set the direction for the unit (value on the unit circle)
      unit -> setDirection(direction);

      //then move it
      unit -> move(delta);

      if(isnan(unit->getXCoordinate()) || isnan(unit->getYCoordinate())){
        //cout << "what the helll " << unit->getXCoordinate() << " " << unit -> getYCoordinate() << endl;
      }

      //we check to see if the projectile has overshot the target
      if(xVector > 0 ){
        if(unit->getXCoordinate() > newX - e){
          unit->setXCoordinate(newX);
        }
      }
      else{
        if(unit->getXCoordinate() < newX + e){
          unit->setXCoordinate(newX);
        }
      }

      if(yVector > 0){
        if(unit->getYCoordinate() > newY - e){
          unit->setYCoordinate(newY);
        }
      }
      else{
        if(unit->getYCoordinate() < newY + e){
          unit->setYCoordinate(newY);
        }
      }
    }
    */
  }
}

/*
 * @return if x2,y2 are near enough to x1,y1
 */
bool MeleeTower::withinRange(float x1, float y1, float x2, float y2){
  if(x1-e <= x2 && x1+e>=x2){
    if(y1-e <= y2 && y1+e>=y2){
      return true;
    }
  }
  return false;
}

/*
 * Caclulates the x and y of the vector that the projectile will travel on.
 * Uses the speed, direction and distance to the enemy unit as a guide
 */
void MeleeTower::calcAttackVector(shared_ptr<ActorInterface> meleeUnit, shared_ptr<ActorInterface> enemyInRange){
  float xvec = enemyInRange -> getXCoordinate() - this -> xCoordinate;
  float yvec = enemyInRange -> getYCoordinate() - this -> yCoordinate;

  //set the target of the projectile to the be x,y of the enemy being fired at
  meleeUnit -> setTargetPos(enemyInRange -> getXCoordinate(), enemyInRange -> getYCoordinate());

  meleeUnit -> setVector(xvec,yvec);
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void MeleeTower::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate actorDestroyedDelegate = std::bind(&MeleeTower::handleActorDestroyed, this, _1);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorDestroyedDelegate, textLoader -> getString(string("IDS_MT_AD")),actorDestroyedEventType);
}

/*
 * Deregister the delegates methods for this class
 */
void MeleeTower::deregisterDelegates(){

    //make an event and get its type
    ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
    EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_MT_AD")),actorDestroyedEventType);
}

void MeleeTower::upgrade(){}


/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void MeleeTower::initSprite(){
  (this->sprite).setTexture(textures -> at(0));
  currentTexture = 0;
}

/*
 * Set the point where the melee units attached to this tower will go back to
 * when they are not fighting
 * @param x: the x coordinate
 * @param y: the y coordinate
 */
void MeleeTower::resetRallyPoint(float x, float y){
  //if this rally point is not in the prescribed radius around the tower
  if(x<xCoordinate-radius*xScale || x>xCoordinate+radius*xScale || y<yCoordinate-radius*yScale || y>yCoordinate+radius*yScale){
    return;
  }
  this -> xRally = x;
  this -> yRally = y;
}

int MeleeTower::getPrice(){
  return this -> price;
}

void  MeleeTower::setPos(intPair pos){
  row = pos.first;
  col=pos.second;

}
void  MeleeTower::setPos(int row, int col) {
  this->row=row;
  this->col=col;
}

/*
 * Handle any actor destroy event
 * @param event: event of the actor destroyed
 */
void MeleeTower::handleActorDestroyed(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * ActorDestroyedEvent type which allows us to access variables and methods
   * specific to ActorDestroyedEvent
   */
  const ActorDestroyedEvent* adEvent = static_cast<const ActorDestroyedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a ActorDestroyedEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  ActorDestroyedEventData* adEventData = static_cast<ActorDestroyedEventData*>((adEvent -> data).get());

  //the id of the actor destroyed
  long long actorID = adEventData -> actorID;

  int count = 0;
  //loop through our units to see if any of them are the destroyed one
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    if(unit -> getID() == actorID){
      handleDeadUnit(count);
      break;
    }
    count++;
  }
}

/*
 * If one of this tower's units died then we take the index of it in the currentUnits
 * list and start a timer for it that is checked for when it will respawn
 * @param indexOfUnit: the index of the dead unit in currentUnits
 */
void MeleeTower::handleDeadUnit(int indexOfUnit){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<seconds>(now.time_since_epoch()).count();

  //set whatever time is in this space to the current time
  timeOfDeath.at(indexOfUnit) = nowInNano;

  //set its fighting unit to null
  if(currentUnits.at(indexOfUnit) -> getEngagedUnit() != NULL){
    currentUnits.at(indexOfUnit) -> getEngagedUnit() -> setEngagedUnit(NULL);
  }
  currentUnits.at(indexOfUnit) -> setEngagedUnit(NULL);
}

/*
 * Respawn any unit that is below 0 health that has a larger elapsed time
 * since it last died than the respawn Speed
 */
void MeleeTower::respawnUnits(float delta){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<seconds>(now.time_since_epoch()).count();

  //cout << "here is problemo " << endl;
  for(int index = 0; index < timeOfDeath.size(); index++){
    long long deathTime = timeOfDeath.at(index);

    //if this is not a dead unit
    if(deathTime == -1){
      continue;
    }
    if(nowInNano - deathTime < (delta/respawnSpeed)){
      timeOfDeath.at(index) = -1;
      //set the health back to max
      currentUnits.at(index) -> resetHealth();

      //set the engaged unit to null
      currentUnits.at(index) -> setEngagedUnit(NULL);

      //set the position to be the center of the tower (so it will not draw and then start moving towards some other point)
      currentUnits.at(index) -> setXCoordinate(xCoordinate);
      currentUnits.at(index) -> setYCoordinate(yCoordinate);
    }
  }
  //cout << "no issue with respawn " << endl;
}

/*
 * @return if there is any enemy unit within the radius ofthe tower
 */
bool MeleeTower::canAttack(){

}

/*
 * If we can attack then we check to see if a unit is not engaged or
 * is engaged with an enemy unit that is not also engaged with it
 */
void MeleeTower::attack(shared_ptr<ActorInterface> enemyInRange, float delta){
  //do nothing if the rally point is still not reset
  if(xRally == xCoordinate && yRally == yCoordinate){
    return;
  }
  if(enemyInRange == NULL){
    return;
  }
  if(unitsEngaged == currentUnits.size()){
    return;
  }
  int unitIndex = 0;
  //the angle to use to stagger each unit around the rally point flag
  float angle = 360.0 / totalUnits;
  for (shared_ptr<ActorInterface> unit : currentUnits) {
    //cout << "we are fine" << endl;
    isEnemyPointingAtUnit = true;
    if (unit->getHitpoints() > 0) {
      cout << " Fry unti " << unitIndex << " is alive " << endl;
      if (unit->getEngagedUnit() == NULL) {
        float enemyX = enemyInRange->getXCoordinate();
        float enemyY = enemyInRange->getYCoordinate();
        sf::FloatRect dimensions = enemyInRange->getSprite().getGlobalBounds();

        float unitCombatDistance = textLoader->getInteger(string("IDS_Unit_Combat_Distance"));
        //the x and y for the unit that is its resting position around the rally point flag
        float newX = (unitCombatDistance) * xScale * cos(angle * unitIndex * (M_PI / 180.0)) + enemyX;
        float newY = (unitCombatDistance) * yScale * sin(angle * unitIndex * (M_PI / 180.0)) + enemyY;

        unit->setEngagedUnit(enemyInRange);// x targ and y tart
        unit->setTargetPos(newX, newY);
        unit->setVector(newX - unit->getXCoordinate(), newY - unit->getYCoordinate());
        // unit -> setXCoordinate(enemyInRange->getXCoordinate());
        // unit -> setYCoordinate(enemyInRange->getYCoordinate());
      }
      // check is there a unit that is engaged with an enemy unit that the enemy unit isn't engaged with
      if (unit->getEngagedUnit()->getEngagedUnit() != unit) {
        isEnemyPointingAtUnit = false;
      }
      if (isEnemyPointingAtUnit == false && unit->getEngagedUnit() == enemyInRange) {
        if (enemyInRange->getEngagedUnit() == NULL) {
          enemyInRange->setEngagedUnit(unit);
        }
      }
      if (isEnemyPointingAtUnit == false && unit->getEngagedUnit() != enemyInRange) {
        if (enemyInRange->getEngagedUnit() == NULL) {
          enemyInRange->setEngagedUnit(unit);
          float enemyX = enemyInRange->getXCoordinate();
          float enemyY = enemyInRange->getYCoordinate();
          sf::FloatRect dimensions = enemyInRange->getSprite().getGlobalBounds();


          float unitCombatDistance = textLoader->getInteger(string("IDS_Unit_Combat_Distance"));
          //the x and y for the unit that is its resting position around the rally point flag
          float newX = (unitCombatDistance) * xScale * cos(angle * unitIndex * (M_PI / 180.0)) + enemyX;
          float newY = (unitCombatDistance) * yScale * sin(angle * unitIndex * (M_PI / 180.0)) + enemyY;

          unit->setEngagedUnit(enemyInRange);// x targ and y tart
          unit->setTargetPos(newX, newY);
          unit->setVector(newX - unit->getXCoordinate(), newY - unit->getYCoordinate());
          // unit -> setXCoordinate(enemyInRange->getXCoordinate());
          // unit -> setYCoordinate(enemyInRange->getYCoordinate());
        } else {
          if (enemyInRange->getHitpoints() < unit->getEngagedUnit()->getHitpoints()) {
            float enemyX = enemyInRange->getXCoordinate();
            float enemyY = enemyInRange->getYCoordinate();
            sf::FloatRect dimensions = enemyInRange->getSprite().getGlobalBounds();

            float unitCombatDistance = textLoader->getInteger(string("IDS_Unit_Combat_Distance"));
            //the x and y for the unit that is its resting position around the rally point flag
            float newX = (unitCombatDistance) * xScale * cos(angle * unitIndex * (M_PI / 180.0)) + enemyX;
            float newY = (unitCombatDistance) * yScale * sin(angle * unitIndex * (M_PI / 180.0)) + enemyY;

            unit->setEngagedUnit(enemyInRange);// x targ and y tart
            unit->setTargetPos(newX, newY);
            unit->setVector(newX - unit->getXCoordinate(), newY - unit->getYCoordinate());
            // unit -> setXCoordinate(enemyInRange->getXCoordinate());
            // unit -> setYCoordinate(enemyInRange->getYCoordinate());
          }
        }
      }
      //cout << "finished " << endl;

      //cout << "unit " << counter << " is fighting " << unit -> getEngagedUnit() -> getType() << " with id " << unit -> getEngagedUnit() -> getID() << endl;
      //cout << "unit id is " << unit -> getID() << endl;
      unitIndex++;
    }
  }

}

/*
 * Return basic statistics about this type of tower
 */
shared_ptr<vector<int>>  MeleeTower::getStatistics(){
  shared_ptr<vector<int>> stats = make_shared<vector<int>>();

  //push nacl the unit hitpoints
  stats->push_back(currentUnits.at(0) -> getHitpoints());
  //push back the unit damage
  stats->push_back(currentUnits.at(0) -> getDamage());
  //push back the unit armor
  stats->push_back(currentUnits.at(0) -> getArmor());
  //push back the unit speed
  stats->push_back(currentUnits.at(0) -> getSpeed());
  //push back the unit armor penetration
  stats->push_back(currentUnits.at(0) -> getArmorPenetration());
  //push back the respawn speed
  stats->push_back(respawnSpeed);

  return stats;
}

/*
 * Setters below used to update the statistics of the units of this tower when
 * upgrading through the upgrade system
 */

 void MeleeTower::updateUnitHitpoints(int newMaxHitpoints){
   for(shared_ptr<MeleeUnit> unit : currentUnits){
     unit -> updateMaxHitpoints(newMaxHitpoints);
     if( unit ->getHitpoints() < 0){
       handleDeadUnit(0);
     }
   }
 }

 void MeleeTower::updateUnitDamage(int newDamage){
   for(shared_ptr<MeleeUnit> unit : currentUnits){
     unit -> updateDamage(newDamage);
   }
 }

 void MeleeTower::updateUnitArmorPenetration(int newArmorPenetration){
   for(shared_ptr<MeleeUnit> unit : currentUnits){
     unit -> updateArmorPenetration(newArmorPenetration);
   }
 }

 void MeleeTower::updateUnitArmor(int newArmor){
   for(shared_ptr<MeleeUnit> unit : currentUnits){
     unit -> updateArmor(newArmor);
   }
 }

 void MeleeTower::updateUnitAttackRate(int newAttackRate){
   for(shared_ptr<MeleeUnit> unit : currentUnits){
     unit -> updateAttackRate(newAttackRate);
   }
 }
