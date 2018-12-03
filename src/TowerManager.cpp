#include "TowerManager.hpp"

/*
 * Constructor for a tower manager
 * @param eventManager: the event manager class that directs events
 */
TowerManager::TowerManager(shared_ptr<EventManager> eventManager,
  shared_ptr<TextLoader> textLoader, shared_ptr<TextureLoader> textureLoader,
  shared_ptr<b2World> world,shared_ptr<CollisionManager> collisionManager) : mt(std::random_device()()) {
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> textureLoader = textureLoader;
  this -> collisionManager = collisionManager;
  this -> world = world;
  this -> registerDelegates();
  this -> populateObstacles();
  this -> populateTowersToChoose();
}

TowerManager::~TowerManager(){
  this -> deregisterDelegates();
}

/*
 * Set the x dimension (cols)
 * and the y dimension (rows)
 */
void TowerManager::setDimensions(int xDim, int yDim){
  this -> xDim = xDim;
  this -> yDim = yDim;
}
/*
 * Set the x size in pixels of a grid space
 * Set they size in pixels of a grid space
 */
void TowerManager::setGridDimensions(float xGrid, float yGrid){
  this -> xGrid = xGrid;
  this -> yGrid = yGrid;
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void TowerManager::registerDelegates(){
  //bind our delegate function for tower creation events
  EventManager::EventDelegate towerCreationEventDelegate = std::bind(&TowerManager::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerCreationEventDelegate, textLoader -> getString(string("IDS_TMD_TC")),towerCreationEventType);

  //bind our delegate function for tower remove events
  EventManager::EventDelegate towerRemoveEventDelegate = std::bind(&TowerManager::handleTowerRemove, this, _1);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerRemoveEventDelegate, textLoader -> getString(string("IDS_TMD_TR")),towerRemoveEventType);
}

/*
 * Deregister all the event delegates for this class
 */
void TowerManager::deregisterDelegates(){
  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_TMD_TC")),towerCreationEventType);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_TMD_TR")),towerRemoveEventType);
}

/*
 * Add all obstacles to the vector of possible towers
 */
void TowerManager::populateObstacles(){
  //get the identifier for each type of obstacle
  string cafeteriaTableID = textLoader ->  getTypeID("IDS_CTO");
  string trashCanID = textLoader -> getTypeID("IDS_TCO");

  //make a pointer to each type of obstacle
  shared_ptr<Obstacle> cafeteriaTable = make_shared<CafeteriaTable>(textLoader, eventManager, textureLoader);
  shared_ptr<Obstacle> trashCan = make_shared<TrashCan>(textLoader, eventManager, textureLoader);

  //all the obstacles serve as their own upgrade
  //used to give obstacles compatability in situations where
  //you want what can be bought at a tile and it can be nothing, a tower, or an obstacle
  vector<shared_ptr<TowerInterface>> allCafeteriaTableUpgrades;
  allCafeteriaTableUpgrades.push_back(cafeteriaTable);
  vector<shared_ptr<TowerInterface>> allTrashCanUpgrades;
  allTrashCanUpgrades.push_back(trashCan);

  //add the towers to tower upgrades
  allTowerUpgrades.insert({cafeteriaTableID, allCafeteriaTableUpgrades});
  allTowerUpgrades.insert({trashCanID, allTrashCanUpgrades});

  //add the obstacles  to towers types
  allTowerTypes.insert({cafeteriaTableID, cafeteriaTable});
  allTowerTypes.insert({trashCanID, trashCan});
}

/*
 * Add all the basic towers to the map of possible tower upgrades
 * keyed on the not a tower. and add them to the list of
 * placeable towers
 */
void TowerManager::populateTowersToChoose(){

  //get the maximum number of melee units allowed per melee tower
  int maxMeleeUnits = textLoader->getInteger(string("IDS_MT_MU"));

  //get the identifier for no tower type chosen
  string noTowerAtTileID = textLoader -> getTypeID("IDS_NT");

  //get the identifier for each basic type of tower
  string cheesePizzaID = textLoader -> getTypeID(string("IDS_CPT"));
  string sodaID = textLoader -> getTypeID(string("IDS_SOT"));
  string normalFryID = textLoader -> getTypeID(string("IDS_NFT"));
  string miniMMSID = textLoader -> getTypeID(string("IDS_MMMT"));

  //first make a pointer to the first of the tower types for each tower tree
  shared_ptr<RangeTower> cheesePizza = make_shared<CheesePizza>(textLoader, eventManager, textureLoader);
  shared_ptr<RangeTower> soda = make_shared<Soda>(textLoader, eventManager, textureLoader);
  shared_ptr<MeleeTower> normalFry = make_shared<NormalFry>(textLoader,maxMeleeUnits, eventManager, textureLoader);
  shared_ptr<RangeTower> miniMMS = make_shared<MiniMMS>(textLoader, eventManager, textureLoader);


  //push all basic towers into a single vector (the vector for an empty tile)
  vector<shared_ptr<TowerInterface>> noTowerAtTileUpgrades;
  noTowerAtTileUpgrades.push_back(cheesePizza);
  noTowerAtTileUpgrades.push_back(soda);
  noTowerAtTileUpgrades.push_back(normalFry);
  noTowerAtTileUpgrades.push_back(miniMMS);

  //add the towers to tower upgrades
  allTowerUpgrades.insert({noTowerAtTileID, noTowerAtTileUpgrades});

  //add the towers  to towers types
  allTowerTypes.insert({cheesePizzaID, cheesePizza});
  allTowerTypes.insert({sodaID, soda});
  allTowerTypes.insert({normalFryID, normalFry});
  allTowerTypes.insert({miniMMSID, miniMMS});


  this -> populateTowerUpgrades();
}

/*
 * Add all the upgrades for each tower to a map of possible upgrades
 * and add them to the list of placeable towers
 */
void TowerManager::populateTowerUpgrades(){
  //get the maximum number of melee units allowed per melee tower
  int maxMeleeUnits = textLoader->getInteger(string("IDS_MT_MU"));

  populateTowerUpgradesLvl1(maxMeleeUnits);
  populateTowerUpgradesLvl2(maxMeleeUnits);
  populateTowerUpgradesLvl3(maxMeleeUnits);

}
/*
 * Add all the upgrades for each tower to a map of possible upgrades for level 1
 * @param maxMeleeUnits: the maximum number of units a melee tower can have
 */
void TowerManager::populateTowerUpgradesLvl1(int maxMeleeUnits){
  //get the identifier for each basic type of tower
  string cheesePizzaID = textLoader -> getTypeID(string("IDS_CPT"));
  string sodaID = textLoader -> getTypeID(string("IDS_SOT"));
  string normalFryID = textLoader -> getTypeID(string("IDS_NFT"));
  string miniMMSID = textLoader -> getTypeID(string("IDS_MMMT"));

  //get the identifier for each level 2 type of tower
  string pepperoniPizzaID = textLoader -> getTypeID(string("IDS_PPT"));
  string energyDrinkID = textLoader -> getTypeID(string("IDS_EDT"));
  string crinkleFryID = textLoader -> getTypeID(string("IDS_CFT"));
  string normalMMSID = textLoader -> getTypeID(string("IDS_NMMT"));

  //make a pointer to each type of object that the basic types can be upgraded to
  shared_ptr<RangeTower> pepperoniPizza = make_shared<PepperoniPizza>(textLoader,  eventManager, textureLoader);
  shared_ptr<RangeTower> energyDrink = make_shared<EnergyDrink>(textLoader,  eventManager, textureLoader);
  shared_ptr<MeleeTower> crinkleFry = make_shared<CrinkleFry>(textLoader,maxMeleeUnits, eventManager, textureLoader);
  shared_ptr<RangeTower> normalMMS = make_shared<NormalMMS>(textLoader, eventManager, textureLoader);

  //push each tower into a vector of possible upgrades
  vector<shared_ptr<TowerInterface>> cheesePizzaUpgrades;
  cheesePizzaUpgrades.push_back(pepperoniPizza);
  vector<shared_ptr<TowerInterface>> sodaUpgrades;
  sodaUpgrades.push_back(energyDrink);
  vector<shared_ptr<TowerInterface>> normalFryUpgrades;
  normalFryUpgrades.push_back(crinkleFry);
  vector<shared_ptr<TowerInterface>> miniMMSUpgrades;
  miniMMSUpgrades.push_back(normalMMS);

  //insert the vector into the map of all possible upgrades keyed on the string identifier
  //from the type of tower you upgrade from
  allTowerUpgrades.insert({cheesePizzaID, cheesePizzaUpgrades});
  allTowerUpgrades.insert({sodaID, sodaUpgrades});
  allTowerUpgrades.insert({normalFryID, normalFryUpgrades});
  allTowerUpgrades.insert({miniMMSID, miniMMSUpgrades});

  //add the towers  to towers types
  allTowerTypes.insert({pepperoniPizzaID, pepperoniPizza});
  allTowerTypes.insert({energyDrinkID, energyDrink});
  allTowerTypes.insert({crinkleFryID, crinkleFry});
  allTowerTypes.insert({normalMMSID, normalMMS});
}
/*
 * Add all the upgrades for each tower to a map of possible upgrades for level 2
 * @param maxMeleeUnits: the maximum number of units a melee tower can have
 */
void TowerManager::populateTowerUpgradesLvl2(int maxMeleeUnits){
  //get the identifier for each level 2 type of tower
  string pepperoniPizzaID = textLoader -> getTypeID(string("IDS_PPT"));
  string energyDrinkID = textLoader -> getTypeID(string("IDS_EDT"));
  string crinkleFryID = textLoader -> getTypeID(string("IDS_CFT"));
  string normalMMSID = textLoader -> getTypeID(string("IDS_NMMT"));

  //get the identifier for each level 3 type of tower
  string deepDishID = textLoader -> getTypeID(string("IDS_DDT"));
  string meatLoversID = textLoader -> getTypeID(string("IDS_MLT"));
  string spicyFryID = textLoader -> getTypeID(string("IDS_SFT"));
  string waffleFryID = textLoader -> getTypeID(string("IDS_WFT"));
  string slushieID = textLoader -> getTypeID(string("IDS_SLT"));
  string gravyID = textLoader -> getTypeID(string("IDS_GT"));
  string peanutButterMMSID = textLoader -> getTypeID(string("IDS_PBMMT"));
  string peanutMMSID = textLoader -> getTypeID(string("IDS_PMMT"));

  //make a pointer to each type of object that the type 2 towers can be upgraded to
  shared_ptr<RangeTower> deepDish = make_shared<DeepDish>(textLoader, eventManager, textureLoader);
  shared_ptr<RangeTower> meatLovers = make_shared<MeatLovers>(textLoader, eventManager, textureLoader);
  shared_ptr<MeleeTower> spicyFry = make_shared<SpicyFry>(textLoader,maxMeleeUnits, eventManager, textureLoader);
  shared_ptr<MeleeTower> waffleFry = make_shared<WaffleFry>(textLoader, maxMeleeUnits, eventManager, textureLoader);
  shared_ptr<RangeTower> slushie = make_shared<Slushie>(textLoader, eventManager, textureLoader);
  shared_ptr<RangeTower> gravy = make_shared<Gravy>(textLoader, eventManager, textureLoader);
  shared_ptr<RangeTower> peanutButterMMS = make_shared<PeanutButterMMS>(textLoader, eventManager, textureLoader);
  shared_ptr<RangeTower> peanutMMS = make_shared<PeanutMMS>(textLoader, eventManager, textureLoader);

  //push each tower into a vector of possible upgrades
  vector<shared_ptr<TowerInterface>> pepperoniPizzaUpgrades;
  pepperoniPizzaUpgrades.push_back(deepDish);
  pepperoniPizzaUpgrades.push_back(meatLovers);
  vector<shared_ptr<TowerInterface>> crinkleFryUpgrades;
  crinkleFryUpgrades.push_back(spicyFry);
  crinkleFryUpgrades.push_back(waffleFry);
  vector<shared_ptr<TowerInterface>> energyDrinkUpgrades;
  energyDrinkUpgrades.push_back(slushie);
  energyDrinkUpgrades.push_back(gravy);
  vector<shared_ptr<TowerInterface>> normalMMSUpgrades;
  normalMMSUpgrades.push_back(peanutButterMMS);
  normalMMSUpgrades.push_back(peanutMMS);

  //insert the vector into the map of all possible upgrades keyed on the string identifier
  //from the type of tower you upgrade from
  allTowerUpgrades.insert({pepperoniPizzaID, pepperoniPizzaUpgrades});
  allTowerUpgrades.insert({crinkleFryID, crinkleFryUpgrades});
  allTowerUpgrades.insert({energyDrinkID, energyDrinkUpgrades});
  allTowerUpgrades.insert({normalMMSID, normalMMSUpgrades});

  //add the towers  to towers types
  allTowerTypes.insert({deepDishID, deepDish});
  allTowerTypes.insert({meatLoversID, meatLovers});
  allTowerTypes.insert({spicyFryID, spicyFry});
  allTowerTypes.insert({waffleFryID, waffleFry});
  allTowerTypes.insert({slushieID, slushie});
  allTowerTypes.insert({gravyID, gravy});
  allTowerTypes.insert({peanutButterMMSID, peanutButterMMS});
  allTowerTypes.insert({peanutMMSID, peanutMMS});
}

/*
 * Add all the upgrades for each tower to a map of possible upgrades for level 3
 * @param maxMeleeUnits: the maximum number of units a melee tower can have
 */
void TowerManager::populateTowerUpgradesLvl3(int maxMeleeUnits){
  //get the identifier for each level 3 type of tower
  string deepDishID = textLoader -> getTypeID(string("IDS_DDT"));
  string meatLoversID = textLoader -> getTypeID(string("IDS_MLT"));
  string spicyFryID = textLoader -> getTypeID(string("IDS_SFT"));
  string waffleFryID = textLoader -> getTypeID(string("IDS_WFT"));
  string slushieID = textLoader -> getTypeID(string("IDS_SLT"));
  string gravyID = textLoader -> getTypeID(string("IDS_GT"));
  string peanutButterMMSID = textLoader -> getTypeID(string("IDS_PBMMT"));
  string peanutMMSID = textLoader -> getTypeID(string("IDS_PMMT"));

  //push each tower into a vector of possible upgrades
  //there are none since this is the last level of towers
  vector<shared_ptr<TowerInterface>> deepDishUpgrades;
  vector<shared_ptr<TowerInterface>> meatLoversUpgrades;
  vector<shared_ptr<TowerInterface>> spicyFryUpgrades;
  vector<shared_ptr<TowerInterface>> waffleFryUpgrades;
  vector<shared_ptr<TowerInterface>> slushieUpgrades;
  vector<shared_ptr<TowerInterface>> gravyUpgrades;
  vector<shared_ptr<TowerInterface>> peanutButterMMSUpgrades;
  vector<shared_ptr<TowerInterface>> peanutMMSUpgrades;

  //insert the vector into the map of all possible upgrades keyed on the string identifier
  //from the type of tower you upgrade from
  allTowerUpgrades.insert({deepDishID, deepDishUpgrades});
  allTowerUpgrades.insert({meatLoversID, meatLoversUpgrades});
  allTowerUpgrades.insert({spicyFryID, spicyFryUpgrades});
  allTowerUpgrades.insert({waffleFryID, waffleFryUpgrades});
  allTowerUpgrades.insert({slushieID, slushieUpgrades});
  allTowerUpgrades.insert({gravyID, gravyUpgrades});
  allTowerUpgrades.insert({peanutButterMMSID, peanutButterMMSUpgrades});
  allTowerUpgrades.insert({peanutMMSID, peanutMMSUpgrades});
}

/*
 * default version that does not include a specific upgrade decision
 * @return the price of the tower at the row and col
 */
int TowerManager::getTowerPrice(int row, int col){
  string towerID;

  //if there is no tower here
  if(towersPlaced.find(row*xDim+col) == towersPlaced.end()){
    //get the identifier for no tower type chosen
    towerID = textLoader -> getTypeID("IDS_NT");

  }else{
     auto tower = towersPlaced.at(row*xDim+col);
     towerID = tower -> getType();
  }

  // get the vector of towers we can upgrade to
  //grab the first tower in that list
  //and return its price
  int price = allTowerUpgrades.at(towerID).at(0) -> getPrice();

  return price;
}

/*
 * @return the price of the specific tower
 */
int TowerManager::getTowerPrice(string towerTypeID){
  assert(allTowerTypes.find(towerTypeID) != allTowerTypes.end());
  return allTowerTypes.at(towerTypeID) -> getPrice();
}


/*
 * @return unordered_map<string, vector<TowerInterface>>: all the towers the player can choose from
 */
unordered_map<string, vector<shared_ptr<TowerInterface>>>& TowerManager::getAllTowersToChoose(){
  return allTowerUpgrades;
}

/*
 * @return a tower with the type id passed
 */
shared_ptr<TowerInterface> TowerManager::getGenericTower(string towerTypeID){
  if(allTowerTypes.find(towerTypeID) != allTowerTypes.end()){
    return allTowerTypes.at(towerTypeID);
  }
  assert(true == false);
  return NULL;
}

/*
 * @return vector<TowerInterface>: all the upgrades for a partiuclar tower type
 */
vector<shared_ptr<TowerInterface>>& TowerManager::getUpgradesForTower(string towerTypeID){
  //clear any tower upgrades in the queue
  towerUpgrades.clear();
  //set to false because this should not have a physics body
  bool inWorld = false;
  //make a copy of each type of tower
  for(shared_ptr<TowerInterface> towerToCopy : allTowerUpgrades.at(towerTypeID)){
    shared_ptr<TowerInterface> copy = copyOfTowerType(towerToCopy->getType(), 0, 0, inWorld);
    towerUpgrades.push_back(copy);
  }
  return towerUpgrades;
}

/*
 * @return vector<TowerInterface>: the vector of tower upgrades that has been copied from the full map
 *                                 of possible upgrades
 */
vector<shared_ptr<TowerInterface>>& TowerManager::getModifiedUpgrades(){
  return towerUpgrades;
}

/*
 * @return unordered_map<int, TowerInterface>:all towers currently placed
 */
unordered_map<int, shared_ptr<TowerInterface>>& TowerManager::getTowersPlaced(){
  return towersPlaced;
}

/*
 * @param combinedRowCol: the key in the map for this tower
 * @return TowerInterface: a pointer to the tower at the position on the grid
 */
shared_ptr<TowerInterface> TowerManager::getTowerPlaced(int combinedRowCol){
  if(towersPlaced.find(combinedRowCol) == towersPlaced.end()){
    string noTowerID = textLoader -> getTypeID("IDS_NT");
    shared_ptr<TowerInterface> noTower = make_shared<NotATower>(textLoader, eventManager, textureLoader);
    return noTower;
  }
  return towersPlaced.at(combinedRowCol);
}

/*
 * @param row: the row index for the tower
 * @param col: the col index for the tower
 * @return TowerInterface: the pointer to the tower at the position on the grid
 */
shared_ptr<TowerInterface> TowerManager::getTowerPlaced(int row, int col){
  if(towersPlaced.find(row*xDim+col) == towersPlaced.end()){
    string noTowerID = textLoader -> getTypeID("IDS_NT");
    shared_ptr<TowerInterface> noTower = make_shared<NotATower>(textLoader, eventManager, textureLoader);
    return noTower;
  }
  return towersPlaced.at(row*xDim + col);
}

/*
 * Get the obstacle at the position as if it were a vector (used to grab
 * whatever is available at a position for purchase)
 * @param row: the row index for the obstacle
 * @parm col: the col index for the obstacle
 */
vector<shared_ptr<TowerInterface>>& TowerManager::getObstacleAsVector(int row, int col){
  shared_ptr<TowerInterface> obstacle = getObstacle( row,  col);
  string type = obstacle -> getType();
  assert(allTowerUpgrades.find(type) != allTowerUpgrades.end());
  return allTowerUpgrades.at(type);
}

/*
 * @param row: the row index for the obstacle
 * @parm col: the col index for the obstacle
 */
shared_ptr<TowerInterface> TowerManager::getObstacle(int row, int col){
  if(towersPlaced.find(row*xDim+col) == towersPlaced.end()){
    string noTowerID = textLoader -> getTypeID("IDS_NT");
    shared_ptr<TowerInterface> noTower = make_shared<NotATower>(textLoader, eventManager, textureLoader);
    return noTower;
  }
  return towersPlaced.at(row*xDim + col);
}


/*
 * Handle a tower creation event
 * @param event: the tower creation event
 */
void TowerManager::handleTowerCreation(const EventInterface& event){
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
  int row = towerPosID / xDim;
  int col = towerPosID % xDim;

  //and add it
  addTower(towerTypeID, row, col);
}

/*
 * Handle a tower remove event
 * @param event: the tower remove event
 */
void TowerManager::handleTowerRemove(const EventInterface& event){
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
  int row = towerPosID / xDim;
  int col = towerPosID % xDim;

  //remove the tower at the position specified
  removeTower(row, col);

}

/*
 * Add obstacles to the map where there are some
 * @param allObstaclesToPlace: all unmade obstacles
 * sent from GameLogic and BoardManager
 */
void TowerManager::addObstacles(unordered_map<int, intPair>& allObstaclesToPlace){
  for(auto it = allObstaclesToPlace.begin(); it != allObstaclesToPlace.end(); ++it){
      //grab the number stored at the position to indicate the type of obstacle
      int typeNum = (*it).first;
      //grab the string identifier of this type of obstacle
      string obstacleType = textLoader -> getTypeID(std::to_string(typeNum));

      //the obstacle we will place
      shared_ptr<TowerInterface> obstacle;

      //grab the position of the obstacle
      int row = ((*it).second).first;
      int col = ((*it).second).second;

      obstacle = copyOfTowerType(obstacleType, row, col);
      towersPlaced.insert({row*xDim+col, obstacle});
  }
}


/*
 * @param type: the index in the vector of tower types that
 * @param combinedRowCol: the posiition on the grid translated as the towers id
 */
void TowerManager::addTower(string type, int combinedRowCol){
  //an tower of the desired type
  shared_ptr<TowerInterface> aTower = copyOfTowerType(type, combinedRowCol / xDim, combinedRowCol % xDim);

  //check if there is a tower at the position that we must remove
  if(towersPlaced.find(combinedRowCol) != towersPlaced.end()){
    modifyToIncludeUpgrades(aTower, towersPlaced.at(combinedRowCol));
  }

  //remove the current tower position if there is one
  removeTower(combinedRowCol);

  //insert the new tower
  towersPlaced.insert({combinedRowCol, aTower});

  //make sure we signal to collision manager this tower exists
  collisionManager -> addNewTower(aTower);
}
/*
 * @param type: the index in the vector of tower types that
 * @param row: the posiition on the grid in the row
 * @param col: the position on the grid in the col
 */
void TowerManager::addTower(string type, int row, int col){

  //an tower of the desired type
  shared_ptr<TowerInterface> aTower = copyOfTowerType(type, row, col);

  int combinedRowCol = row * xDim + col;
  //check if there is a tower at the position that we must remove
  if(towersPlaced.find(combinedRowCol) != towersPlaced.end()){
    modifyToIncludeUpgrades(aTower, towersPlaced.at(combinedRowCol));
  }

  //remove the current tower position if there is one
  removeTower(row, col);

  //insert the new tower
  towersPlaced.insert({row*xDim+col, aTower});

  //signal to collison manager this tower exists
  collisionManager -> addNewTower(aTower);
}

/*
 * calculate how much the stats of the previous tower were improved and apply that
 * to the new tower it is being upgraded to
 * @param towerUpgrade: the tower we will be upgrading to
 * @param tower: the tower we will be upgrading
 */
void TowerManager::modifyToIncludeUpgrades(shared_ptr<TowerInterface> towerUpgrade, shared_ptr<TowerInterface> tower){

  //get a generic copy of this tower to measure the amount its variables have been changed
  shared_ptr<TowerInterface> genericTowerOfType = getGenericTower(tower->getType());


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

/*
 * Make a copy of one of the tower types and
 * initialize them with their units/projectiles
 * @param inWorld: whether this should be placed in the physics and collision world
 * @return a shared pointer to a copy of the tower type specified
 */
shared_ptr<TowerInterface> TowerManager::copyOfTowerType(string type, int row, int col, bool inWorld){
  shared_ptr<TowerInterface> retTower;

  //get the maximum number of melee units allowed per melee tower
  int maxMeleeUnits = textLoader -> getInteger(string("IDS_MT_MU"));

  if(type == textLoader->getTypeID(string("IDS_CPT"))){
    retTower = make_shared<CheesePizza>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_PPT"))){
    retTower = make_shared<PepperoniPizza>(textLoader,eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_DDT"))){
    retTower = make_shared<DeepDish>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_MLT"))){
    retTower = make_shared<MeatLovers>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_MMMT"))){
    retTower = make_shared<MiniMMS>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_NMMT"))){
    retTower = make_shared<NormalMMS>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_PBMMT"))){
    retTower = make_shared<PeanutButterMMS>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_PMMT"))){
    retTower = make_shared<PeanutMMS>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_SOT"))){
    retTower = make_shared<Soda>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_EDT"))){
    retTower = make_shared<EnergyDrink>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_GT"))){
    retTower = make_shared<Gravy>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_SLT"))){
    retTower = make_shared<Slushie>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_NFT"))){
    retTower = make_shared<NormalFry>(textLoader, maxMeleeUnits, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_CFT"))){
    retTower = make_shared<CrinkleFry>(textLoader, maxMeleeUnits, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_SFT"))){
    retTower = make_shared<SpicyFry>(textLoader, maxMeleeUnits, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_WFT"))){
    retTower = make_shared<WaffleFry>(textLoader, maxMeleeUnits, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_CTO"))){
    retTower = make_shared<CafeteriaTable>(textLoader, eventManager, textureLoader);
  }
  else if(type == textLoader->getTypeID(string("IDS_TCO"))){
    retTower = make_shared<TrashCan>(textLoader, eventManager, textureLoader);
  }

  //set the dimensions and location of the tower
  retTower -> setPos(row,col);
  retTower -> setXCoordinate((float)col * xGrid + (xGrid/2.0));
  retTower -> setYCoordinate((float)row * yGrid + (yGrid/2.0));

  //get the sprite to be drawn
  sf::Sprite currentSprite = retTower -> getSprite();

  //the bounding rectangle will give us the dimensions of the sprite
  sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
  //the x dimension of the box
  float xDimension = boundingBox.width;
  //the ydimension of the box
  float yDimimenson = boundingBox.height;

  //the scale in the x direction
  float xScale = (float) xGrid / (float) xDimension;
  //the scale in the y direction
  float yScale = (float) yGrid / (float) yDimimenson;

  retTower->setXScale(xScale);
  retTower->setYScale(yScale);
  retTower->setTileSize(xGrid, yGrid);
  if(inWorld){
    //retTower -> setWorld(world);

    //if the tower is a melee tower we set its rally point to be the center of the tower
    if(retTower -> isMelee){
      MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(retTower.get());
      //set the rally point of the tower to be the center of the tower
      meleeTower -> resetRallyPoint((float)col * xGrid + (xGrid/2.0), (float)row * yGrid + (yGrid/2.0));
      //set the positions of the units to be the center of the tower
      meleeTower -> setUpUnitCoordinates(meleeTower->getXCoordinate(), meleeTower->getYCoordinate());
      meleeTower -> setUpUnitTileSize(xGrid, yGrid);
      /*
      //loop through all the meleeUnits and set their world
      vector<shared_ptr<MeleeUnit>> meleeUnits = meleeTower -> getUnits();
      for (shared_ptr<MeleeUnit> meleeUnit : meleeUnits){
        meleeUnit -> setWorld(world);
        meleeUnit -> setFixtures();
      }
      */
    }
  }
  return retTower;
}

/*
 * Remove a tower from the specified position
 * @param combinedRowCol: the row*maxCol+col
 */
void TowerManager::removeTower(int combinedRowCol){
  if(towersPlaced.find(combinedRowCol) != towersPlaced.end()){
    shared_ptr<TowerInterface> towerToRemove = towersPlaced.at(combinedRowCol);
    collisionManager -> removeOldTower(towerToRemove);
    towersPlaced.erase(combinedRowCol);
  }
}
/*
 * Remove a tower from the specified position
 * @param row: row index
 * @param col: the col index
 */
void TowerManager::removeTower(int row, int col){
  int combinedRowCol = row * xDim + col;
  if(towersPlaced.find(combinedRowCol) != towersPlaced.end()){
    shared_ptr<TowerInterface> towerToRemove = towersPlaced.at(combinedRowCol);
    collisionManager -> removeOldTower(towerToRemove);
    towersPlaced.erase(combinedRowCol);
  }
}

/*
 * @return the price of an upgrade for the tower at the passed position
 */
int TowerManager::getUpgradePrice(int row, int col){
  int combinedRowCol = row * xDim + col;
  if(towersPlaced.find(combinedRowCol) == towersPlaced.end()){
    cerr << "Could Not Get Upgrade Price: TowerManager" << endl;
    assert(true == false);
  }

  //get the tower we are looking for upgrade prices for
  shared_ptr<TowerInterface> towerToUpgrade = towersPlaced.at(combinedRowCol);

  //calculate the next upgrade price
  int nextUpgradePrice = pow(1.5,towerToUpgrade->getNumUpgrades());

  return nextUpgradePrice;
}

/*
 * Upgrades the tower at the passed row and column for the type of upgrade requested
 * @param upgradeButtonID: the id of the button pressed to upgrade
 * @param row: row of the tower
 * @param col: col of the tower
 */
 void TowerManager::upgradeTower(string upgradeButtonID, int row, int col){
   int combinedRowCol = row * xDim + col;
   if(towersPlaced.find(combinedRowCol) == towersPlaced.end()){
     cerr << "Upgrade Tower Failed: TowerManager" << endl;
     assert(true == false);
   }

   //get the tower we want to upgrade the stat of
   shared_ptr<TowerInterface> towerToUpgrade = towersPlaced.at(combinedRowCol);

   //if this is a melee tower we handle its upgrades differently
   if(towerToUpgrade -> isMelee){
     upgradeMeleeTower(upgradeButtonID, towerToUpgrade);
   }
  else{
     upgradeRangeTower(upgradeButtonID, towerToUpgrade);
   }
 }

/*
 * Upgrades the melee tower in the statistic corresponding to the button id
 * @param upgradeButtonID: the upgrade button that has been chosen
 * @param towerToUpgrade: the  tower we are upgrading
 */
 void TowerManager::upgradeMeleeTower(string upgradeButtonID, shared_ptr<TowerInterface> towerToUpgrade){
   //calculate the price for this upgrade
   int upgradePrice = pow(1.5, towerToUpgrade -> getNumUpgrades());

   //generate an amount to upgrade
   //the distribution we generate numbers for
   std::uniform_int_distribution<int> dist(textLoader->getInteger(string("IDS_Minimum_Tower_Upgrade")),pow(textLoader->getInteger(string("IDS_Maximum_Tower_Upgrade")), towerToUpgrade->getLevel()));

   int upgradeAmount = dist(mt);

   //cast as a melee tower
   MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(towerToUpgrade.get());

   //check which upgrade has been trigged and apply the upgrading amount
   if(upgradeButtonID == textLoader->getString(string("IDS_Tower_Radius_Upgrade"))){
     meleeTower->updateRadius(meleeTower->getRadius()+upgradeAmount);
   }
   else if(upgradeButtonID == textLoader->getString(string("IDS_Tower_Respawn_Rate_Upgrade"))){
     meleeTower->updateRespawnSpeed(meleeTower->getRespawnSpeed()+upgradeAmount);
   }
   else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Max_Hitpoints_Upgrade"))){
     meleeTower->updateUnitHitpoints(meleeTower->getUnitHitpoints()+upgradeAmount);
   }
   else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Max_Damage_Upgrade"))){
     meleeTower->updateUnitDamage(meleeTower->getUnitDamage()+upgradeAmount);
   }
   else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Armor_Penetration_Upgrade"))){
     meleeTower->updateUnitArmorPenetration(meleeTower->getUnitArmorPenetration()+upgradeAmount);
   }
   else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Armor_Upgrade"))){
     meleeTower->updateUnitArmor(meleeTower->getUnitArmor()+upgradeAmount);
   }
   else{
     cerr << "upgrade Melee Tower unknown upgrade button id : TowerManager" << endl;
     assert(true == false);
   }

   meleeTower->incrementNewUpgrade();
 }

 /*
  * Upgrades the range tower in the statistic corresponding to the button id
  * @param upgradeButtonID: the upgrade button that has been chosen
  * @param towerToUpgrade: the tower we are upgrading
  */
  void TowerManager::upgradeRangeTower(string upgradeButtonID, shared_ptr<TowerInterface> towerToUpgrade){
    //calculate the price for this upgrade
    int upgradePrice = pow(1.5, towerToUpgrade -> getNumUpgrades());

    //generate an amount to upgrade
    //the distribution we generate numbers for
    std::uniform_int_distribution<int> dist(textLoader->getInteger(string("IDS_Minimum_Tower_Upgrade")),pow(textLoader->getInteger(string("IDS_Maximum_Tower_Upgrade")), towerToUpgrade->getLevel()));

    int upgradeAmount = dist(mt);

    //cast as a range tower
    RangeTower* rangeTower = dynamic_cast<RangeTower*>(towerToUpgrade.get());

    //check which upgrade has been trigged and apply the upgrading amount
    if(upgradeButtonID == textLoader->getString(string("IDS_Tower_Radius_Upgrade"))){
      rangeTower->updateRadius(rangeTower->getRadius()+upgradeAmount);
    }
    else if(upgradeButtonID == textLoader->getString(string("IDS_Tower_Rate_Of_Fire_Upgrade"))){
      rangeTower->updateRateOfFire(rangeTower->getRateOfFire()+upgradeAmount);
    }
    else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Max_Damage_Upgrade"))){
      rangeTower->updateProjectileDamage(rangeTower->getProjectileDamage()+upgradeAmount);
    }
    else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Armor_Penetration_Upgrade"))){
      rangeTower->updateProjectileArmorPenetration(rangeTower->getProjectileArmorPenetration()+upgradeAmount);
    }
    else if(upgradeButtonID == textLoader->getString(string("IDS_Actor_Area_Of_Effect_Upgrade"))){
      rangeTower->updateProjectileAreaOfEffect(rangeTower->getProjectileAreaOfEffect()+upgradeAmount);
    }
    else{
      cerr << "upgrade Range Tower unknown upgrade button id : Tower Manager" << endl;
      assert(true == false);
    }

    rangeTower->incrementNewUpgrade();
  }
