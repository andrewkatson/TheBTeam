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
  this -> populateTowersToChoose();
  this -> populateTowerUpgrades();
}

/*
 * Add all the basic towers to the vector of possible towers
 */
void TowerManager::populateTowersToChoose(){

  //get the maximum number of melee units allowed per melee tower
  int maxMeleeUnits = textLoader -> getConstant(string("IDS_MT_MU"));
  //get the identifier for each basic type of tower
  string cheesePizzaID = textLoader -> getString(string("IDS_CPT"));
  string sodaID = textLoader -> getString(string("IDS_SOT"));
  string normalFryID = textLoader -> getString(string("IDS_NFT"));
  string miniMMSID = textLoader -> getString(string("IDS_MMMT"));

  //first make a pointer to the first of the tower types for each tower tree
  shared_ptr<CheesePizza> cheesePizza = make_shared<CheesePizza>(CheesePizza(textLoader, cheesePizzaID));
  shared_ptr<Soda> soda = make_shared<Soda>(Soda(textLoader, sodaID));
  shared_ptr<NormalFry> normalFry = make_shared<NormalFry>(NormalFry(textLoader, normalFryID,maxMeleeUnits));
  shared_ptr<MiniMMS> miniMMS = make_shared<MiniMMS>(MiniMMS(textLoader, miniMMSID));

  //then make pointers to the generic types of tower that will hold an internal tower(i.e. their specific branch)
  shared_ptr<TowerInterface> towerType1 = make_shared<RangeTower>(RangeTower(cheesePizza));
  shared_ptr<TowerInterface> towerType2 = make_shared<RangeTower>(RangeTower(soda));
  shared_ptr<TowerInterface> towerType3 = make_shared<MeleeTower>(MeleeTower(normalFry));
  shared_ptr<TowerInterface> towerType4 = make_shared<RangeTower>(RangeTower(miniMMS));

  //add the towers to towers to choose
  towersToChoose.push_back(towerType1);
  towersToChoose.push_back(towerType2);
  towersToChoose.push_back(towerType3);
  towersToChoose.push_back(towerType4);

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
  shared_ptr<RangeTower> pepperoniPizza = make_shared<PepperoniPizza>(PepperoniPizza(textLoader, pepperoniPizzaID));
  shared_ptr<RangeTower> energyDrink = make_shared<EnergyDrink>(EnergyDrink(textLoader, energyDrinkID));
  shared_ptr<MeleeTower> crinkleFry = make_shared<CrinkleFry>(CrinkleFry(textLoader, crinkleFryID,maxMeleeUnits));
  shared_ptr<RangeTower> normalMMS = make_shared<NormalMMS>(NormalMMS(textLoader, normalMMSID));

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
  possibleUpgrades.insert({cheesePizzaID, cheesePizzaUpgrades});
  possibleUpgrades.insert({sodaID, sodaUpgrades});
  possibleUpgrades.insert({normalFryID, normalFryUpgrades});
  possibleUpgrades.insert({miniMMSID, miniMMSUpgrades});

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
  shared_ptr<RangeTower> deepDish = make_shared<DeepDish>(DeepDish(textLoader, deepDishID));
  shared_ptr<RangeTower> meatLovers = make_shared<MeatLovers>(MeatLovers(textLoader, meatLoversID));
  shared_ptr<MeleeTower> spicyFry = make_shared<SpicyFry>(SpicyFry(textLoader, spicyFryID,maxMeleeUnits));
  shared_ptr<MeleeTower> waffleFry = make_shared<WaffleFry>(WaffleFry(textLoader, waffleFryID, maxMeleeUnits));
  shared_ptr<RangeTower> slushie = make_shared<Slushie>(Slushie(textLoader, slushieID));
  shared_ptr<RangeTower> gravy = make_shared<Gravy>(Gravy(textLoader, gravyID));
  shared_ptr<RangeTower> peanutButterMMS = make_shared<PeanutButterMMS>(PeanutButterMMS(textLoader, peanutButterMMSID));
  shared_ptr<RangeTower> peanutMMS = make_shared<PeanutMMS>(PeanutMMS(textLoader, peanutMMSID));

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
  possibleUpgrades.insert({pepperoniPizzaID, pepperoniPizzaUpgrades});
  possibleUpgrades.insert({crinkleFryID, crinkleFryUpgrades});
  possibleUpgrades.insert({energyDrinkID, energyDrinkUpgrades});
  possibleUpgrades.insert({normalMMSID, normalMMSUpgrades});
}


/*
 * @return vector<TowerInterface>: all the towers the player can choose from
 */
vector<shared_ptr<TowerInterface>>& TowerManager::getTowersToChoose(){
  return towersToChoose;
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
