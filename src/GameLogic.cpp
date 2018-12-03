/*
  GameLogic.cpp

  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */
#include "GameLogic.hpp"

//Constructor.
GameLogic::GameLogic(shared_ptr<TextLoader> textLoader, int windowX, int windowY,
  shared_ptr<TextureLoader> textureLoader,shared_ptr<b2World> world){
  this -> textLoader = textLoader;
  this -> textureLoader = textureLoader;
  this -> world = world;
  this -> eventManager = make_shared<EventManager>();
  this -> boardManager = unique_ptr<BoardManager>(new BoardManager(eventManager, textLoader));
  this -> gameState = unique_ptr<GameState>(new GameState(eventManager, textLoader));
  this -> player = unique_ptr<Player>(new Player(eventManager, textLoader));
  this -> soundManager = unique_ptr<SoundManager>(new SoundManager(eventManager, textLoader));
  this -> waveManager = make_shared<WaveManager>(eventManager, textLoader, textureLoader,windowX,windowY,player->getLevel(),player->getSchool(),world);
  this -> projectileManager = make_shared<ProjectileManager>(eventManager, textLoader, world);
  this -> collisionManager = make_shared<CollisionManager>(textLoader, eventManager, waveManager, projectileManager);
  this -> towerManager = make_shared<TowerManager>(eventManager, textLoader, textureLoader, world, collisionManager);
  this -> registerEvents();
  this -> registerDelegates();
  test = 5;
  this -> windowX = windowX;
  this -> windowY = windowY;
}

/*
 * any events created by this class must be registered with the
 * Event Manager
 */
 void GameLogic::registerEvents(){
   //make a generic tower creation event, get its type, and register it
   TowerCreationEvent towerCreationEvent = TowerCreationEvent();
   EventType towerCreationEventType = towerCreationEvent.getEventType();

   this -> eventManager -> registerEvent(towerCreationEventType);

   //make a generic tower remove event, get its type, and register it
   TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
   EventType towerRemoveEventType = towerRemoveEvent.getEventType();

   this -> eventManager -> registerEvent(towerRemoveEventType);

   //make a generic map generated event, get its type, and register it
   MapGeneratedEvent mapGeneratedEvent = MapGeneratedEvent();
   EventType mapGeneratedEventType = mapGeneratedEvent.getEventType();

   this -> eventManager -> registerEvent(mapGeneratedEventType);

   //make a projectile explosion event, get its type, and register it
   ProjectileExplosionEvent projectileExplosionEvent = ProjectileExplosionEvent();
   EventType projectileExplosionEventType = projectileExplosionEvent.getEventType();

   this -> eventManager -> registerEvent(projectileExplosionEventType);

   //make a actor destroyed event, get its type, and register it
   ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
   EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();

   this -> eventManager -> registerEvent(actorDestroyedEventType);
 }

 GameLogic::~GameLogic(){
   this -> deregisterDelegates();
 }

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void GameLogic::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&GameLogic::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_GLD_KP")),keyPressEventType);
  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&GameLogic::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_GLD_MP")),mousePressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate stateChangeDelegate = std::bind(&GameLogic::handleStateChange, this, _1);

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(stateChangeDelegate, textLoader -> getString(string("IDS_GLD_SC")),stateChangeEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate projectileExplosionEventDelegate = std::bind(&GameLogic::handleProjectileExplosion, this, _1);

  //make an event and get its type
  ProjectileExplosionEvent projectileExplosionEvent = ProjectileExplosionEvent();
  EventType projectileExplosionEventType = projectileExplosionEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(projectileExplosionEventDelegate, textLoader -> getString(string("IDS_GameLogic_Delegate_Projectile_Explosion")),projectileExplosionEventType);

}

/*
 * Deregister all event delegates for this class
 */
void GameLogic::deregisterDelegates(){
  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_GLD_KP")),keyPressEventType);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_GLD_MP")),mousePressEventType);

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_GLD_SC")),stateChangeEventType);

  //make an event and get its type
  ProjectileExplosionEvent projectileExplosionEvent = ProjectileExplosionEvent();
  EventType projectileExplosionEventType = projectileExplosionEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_GameLogic_Delegate_Projectile_Explosion")),projectileExplosionEventType);
}


//Called once every loop. Update according to elapsed time.
void GameLogic::updateGameLogic(float deltaS){
  if(getGameState()==State::Playing){
    this -> waveManager -> update(deltaS);
  }

  this -> eventManager -> processEvent();
  //cout << "oh boy " << fryID << endl;
  if(boardManager -> hasMap()){
    int row = 3;
    int col = 3;
    if(test == 5){
      //creates a unit for testing as well
      // shared_ptr<MeleeUnit> fryGuy = make_shared<NormalFryUnit>(textLoader, eventManager, textureLoader);
      // shared_ptr<MeleeUnit> fryGuy1 = make_shared<NormalFryUnit>(textLoader, eventManager, textureLoader);
      // fryGuy -> setWorld(world);
      // fryGuy1 -> setWorld(world);
      // fryGuy -> setFixtures();
      // fryGuy1 -> setFixtures();
      //
      // fryID = fryGuy -> getID();
      // fryID1 = fryGuy1 -> getID();

      //set the x and y coordinates
      // fryGuy -> setXCoordinate(3 * gridX);
      // fryGuy -> setYCoordinate(2 * gridY);
      // fryGuy1 -> setXCoordinate(3 * gridX);
      // fryGuy1 -> setYCoordinate(2 * gridY);

      //add to the current wave of spawned
      //something something idiot
      //(waveManager -> spawnedCurrentWave).insert({fryGuy -> getID(), fryGuy});
      //(waveManager -> spawnedCurrentWave).insert({fryGuy1 -> getID(), fryGuy1});

      //vector<shared_ptr<TowerInterface>> allTowers = allUpgradesForTower(row, col);

      // if(allTowers.size() != 0){
      //   shared_ptr<TowerInterface> tower = allTowers.at(0);
      //   tower -> setWorld(world);
      //   string towerType = tower -> getType();
      //   if(canBuy(towerType) && !(boardManager->isObstacle(row,col))){
      //     createATower(row,col,towerType);
      //     test++;
      //   }
      //   else if(canBuy(towerType) && boardManager -> isObstacle(row,col)){
      //     removeATower(row,col);
      //     cout << "removed an obstacle" << endl;
      //     test -=2;
      //   }
      // }

    }
    if(test == 2){
      /*
      //get all the spawned units
      unordered_map<long long, shared_ptr<MeleeUnit>> spawnedWave = getSpawnedEnemyUnits();

      cout << "size " << spawnedWave.size() << endl;
      cout << "fry id now " << fryID << endl;

      //get our fry guy
      shared_ptr<MeleeUnit> fryGuy = spawnedWave.at(fryID);

      //rotate fry
      sf::Sprite sp = fryGuy -> getSprite();

      //get the tower
      unordered_map<int, shared_ptr<TowerInterface>> towers = towerManager -> getTowersPlaced();

      cout << "tower num " << towers.size() << endl;
      cout << "check placed " << row*getCols() + col << endl;

      shared_ptr<TowerInterface> towerToFire = towers.at(row*getCols() + col);

      towerToFire -> attack(fryGuy);

      cout << "where is this tower " << endl;
      cout << towerToFire -> getXCoordinate() << endl;
      cout << towerToFire -> getYCoordinate() << endl;
      */
    }
    if(test == 10){
      cout << "is there a tower now? " << boardManager -> isTower(row, col) << endl;
      cout << (boardManager -> getAboveFloor()).at(row).at(col) << endl;
      if(boardManager -> isTower(row, col)){
        removeATower(row,col);
      }
    }
    test-=2;
  }

}
/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void GameLogic::handleKeyPress(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * KeyPressEvent type which allows us to access variables and methods
   * specific to KeyPressEvent
   */
  const KeyPressEvent* kpEvent = static_cast<const KeyPressEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a KeyPressEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  KeyPressEventData* kpEventData = static_cast<KeyPressEventData*>((kpEvent -> data).get());
  //get the key string identifier from the data
  string key = kpEventData -> keyID;
  if(key == "CLOSE"){
    shutDown();
  }
  else if(key == "Q"){
    shutDown();
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void GameLogic::handleMousePress(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * MousePressEvent type which allows us to access variables and methods
   * specific to MousePressEvent
   */
  const MousePressEvent* mpEvent = static_cast<const MousePressEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a KeyPressEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  MousePressEventData* mpEventData = static_cast<MousePressEventData*>((mpEvent -> data).get());
  //get the xposition
  float xPos = mpEventData -> x;
  //get the y position
  float yPos = mpEventData -> y;
}

/*
 * Handle a state change
 * @param event: event of the state change (i.e. play to options )
 */
void GameLogic::handleStateChange(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * StateChangeEvent type which allows us to access variables and methods
   * specific to StateChangeEvent
   */
  const StateChangeEvent* scEvent = static_cast<const StateChangeEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a StateChangeEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  StateChangeEventData* scEventData = static_cast<StateChangeEventData*>((scEvent -> data).get());
  //get integer of the state change
  State state = scEventData -> state;

  //set the current state to be the state changed
  gameState -> setState(state);

  //if the state is playing we generate a new map
  //only if one is not currently existing
  if(!(boardManager -> hasMap()) && State::Playing == state){
    makeNewMap();
  }
}

/*
 * Handle a projectile explosion
 * @param event: the event of the projectile explosion
 */
 void GameLogic::handleProjectileExplosion(const EventInterface& event){
   /*
    * cast the EventInterface reference to a CONST pointer to the
    * ProjectileExplosionEvent type which allows us to access variables and methods
    * specific to ProjectileExplosionEvent
    */
   const ProjectileExplosionEvent* peEvent = static_cast<const ProjectileExplosionEvent*>(&event);
   /*
    * cast the "data" (a EventDataInterface) to a ProjectileExplosionEventData type
    * the .get() is because data is a unique_ptr and we need to grab the
    * raw pointer inside of it for this
    */
   ProjectileExplosionEventData* peEventData = static_cast<ProjectileExplosionEventData*>((peEvent -> data).get());
   //get id for the projectile that exploded
   long long projectileExplodedID = peEventData -> projectileID;

   //setting fixtures for projectiles
   shared_ptr<ActorInterface> projectile = projectileManager -> getProjectile(projectileExplodedID);
   Projectile* newProjectile = dynamic_cast<Projectile*>(projectile.get());
   //newProjectile -> setFixtures();


   //now create an event to indicate the projectile was destroyed
   //the time object of the class
   auto now = high_resolution_clock::now();
   //the actual count in nanoseconds for the time
   auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

   //make event
   shared_ptr<EventInterface> projectileDestroyed = make_shared<ActorDestroyedEvent>(projectileExplodedID, nowInNano);

   this -> eventManager -> queueEvent(projectileDestroyed);
 }

/*
 * Have a new map generated (callable by the UserView)
 */
 void GameLogic::makeNewMap(){
   //make the new map
   this -> boardManager -> newMap();

   //set the dimensions (x are cols, y are rows of the map)
   int xDim = boardManager -> getXDim();
   int yDim = boardManager -> getYDim();
   this -> towerManager -> setDimensions(xDim, yDim);
   this -> collisionManager -> setDimensions(xDim, yDim);
   this -> waveManager -> setDimensions(xDim, yDim);

   //set the x and y in pixel length
   this -> gridX = (float) windowX / boardManager -> getXDim();
   this -> gridY = (float) windowY / boardManager -> getYDim();
   this-> towerManager -> setGridDimensions(gridX, gridY);
   this -> collisionManager -> setGridDimensions(gridX, gridY);
   this -> waveManager -> setGridDimensions(gridX, gridY);

   //make a map generated event
   //the time object of the class
   auto now = high_resolution_clock::now();
   //the actual count in nanoseconds for the time
   auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

   shared_ptr<EventInterface> mapGenerated = make_shared<MapGeneratedEvent>(nowInNano,boardManager->getDistances(),boardManager->getEntryPositions());

   this -> eventManager -> queueEvent(mapGenerated);

   placeObstacles();

   ActorInterface::setXScale(boardManager -> getXDim());
   ActorInterface::setYScale(boardManager -> getYDim());
 }

/*
 * Send the list of obstacles and their types from the
 * board manager to the tower manager for their creation
 */
void GameLogic::placeObstacles(){
  //an unordered map where the type of the obstacle is the key
  //and the position is a pair
  unordered_map<int, intPair> obstacleValueToPos;
  obstacleValueToPos = boardManager -> getAllObstacles();

  towerManager -> addObstacles(obstacleValueToPos);
}


//return a reference to the event manager
shared_ptr<EventManager> GameLogic::getEventManager(){
  return this -> eventManager;
}

/*
 * Return a vector with all the towers that can be used to upgrade
 * @param row: the row of the tower
 * @param col: the col of the tower
 */
vector<shared_ptr<TowerInterface>>& GameLogic::allUpgradesForTower(int row, int col){
  static vector<shared_ptr<TowerInterface>> noTowers;
  //return an empty vector if the space is a path, exit, or an obstacle
  if(boardManager -> isExit(row,col)){
    return noTowers;
  }
  if(boardManager -> isPath(row,col)){
    return noTowers;
  }
  //if there is an obstacle here than we want the obstacle
  //because we are just trying to remove it
  if(boardManager -> isObstacle(row,col)){
    return towerManager -> getObstacleAsVector(row,col);
  }

  shared_ptr<TowerInterface> tower = towerManager -> getTowerPlaced(row,col);

  string towerID = tower -> getType();

  //if the current tower is no tower than we do not need to modify the statistics at all
  if(tower -> getType() == textLoader->getTypeID(string("IDS_NT"))){
    return towerManager->getUpgradesForTower(towerID);
  }
  //otherwise we need to modify the statistics of these towers to reflect the player purchased upgrades
  else{
    modifyToIncludeUpgrades(towerManager->getUpgradesForTower(towerID), tower);
    return towerManager->getModifiedUpgrades();
  }
}

/*
 * @param towerUpgrades: all the possible upgrades for the tower at the position to consider
 * @param tower: the tower we will be upgrading
 */
void GameLogic::modifyToIncludeUpgrades(vector<shared_ptr<TowerInterface>>& towerUpgrades, shared_ptr<TowerInterface> tower){

  //get a generic copy of this tower to measure the amount its variables have been changed
  shared_ptr<TowerInterface> genericTowerOfType = towerManager -> getGenericTower(tower->getType());


  //first we need to determine if this is a melee tower or a range tower we are upgrading
  if(tower -> isMelee){
    //cast the towers to their correct type
    MeleeTower* genericMelee = dynamic_cast<MeleeTower*>(genericTowerOfType.get());
    MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(tower.get());

    //get the difference between the generic type and the current tower (i.e. the amount the tower was upgraded)
    int respawnSpeedUpgrades = meleeTower->getRespawnSpeed()-genericMelee->getRespawnSpeed();
    int respawnRangeUpgrades = meleeTower->getRadius()-genericMelee->getRadius();
    int unitMaxHitpointsUpgrades = meleeTower->getUnitHitpoints()-genericMelee->getUnitHitpoints();
    int unitDamageUpgrades = meleeTower->getUnitDamage()-genericMelee->getUnitDamage();
    int unitArmorPenetrationUpgrades = meleeTower->getUnitArmorPenetration()-genericMelee->getUnitArmorPenetration();
    int unitArmorUpgrades = meleeTower->getUnitArmor()-genericMelee->getUnitArmor();
    int unitAttackRateUpgrades = meleeTower->getUnitAttackRate()-genericMelee->getUnitAttackRate();

    //modify each tower upgrades statisitcs to reflect the purchased upgrades
    for(shared_ptr<TowerInterface> towerUpgrade : towerUpgrades){
      //cast the tower
      MeleeTower* towerToUpgrade = dynamic_cast<MeleeTower*>(towerUpgrade.get());

      //set all statistics to be the old statistic plus the upgrades
      towerToUpgrade->updateRespawnSpeed(towerToUpgrade->getRespawnSpeed()+respawnSpeedUpgrades);
      towerToUpgrade->updateRadius(towerToUpgrade->getRadius()+respawnRangeUpgrades);
      towerToUpgrade->updateUnitHitpoints(towerToUpgrade->getUnitHitpoints()+unitMaxHitpointsUpgrades);
      towerToUpgrade->updateUnitDamage(towerToUpgrade->getUnitDamage()+unitDamageUpgrades);
      towerToUpgrade->updateUnitArmorPenetration(towerToUpgrade->getUnitArmorPenetration()+unitArmorPenetrationUpgrades);
      towerToUpgrade->updateUnitArmor(towerToUpgrade->getUnitArmor()+unitArmorUpgrades);
      towerToUpgrade->updateUnitAttackRate(towerToUpgrade->getUnitAttackRate()+unitAttackRateUpgrades);
    }

  }
  else{
    RangeTower* genericRanged = dynamic_cast<RangeTower*>(genericTowerOfType.get());
    RangeTower* rangeTower = dynamic_cast<RangeTower*>(tower.get());

    //get the difference between the generic type and the current tower (i.e. the amount the tower was upgraded)
    int rateOfFireUpgrades = rangeTower -> getRateOfFire()-genericRanged->getRateOfFire();
    int rangeOfFireUpgrades = rangeTower->getRadius()-genericRanged->getRadius();
    int projectileDamageUpgrades = rangeTower->getProjectileDamage()-genericRanged->getProjectileDamage();
    int projectileArmorPenetrationUpgrades = rangeTower->getProjectileArmorPenetration()-genericRanged->getProjectileArmorPenetration();
    int projectileAreaOfEffectUpgrades = rangeTower->getProjectileAreaOfEffect()-genericRanged->getProjectileAreaOfEffect();

    //modify each tower upgrades statisitcs to reflect the purchased upgrades
    for(shared_ptr<TowerInterface> towerUpgrade : towerUpgrades){
      //cast the tower
      RangeTower* towerToUpgrade = dynamic_cast<RangeTower*>(towerUpgrade.get());

      //set all statitics to be theold statistic plus the upgrades
      towerToUpgrade->updateRateOfFire(towerToUpgrade->getRateOfFire()+rateOfFireUpgrades);
      towerToUpgrade->updateRadius(towerToUpgrade->getRadius()+rangeOfFireUpgrades);
      towerToUpgrade->updateProjectileDamage(towerToUpgrade->getProjectileDamage()+projectileDamageUpgrades);
      towerToUpgrade->updateProjectileArmorPenetration(towerToUpgrade->getProjectileArmorPenetration()+projectileArmorPenetrationUpgrades);
      towerToUpgrade->updateProjectileAreaOfEffect(towerToUpgrade->getProjectileAreaOfEffect()+projectileAreaOfEffectUpgrades);
    }
  }
}

/*
 * Attempt a purchase of a tower at a particular location
 * @param row: the row of the tile
 * @param col: the col of the tile
 * @param towerTypeID: the string identifier of the tower
 * @return bool: whether they were successful or not
 */
bool GameLogic::attemptPurchaseTower(int row, int col, string towerTypeID){

  //if we canbuy a tower/obstacle of this type
  if(canBuy(towerTypeID)){
    //create a tower if this is a tower
    if(boardManager -> isTower(row,col) || boardManager -> isEmptySpace(row,col)){
      createATower(row, col, towerTypeID);
    }
    //use a remove tower event if this is an obstacle
    if(boardManager -> isObstacle(row,col)){
      removeATower(row,col);
    }
    return true;
  }
  //return false in case we want the buy tower screen to make an indication of failure
  else{
    return false;
  }
}

/*
 * Attempt a sale of a tower at a particular location
 * @param row: the row of the tile
 * @param col: the col of the tile
 * @return bool: whether they were successful or not
 */
bool GameLogic::attemptSellTower(int row, int col){

   if(boardManager -> isTower(row,col)){
      removeATower(row, col);
      return true;
  }

  //return false in case we want the buy tower screen to make an indication of failure
  else{
    return false;
  }
}

/*
 * Try to see if the tower at this position can have a statistic upgraded
 * @param row: the row of the tower
 * @param col: the col of the tower
 * @return bool: whether we can upgrade a statistic
 */
 bool GameLogic::canUpgradeTowerStats(int row, int col){
   assert(isTower(row,col));

   //the price for an upgrade
   int upgradeCost = getUpgradePrice(row, col);

   int playerBalance = player -> getBalance();

   if(playerBalance >= upgradeCost){
     return true;
   }
   return false;
 }


/*
 * @param row: the row of the target
 * @param col: the col of the target
 * @return whether the user can buy the obstacle/tower at the space selected
 */
bool GameLogic::canBuy(int row, int col){
  bool isExit = (boardManager -> isExit(row,col));
  //check if this is not the exit
  if(isExit){
    return false;
  }

  bool isPath = (boardManager -> isPath(row,col));
  //check if this is not on a path
  if(isPath){
    return false;
  }
  //return whether the obstacle/tower at this position is too expensive
  bool tooExpensive = towerManager -> getTowerPrice(row,col) <= player -> getBalance();

  return tooExpensive;
}

/*
 * @param towerType: the tower type to be created
 * @return whether the user can buy the obstacle/tower at the space selected
 */
bool GameLogic::canBuy(string towerType){
  //return whether the obstacle/tower at this position is too expensive
  bool tooExpensive = towerManager -> getTowerPrice(towerType) <= player -> getBalance();
  return tooExpensive;
}

/*
 * make a tower creation event
 * @param row: the row of the target
 * @param col: the col of the target
 * @param towerType: the type of the tower to be created
 */
void GameLogic::createATower(int row, int col, string towerType){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  int combinedRowCol = row*(boardManager -> getXDim()) + col;

  shared_ptr<EventInterface> tcEvent = make_shared<TowerCreationEvent>(combinedRowCol, towerType, nowInNano);

  //handle the money change from buying this tower
  createATowerMoney(towerType);

  this -> eventManager -> queueEvent(tcEvent);
}

/*
 * When a tower is purchased we deduct the monetary value
 * from the player's total money
 * @param tower: the tower created
 */
void GameLogic::createATowerMoney(string towerType){
  //get the price of the tower
  int price = towerManager -> getTowerPrice(towerType);

  //remove money equal to the tower's price
  player -> modifyBalance(price*-1);

}

/*
 * Sell tower at this position and create a removeTower event
 * @param row: row index of tower
 * @param col: the col index of tower
 */
void GameLogic::removeATower(int row, int col){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  int combinedRowCol = row*(boardManager -> getXDim()) + col;

  shared_ptr<EventInterface> trEvent = make_shared<TowerRemoveEvent>(combinedRowCol,  nowInNano);

  //if we remove a tower then we have to return a percentage of the
  //money from the tower to the player
  if(boardManager -> isTower(row, col)){
    removeATowerMoney(row, col);
  }
  //if the thing removed is an obstacle then
  //we have to remove money equal to the obstalces price
  else if(boardManager->isObstacle(row,col)){
    removeAObstacleMoney(row,col);
  }


  this -> eventManager -> queueEvent(trEvent);
}

/*
 * If a tower is removed we return a percentage of the money to the player
 * @param row: the row index of the tower
 * @param col: the col index of the tower
 */
void GameLogic::removeATowerMoney(int row, int col){
  //grab the tower at the position
  shared_ptr<TowerInterface> tower = towerManager -> getTowerPlaced(row,col);

  //get the price of the tower
  int price = tower -> getPrice();

  //get the percentage modifier for how much money is returned to the player
  double percentage = textLoader -> getDouble(string("IDS_Percentage_Money_Returned_On_Sell_Tower"));

  //add a percentage of this money back to the player's account
  player -> modifyBalance(price*percentage);
}

/*
 * If an obstacle is removed we take money from the player equal to the
 * price of the obstacle
 * @param row: the row index of the obstacle
 * @param col: the col index of the obstacle
 */
void GameLogic::removeAObstacleMoney(int row, int col){
  //grab the obstacle at the position
  shared_ptr<TowerInterface> obstacle = towerManager -> getTowerPlaced(row,col);

  //get the price of the tower
  int price = obstacle -> getPrice();

  //add a percentage of this money back to the player's account
  player -> modifyBalance(price*-1);
}

/*
 * @return the price of an upgrade for the tower at the passed position
 */
int GameLogic::getUpgradePrice(int row, int col){
  return towerManager->getUpgradePrice(row,col);
}


/*
 * Upgrade the tower at this row and col
 * @param upgradeButtonID: the id of the upgrade button that was selected
 */
void GameLogic::upgradeTower(string upgradeButtonID, int row, int col){
  //get the upgrade price
  int priceOfUpgrade = getUpgradePrice(row,col);

  //update the balance to reflect the purchase
  player -> modifyBalance(priceOfUpgrade * -1);

  towerManager -> upgradeTower(upgradeButtonID, row, col);
}


/*```
 * Return the current GameState
 */
State GameLogic::getGameState(){
  return gameState -> getState();
}

/*
 * Handle any cleanup required for shutting down the game
 */
void GameLogic::shutDown(){

}

/*
 * Get the grid showing the floor
 */
const vector<vector<int>>& GameLogic::getFloor(){
  return boardManager -> getFloor();
}

/*
 * Get the grid showing anything placed above the floor (i.e. obstacles and towers)
 */
const vector<vector<int>>& GameLogic::getAboveFloor(){
  return boardManager -> getAboveFloor();
}

/*
 * Get the grid showing the distance from any cell to the exit
 */
const vector<vector<int>>& GameLogic::getDistances(){
  return boardManager -> getDistances();
}

/*
 * @return if the row, col passed has a tower
 */
bool GameLogic::isTower(int row, int col){
  return boardManager -> isTower(row,col);
}

/*
 * @return if the row, col passed has an obstacle
 */
bool GameLogic::isObstacle(int row, int col){
  return boardManager -> isObstacle(row, col);
}

/*
 * @return if the row, col is an empty space (no path, or exit)
 */
bool GameLogic::isEmptySpace(int row, int col){
  return boardManager->isEmptySpace(row, col);
}

/*
 * @return if the row, col is an exit
 */
bool GameLogic::isExit(int row, int col){
  return boardManager -> isExit(row,col);
}

/*
 * @return if row, col is a path tile
 */
bool GameLogic::isPath(int row, int col){
  return boardManager -> isPath(row, col);
}

/*
 * Get the x size of a tile on the map
 */
const float GameLogic::getTileXSize(){
  return gridX;
}

/*
 * Get the y size of a tile on the map
 */
const float GameLogic::getTileYSize(){
  return gridY;
}

/*
 * Get the rows on the board
 */
const int GameLogic::getRows(){
  return boardManager -> getYDim();
}

/*
 * Get the cols on the board
 */
const int GameLogic::getCols(){
  return boardManager -> getXDim();
}

/*
 * Get the size in the x direction of the window
 */
const int GameLogic::getWindowX(){
  return windowX;
}

/*
 * Get the size in the y direction of the window
 */
const int GameLogic::getWindowY(){
  return windowY;
}

/*
 * @return Player: the current statistics of the player
 */
Player& GameLogic::getPlayer(){
  return *(player.get());
}


/*
 * @return MapChoices: all customizaton options for this map
 */
const MapChoices& GameLogic::getMapCustomizationChoices(){
  return boardManager -> getMapCustomizationChoices();
}

/*
 * @return a pointer to the tower placed at the specified position on the board
 */
const shared_ptr<TowerInterface> GameLogic::getTowerPlaced(int row, int col){
  return towerManager->getTowerPlaced(row,col);
}

/*
 * @return the unordered map of all the towers placed on the board
 */
const unordered_map<int, shared_ptr<TowerInterface>>& GameLogic::getTowersPlaced(){
  return towerManager -> getTowersPlaced();
}

/*
 * @return the vector with all the currently spawned enemy units on the board
 */
const unordered_map<long long,shared_ptr<MeleeUnit>>& GameLogic::getSpawnedEnemyUnits(){
  return waveManager -> getSpawnedEnemyUnits();
}

/*
 * @return the vector with all the currently fired projectiles
 */
unordered_map<long long, shared_ptr<ActorInterface>>& GameLogic::getFiredProjectiles(){
  return projectileManager -> getAllProjectiles();
}
