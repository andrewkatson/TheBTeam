#include "CollisionManager.hpp"


CollisionManager::CollisionManager(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager,
  shared_ptr<WaveManager> waveManager,
  shared_ptr<ProjectileManager> projectileManager){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> waveManager = waveManager;
  this -> projectileManager = projectileManager;
  registerDelegates();
}

CollisionManager::~CollisionManager(){
  deregisterDelegates();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void CollisionManager::registerDelegates(){
  //bind our delegate function for tower creation events
  EventManager::EventDelegate towerCreationEventDelegate = std::bind(&CollisionManager::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerCreationEventDelegate, textLoader -> getString(string("IDS_Collision_Manager_Tower_Creation")),towerCreationEventType);

  //bind our delegate function for tower remove events
  EventManager::EventDelegate towerRemoveEventDelegate = std::bind(&CollisionManager::handleTowerRemove, this, _1);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerRemoveEventDelegate, textLoader -> getString(string("IDS_Collision_Manager_Tower_Remove")),towerRemoveEventType);

  //bind our delegate function for actor creations (specifically projectiles)
  EventManager::EventDelegate actorCreatedDelegate = std::bind(&CollisionManager::handleActorCreated, this, _1);

  //make an event and get its type
  ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
  EventType actorCreatedEventType = actorCreatedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorCreatedDelegate, textLoader -> getString(string("IDS_Collision_Manager_Actor_Creation")),actorCreatedEventType);

  //bind our delegate function for actor destructions (specifically projectiles)
  EventManager::EventDelegate actorDestroyedDelegate = std::bind(&CollisionManager::handleActorDestroyed, this, _1);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorDestroyedDelegate, textLoader -> getString(string("IDS_ProjectileManager_ActorCreated")),actorDestroyedEventType);
}


/*
 * Deregister all event delegates for this class
 */
void CollisionManager::deregisterDelegates(){
  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Collision_Manager_Tower_Creation")),towerCreationEventType);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Collision_Manager_Tower_Remove")),towerRemoveEventType);

  //make an event and get its type
  ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
  EventType actorCreatedEventType = actorCreatedEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate( textLoader -> getString(string("IDS_Collision_Manager_Actor_Creation")),actorCreatedEventType);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Collision_Manager_Actor_Destroy")),actorDestroyedEventType);
}

/*
 * Handle a tower creation event
 * @param event: the tower creation event
 */
void CollisionManager::handleTowerCreation(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * TowerCreationEvent type which allows us to access variables and methods
   * specific to TowerCreationEvent
   */
  const TowerCreationEvent* tcEvent = static_cast<const TowerCreationEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a TowerCreationEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  TowerCreationEventData* tcEventData = static_cast<TowerCreationEventData*>((tcEvent -> data).get());
  //get the tower id
  int towerPosID = tcEventData -> towerPosID;
  //get the type of the tower (an index corresponding to a type in towersToChoose)
  string towerTypeID = tcEventData -> towerTypeID;

  //decode the ID so that it is a row and column
  int row = towerPosID / cols;
  int col = towerPosID % cols;

}

/*
 * Handle a tower remove event
 * @param event: the tower remove event
 */
void CollisionManager::handleTowerRemove(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * TowerRemoveEvent type which allows us to access variables and methods
   * specific to TowerRemoveEvent
   */
  const TowerRemoveEvent* trEvent = static_cast<const TowerRemoveEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a TowerRemoveEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  TowerRemoveEventData* trEventData = static_cast<TowerRemoveEventData*>((trEvent -> data).get());
  //get the tower id
  int towerPosID = trEventData -> towerPosID;

  //decode the ID so that it is a row and column
  int row = towerPosID / cols;
  int col = towerPosID % cols;

}

void CollisionManager::handleActorCreated(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * ActorCreatedEvent type which allows us to access variables and methods
   * specific to ActorCreatedEvent
   */
  const ActorCreatedEvent* acEvent = static_cast<const ActorCreatedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a ActorCreatedEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  ActorCreatedEventData* acEventData = static_cast<ActorCreatedEventData*>((acEvent -> data).get());
  //get the identifier for whether this is a projectile or not
  bool isProjectile = acEventData -> isProjectile;

  if(isProjectile){
    //the projectile that was created
    shared_ptr<ActorInterface> firedProjectile = acEventData -> actorCreated;

  }
}

void CollisionManager::handleActorDestroyed(const EventInterface& event){
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
  //get the id of the actor to check if it was a projectile
  long long actorDestroyedID = adEventData -> actorID;

}

/*
 * Set the size of a row and col in pixels
 */
void CollisionManager::setGridDimensions(float x, float y){
  xTileSize = x;
  yTileSize = y;
}

/*
 * Set the dimensions of the grid
 */
void CollisionManager::setDimensions(int rows, int cols){
  this -> rows = rows;
  this -> cols = cols;
}

/*
 * Store a new tower created and store it after determining its location
 */
void CollisionManager::addNewTower(shared_ptr<TowerInterface> tower){

}

/*
 * Remove a tower stored in the list of collisions using its location and radius to determine what
 * cells in the unordered map it is part of
 */
void CollisionManager::removeOldTower(shared_ptr<TowerInterface> tower){

}

/*
 * Check for collisions between all objects within the same row, col
 */
void CollisionManager::checkForCollisions(){

}
