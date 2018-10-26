#include "TowerManager.hpp"

/*
 * Constructor for a tower manager
 * @param eventManager: the event manager class that directs events
 * @param yDim: the y dimension of the grid (rows)
 * @param xDim: the x dimension of the grid (cols)
 */
TowerManager::TowerManager(shared_ptr<EventManager> eventManager, int yDim, int xDim){
  this -> eventManager = eventManager;
  this -> xDim = xDim;
  this -> yDim = yDim;
}

/*
 * @return vector<TowerInterface>: all the towers the player can choose from
 */
vector<unique_ptr<TowerInterface>>& TowerManager::getTowersToChoose(){
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
 * @param combinedRowCol:
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
