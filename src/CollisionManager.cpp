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

  //the actor that was created
  shared_ptr<ActorInterface> actorCreated = acEventData -> actorCreated;

  //the row and col of the actor
  int row = actorCreated -> getRow();
  int col = actorCreated -> getCol();

  if(isProjectile){

    //add it to the map of projectiles
    projectilesFired.insert({actorCreated->getID(), actorCreated});
  }
  else{
    //if this is an allied unit we place it in a map only for the allied units
    if(actorCreated->isAnAlly()){
      //the row and col the ally is currently at
      cout << "row " << actorCreated -> getRow() << " col " << actorCreated -> getCol() << endl;
      cout << "x pos " << actorCreated -> getXCoordinate() << " y " << actorCreated -> getYCoordinate() << endl;
      if(inMap(row,col)){
        int combinedRowCol = actorCreated -> getRow() * cols + actorCreated -> getCol();
        //if there is not a row, col stored then we need to set one up
        if(alliedUnits.find(combinedRowCol) == alliedUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          alliedUnits.insert({combinedRowCol, emptyMap});
        }
        alliedUnits.at(combinedRowCol).insert({actorCreated->getID(), actorCreated});
      }
    }
    else{
      //the row and col the enemy is currently at
      cout << "row en " << actorCreated -> getRow() << " col " << actorCreated -> getCol() << endl;
      cout << "x pos en " << actorCreated -> getXCoordinate() << " y " << actorCreated -> getYCoordinate() << endl;
      if(inMap(row,col)){
        int combinedRowCol = actorCreated -> getRow() * cols + actorCreated -> getCol();
        //if there is not a row, col stored then we need to set one up
        if(alliedUnits.find(combinedRowCol) == alliedUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          enemyUnits.insert({combinedRowCol, emptyMap});
        }
        enemyUnits.at(combinedRowCol).insert({actorCreated->getID(), actorCreated});
      }
    }
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

  shared_ptr<ActorInterface> actorDestroyed = adEventData -> actorDestroyed;

  //the row and col of the actor
  int row = actorDestroyed -> getRow();
  int col = actorDestroyed -> getCol();

  //we do not destroy it normally if it is not a projectile
  if(!(actorDestroyed->isAProjectile())){
    //if this is an allied unit we place it in a map only for the allied units
    if(actorDestroyed->isAnAlly()){
      //the row and col the ally is currently at
      cout << "row d" << actorDestroyed -> getRow() << " col " << actorDestroyed -> getCol() << endl;
      cout << "x pos d" << actorDestroyed -> getXCoordinate() << " y " << actorDestroyed -> getYCoordinate() << endl;
      if(inMap(row,col)){
        int combinedRowCol = actorDestroyed -> getRow() * cols + actorDestroyed -> getCol();

        alliedUnits.at(combinedRowCol).erase(actorDestroyed->getID());
      }
    }
    else{
      //the row and col the enemy is currently at
      cout << "row en d" << actorDestroyed -> getRow() << " col " << actorDestroyed -> getCol() << endl;
      cout << "x pos en d" << actorDestroyed -> getXCoordinate() << " y " << actorDestroyed -> getYCoordinate() << endl;
      if(inMap(row,col)){
        int combinedRowCol = actorDestroyed -> getRow() * cols + actorDestroyed -> getCol();
        alliedUnits.at(combinedRowCol).erase(actorDestroyed->getID());
      }
    }
  }

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
  //update the position of everything that can be moving
  updateAllUnitPositions();
}

/*
 * Update the position of all the units to reflect their current positions
 */
void CollisionManager::updateAllUnitPositions(){
  updateAllAllyUnitPositions();
  updateAllEnemyUnitPositions();
}

/*
 * Update the position of all units that are allies
 */
void CollisionManager::updateAllAllyUnitPositions(){
  //iterate through every row,col keyed map of units
  for(auto it : alliedUnits){
    int combinedRowCol = it.first;

    //iterate through each unit at the current row, col
    for(auto unitMap : it.second){
      shared_ptr<ActorInterface> alliedUnit = unitMap.second;

      int currentCombinedRowCol = alliedUnit->getRow() * cols + alliedUnit->getCol();

      //if the unit is no longer in the row, col pair then change its position in the map
      if(currentCombinedRowCol != combinedRowCol){
        alliedUnits.at(combinedRowCol).erase(alliedUnit->getID());

        //ensure that there is a new row,col pair map to place in
        if(alliedUnits.find(currentCombinedRowCol) == alliedUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          alliedUnits.insert({currentCombinedRowCol,emptyMap});
        }

        //place it at the new row, col pair
        alliedUnits.at(currentCombinedRowCol).insert({alliedUnit->getID(), alliedUnit});
      }
    }
  }
}

/*
 * Update the position of all units that are enemies
 */
void CollisionManager::updateAllEnemyUnitPositions(){
  //iterate through every row,col keyed map of units
  for(auto it : alliedUnits){
    int combinedRowCol = it.first;

    //iterate through each unit at the current row, col
    for(auto unitMap : it.second){
      shared_ptr<ActorInterface> enemyUnit = unitMap.second;

      int currentCombinedRowCol = enemyUnit->getRow() * cols + enemyUnit->getCol();

      //if the unit is no longer in the row, col pair then change its position in the map
      if(currentCombinedRowCol != combinedRowCol){
        enemyUnits.at(combinedRowCol).erase(enemyUnit->getID());

        //ensure that there is a new row,col pair map to place in
        if(enemyUnits.find(currentCombinedRowCol) == enemyUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          enemyUnits.insert({currentCombinedRowCol,emptyMap});
        }

        enemyUnits.at(currentCombinedRowCol).insert({enemyUnit->getID(), enemyUnit});
      }
    }
  }
}

/*
 * @return bool: whether this is in the map
 */
bool CollisionManager::inMap(int row, int col){
  if(row < 0 || row >= rows){
    return false;
  }
  if(col < 0 || col >= cols){
    return false;
  }
  return true;
}

/*
 * @return bool: whether this is in the window area
 */
bool CollisionManager::inMap(float x, float y){
  float windowX = rows * yTileSize;
  float windowY = cols * xTileSize;
  float e = 0.001;

  if(x < 0 || !(x <= windowX + e)){
    return false;
  }
  if(y < 0 || !(y <= windowY + e)){
    return false;
  }
  return true;
}
