#include "TowerManager.hpp"

/*
 * Constructor for a tower manager
 * @param eventManager: the event manager class that directs events
 * @param yDim: the y dimension of the grid (rows)
 * @param xDim: the x dimension of the grid (cols)
 */
TowerManager::TowerManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, int yDim, int xDim){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> xDim = xDim;
  this -> yDim = yDim;
  this -> registerDelegates();
  this -> populateTowersToChoose();
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


}

/*
 * Add all the basic towers to the vector of possible towers
 */
void TowerManager::populateTowersToChoose(){

  //get the maximum number of melee units allowed per melee tower
  int maxMeleeUnits = textLoader -> getConstant(string("IDS_MT_MU"));

  //get the identifier for no tower type chosen
  string noTowerAtTileID = textLoader -> getString("IDS_NT");

  //get the identifier for each basic type of tower
  string cheesePizzaID = textLoader -> getString(string("IDS_CPT"));
  string sodaID = textLoader -> getString(string("IDS_SOT"));
  string normalFryID = textLoader -> getString(string("IDS_NFT"));
  string miniMMSID = textLoader -> getString(string("IDS_MMMT"));

  //first make a pointer to the first of the tower types for each tower tree
  shared_ptr<RangeTower> cheesePizza = make_shared<CheesePizza>(textLoader, cheesePizzaID);
  shared_ptr<RangeTower> soda = make_shared<Soda>(textLoader, sodaID);
  shared_ptr<MeleeTower> normalFry = make_shared<NormalFry>(textLoader, normalFryID,maxMeleeUnits);
  shared_ptr<RangeTower> miniMMS = make_shared<MiniMMS>(textLoader, miniMMSID);


  //push all basic towers into a single vector (the vector for an empty tile)
  vector<shared_ptr<TowerInterface>> noTowerAtTileUpgrades;
  noTowerAtTileUpgrades.push_back(cheesePizza);
  noTowerAtTileUpgrades.push_back(soda);
  noTowerAtTileUpgrades.push_back(normalFry);
  noTowerAtTileUpgrades.push_back(miniMMS);

  //add the towers to towers to choose
  allTowersToChoose.insert({noTowerAtTileID, noTowerAtTileUpgrades});

  this -> populateTowerUpgrades();
}

/*
 * Add all the upgrades for each tower to a map of possible upgrades
 */
void TowerManager::populateTowerUpgrades(){
  //get the maximum number of melee units allowed per melee tower
  int maxMeleeUnits = textLoader -> getConstant(string("IDS_MT_MU"));

  populateTowerUpgradesLvl1(maxMeleeUnits);
  populateTowerUpgradesLvl2(maxMeleeUnits);

}
/*
 * Add all the upgrades for each tower to a map of possible upgrades for level 1
 * @param maxMeleeUnits: the maximum number of units a melee tower can have
 */
void TowerManager::populateTowerUpgradesLvl1(int maxMeleeUnits){
  //get the identifier for each basic type of tower
  string cheesePizzaID = textLoader -> getString(string("IDS_CPT"));
  string sodaID = textLoader -> getString(string("IDS_SOT"));
  string normalFryID = textLoader -> getString(string("IDS_NFT"));
  string miniMMSID = textLoader -> getString(string("IDS_MMMT"));

  //get the identifier for each level 2 type of tower
  string pepperoniPizzaID = textLoader -> getString(string("IDS_PPT"));
  string energyDrinkID = textLoader -> getString(string("IDS_EDT"));
  string crinkleFryID = textLoader -> getString(string("IDS_CFT"));
  string normalMMSID = textLoader -> getString(string("IDS_NMMT"));

  //make a pointer to each type of object that the basic types can be upgraded to
  shared_ptr<RangeTower> pepperoniPizza = make_shared<PepperoniPizza>(textLoader, pepperoniPizzaID);
  shared_ptr<RangeTower> energyDrink = make_shared<EnergyDrink>(textLoader, energyDrinkID);
  shared_ptr<MeleeTower> crinkleFry = make_shared<CrinkleFry>(textLoader, crinkleFryID,maxMeleeUnits);
  shared_ptr<RangeTower> normalMMS = make_shared<NormalMMS>(textLoader, normalMMSID);

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
  allTowersToChoose.insert({cheesePizzaID, cheesePizzaUpgrades});
  allTowersToChoose.insert({sodaID, sodaUpgrades});
  allTowersToChoose.insert({normalFryID, normalFryUpgrades});
  allTowersToChoose.insert({miniMMSID, miniMMSUpgrades});

}
/*
 * Add all the upgrades for each tower to a map of possible upgrades for level 2
 * @param maxMeleeUnits: the maximum number of units a melee tower can have
 */
void TowerManager::populateTowerUpgradesLvl2(int maxMeleeUnits){
  //get the identifier for each level 2 type of tower
  string pepperoniPizzaID = textLoader -> getString(string("IDS_PPT"));
  string energyDrinkID = textLoader -> getString(string("IDS_EDT"));
  string crinkleFryID = textLoader -> getString(string("IDS_CFT"));
  string normalMMSID = textLoader -> getString(string("IDS_NMMT"));

  //get the identifier for each level 3 type of tower
  string deepDishID = textLoader -> getString(string("IDS_DDT"));
  string meatLoversID = textLoader -> getString(string("IDS_MLT"));
  string spicyFryID = textLoader -> getString(string("IDS_SFT"));
  string waffleFryID = textLoader -> getString(string("IDS_WFT"));
  string slushieID = textLoader -> getString(string("IDS_SLT"));
  string gravyID = textLoader -> getString(string("IDS_GT"));
  string peanutButterMMSID = textLoader -> getString(string("IDS_PBMMT"));
  string peanutMMSID = textLoader -> getString(string("IDS_PMMT"));

  //make a pointer to each type of object that the type 2 towers can be upgraded to
  shared_ptr<RangeTower> deepDish = make_shared<DeepDish>(textLoader, deepDishID);
  shared_ptr<RangeTower> meatLovers = make_shared<MeatLovers>(textLoader, meatLoversID);
  shared_ptr<MeleeTower> spicyFry = make_shared<SpicyFry>(textLoader, spicyFryID,maxMeleeUnits);
  shared_ptr<MeleeTower> waffleFry = make_shared<WaffleFry>(textLoader, waffleFryID, maxMeleeUnits);
  shared_ptr<RangeTower> slushie = make_shared<Slushie>(textLoader, slushieID);
  shared_ptr<RangeTower> gravy = make_shared<Gravy>(textLoader, gravyID);
  shared_ptr<RangeTower> peanutButterMMS = make_shared<PeanutButterMMS>(textLoader, peanutButterMMSID);
  shared_ptr<RangeTower> peanutMMS = make_shared<PeanutMMS>(textLoader, peanutMMSID);

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
  allTowersToChoose.insert({pepperoniPizzaID, pepperoniPizzaUpgrades});
  allTowersToChoose.insert({crinkleFryID, crinkleFryUpgrades});
  allTowersToChoose.insert({energyDrinkID, energyDrinkUpgrades});
  allTowersToChoose.insert({normalMMSID, normalMMSUpgrades});
}

/*
 * @return the price of the tower at the row and col
 */
int TowerManager::getTowerPrice(int row, int col){
  return getTowerPlaced(row, col) -> getPrice();
}


/*
 * @return vector<TowerInterface>: all the towers the player can choose from
 */
unordered_map<string, vector<shared_ptr<TowerInterface>>>& TowerManager::getAllTowersToChoose(){
  return allTowersToChoose;
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
  return towersPlaced.at(combinedRowCol);
}

/*
 * @param row: the row index for the tower
 * @param col: the col index for the tower
 * @return TowerInterface: the pointer to the tower at the position on the grid
 */
shared_ptr<TowerInterface> TowerManager::getTowerPlaced(int row, int col){
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

}


/*
 * @param type: the index in the vector of tower types that
 * @param combinedRowCol: the posiition on the grid translated as the towers id
 */
void TowerManager::addTower(int type, int combinedRowCol){

}
/*
 * @param type: the index in the vector of tower types that
 * @param row: the posiition on the grid in the row
 * @param col: the position on the grid in the col
 */
void TowerManager::addTower(int type, int row, int col){

}

void TowerManager::removeTower(int combinedRowCol){

}
void TowerManager::removeTower(int row, int col){

}

void TowerManager::upgradeTower(int combinedRowCol){

}
void TowerManager::upgradeTower(int row, int col){

}
