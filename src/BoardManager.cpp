#include "BoardManager.hpp"

BoardManager::BoardManager(shared_ptr<EventManager> eventManager){
  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,5)));
  this -> eventManager = eventManager;
  this -> newMap();
}

//handle new event
void BoardManager::delegateMethod(const EventInterface& event){}

//genearte a new random map
void BoardManager::newMap(){
  if(mapFactory != NULL){
      mapFactory -> generateMap();
  }
}

//generate a new random map with a differnet set of customization options
void BoardManager::newMap(MapChoices * newCustomization){
  if(mapFactory != NULL){
    mapFactory -> setMapCustomizationChoices(newCustomization);
    mapFactory -> generateMap();
  }
}

void BoardManager::setMapCustomizationChoices(MapChoices * newCustomization){
  mapFactory -> setMapCustomizationChoices(newCustomization);
}
void BoardManager::setMapObstacleChoice(int obstacleChoice){
  mapFactory -> setMapObstacleChoice(obstacleChoice);
}
void BoardManager::setMapCafeteriaChoice(int cafeteriaChoice){
  mapFactory -> setMapCafeteriaChoice(cafeteriaChoice);
}
void BoardManager::setMapEntryChoice(int pathEntryChoice){
  mapFactory -> setMapEntryChoice(pathEntryChoice);
}

vector<vector<int>>const & BoardManager::getDistances(){
  return distances;
}
vector<int>const & BoardManager::getDistancesRow(int row){
  return distances.at(row);
}
vector<int>const & BoardManager::getDistanceCol(int col){
  static vector<int> distanceCol;
  distanceCol.clear();

  for(int row = 0; row < mapFactory -> getYDim(); row++){
    distanceCol.push_back(distances.at(row).at(col));
  }
  return distanceCol;
}

int BoardManager::getDistanceRowCol(int row, int col){
  return distances.at(row).at(col);
}

vector<vector<int>>const & BoardManager::getAboveFloor(){
  return aboveFloorGrid;
}
vector<int>const & BoardManager::getAboveFloorRow(int row){
  return aboveFloorGrid.at(row);
}
vector<int>const & BoardManager::getAboveFloorCol(int col){
  static vector<int> aboveFloorCol;
  aboveFloorCol.clear();

  for(int row = 0; row < mapFactory -> getYDim(); row++){
    aboveFloorCol.push_back(aboveFloorGrid.at(row).at(col));
  }
  return aboveFloorCol;
}
int BoardManager::getAboveFloorRowCol(int row, int col){
  return aboveFloorGrid.at(row).at(col);
}

vector<vector<int>>const & BoardManager::getFloor(){
  return floorGrid;
}
vector<int>const & BoardManager::getFloorRow(int row){
  return floorGrid.at(row);
}
vector<int>const & BoardManager::getFloorCol(int col){
  static vector<int> floorCol;
  floorCol.clear();

  for(int row = 0; row < mapFactory -> getYDim(); row++){
    floorCol.push_back(floorGrid.at(row).at(col));
  }
  return floorCol;
}
int BoardManager::getFloorRowCol(int row, int col){
  return floorGrid.at(row).at(col);
}
