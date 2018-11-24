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
}

MeleeTower::~MeleeTower(){
  this -> deregisterDelegates();
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
 * Initialize all the units that will spawn for this tower
 */
void MeleeTower::setUpUnits(){}

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
void MeleeTower::resetRallyPoint(int x, int y){
  //if this rally point is not in the prescribed radius around the tower
  if(x<xCoordinate-radius || x>xCoordinate+radius || y<yCoordinate-radius || y>yCoordinate+radius){
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


void MeleeTower::update(float delta){

}
