#include "BoardManager.hpp"

BoardManager::BoardManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> textLoader = textLoader;
  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,5)));
  this -> eventManager = eventManager;
  this -> newMap();
  this -> registerDelegates();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void BoardManager::registerDelegates(){
  //bind our delegate function for tower creation events
  EventManager::EventDelegate delegate = std::bind(&BoardManager::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent event = TowerCreationEvent();
  EventType type = event.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(delegate, textLoader -> getString(string("IDS_BMD1")),type);
}

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

/*
 * Handle any tower creation
 * @param event: event of the tower creation
 */
void BoardManager::handleTowerCreation(const EventInterface& event){
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

  cout << "ID " << tcEventData -> towerID << endl;

}
int BoardManager::getYDim(){
  return mapFactory -> getYDim();
}
int BoardManager::getXDim(){
  return mapFactory -> getXDim();
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
