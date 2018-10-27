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
}

/*
 * Add all the basic towers to the vector of possible towers
 */
void TowerManager::populateTowersToChoose(){

  //first make a pointer to the first of the tower types for each tower tree
  shared_ptr<CheesePizza> cheesePizza = make_shared<CheesePizza>(CheesePizza());
  shared_ptr<Soda> soda = make_shared<Soda>(Soda());
  shared_ptr<NormalFry> normalFry = make_shared<NormalFry>(NormalFry());
  shared_ptr<MiniMMS> miniMMS = make_shared<MiniMMS>(MiniMMS());

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
