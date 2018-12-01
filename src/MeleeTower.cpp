#include "MeleeTower.hpp"
//empty constructor used for derived classes to call
MeleeTower::MeleeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  //all rally points initilaized to this number so that if we try to spawn them without
  //reseting the rally point they will not spawn
  this -> xRally = 0xFFFFFFFF;
  this -> yRally = 0xFFFFFFFF;
  this -> e = 0.00001;
  this -> timeOfDeath = {-1.0, -1.0, -1.0};
  this -> isMelee = true;
  this -> radiusVisible = false;
  this -> registerDelegates();
  this -> setToCenter();
}

MeleeTower::~MeleeTower(){
  this -> deregisterDelegates();
}

void MeleeTower::update(float delta){
  int unitIndex = 0;
  //if a unit does not have an engaged enemy unit then send it back towards
  //a point situated around the rally point
  for(shared_ptr<MeleeUnit> unit : currentUnits){
    if(unit -> getHitpoints() != 0){
      if((unit -> getEngagedUnit()).get() == NULL){
        //sets the unit position to the center of the tower if there is no set rally point
        //or moves it closer to the rally point position
        resetUnitPosition(unit, unitIndex);
      }
      else{
        //TODO move the unit towards the enemy unit (or attack if in contact)
      }

    }
    unitIndex++;
  }
}

/*
 * Initialize all the units that will spawn for this tower with a position
 */
void MeleeTower::setUpUnits(){
  for(int unitIndex = 0; unitIndex < currentUnits.size(); unitIndex++){
    currentUnits.at(unitIndex) -> setXCoordinate(xCoordinate);
    currentUnits.at(unitIndex) -> setYCoordinate(yCoordinate);
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
    float newX = (radiusOfUnitCircle) * xScale * cos(angle*unitIndex) + xRally;
    float newY = (radiusOfUnitCircle) * yScale * sin(angle*unitIndex) + yRally;

    cout << "for unit " << unitIndex << endl;
    cout << "go to x " << newX << " y " << newY << endl;

    //if the unit is already at its correct resting poisiton nothing needs to be done
    if(!(withinRange(newX, newY, unit->getXCoordinate(), unit->getYCoordinate()))){
      //the vector components of the movement this unit needs to make
      float xVector = newX - unit -> getXCoordinate();
      float yVector = newY - unit -> getYCoordinate();

      //the multipliers cooresponding to the movement of the unit in the direction of the desired position
      float xmult = cos(xVector);
      float ymult = sin(yVector);

      unit -> move(delta, xmult, ymult);

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
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  //set whatever time is in this space to the current time
  timeOfDeath.at(indexOfUnit) = nowInNano;
}

/*
 * Respawn any unit that is below 0 health that has a larger elapsed time
 * since it last died than the respawn Speed
 */
void MeleeTower::respawnUnits(){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  for(int index = 0; index < timeOfDeath.size(); index++){
    float deathTime = timeOfDeath.at(index);

    //if this is not a dead unit
    if(deathTime == -1.0){
      continue;
    }
    if(deathTime - e <= nowInNano && deathTime + e >= nowInNano){
      timeOfDeath.at(index) = -1.0;
      //set the health back to max
      currentUnits.at(index) -> resetHealth();

      //set the engaged unit to null
      currentUnits.at(index) -> setEngagedUnit(NULL);

      //set the position to be the center of the tower (so it will not draw and then start moving towards some other point)
      currentUnits.at(index) -> setXCoordinate(xCoordinate);
      currentUnits.at(index) -> setYCoordinate(yCoordinate);
    }
  }
}

/*
 * @return if there is any enemy unit within the radius ofthe tower
 */
bool MeleeTower::canAttack(){
  //TODO implement using box2D collision
}

/*
 * If we can attack then we check to see if a unit is not engaged or
 * is engaged with an enemy unit that is not also engaged with it
 */
void MeleeTower::attack(shared_ptr<ActorInterface> enemyInRange){

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
