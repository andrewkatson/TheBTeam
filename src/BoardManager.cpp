#include "BoardManager.hpp"

BoardManager::BoardManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> textLoader = textLoader;
  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,10)));
  this -> eventManager = eventManager;
  this -> registerDelegates();

}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void BoardManager::registerDelegates(){
  //bind our delegate function for tower creation events
  EventManager::EventDelegate towerCreationEventDelegate = std::bind(&BoardManager::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerCreationEventDelegate,
  textLoader -> getString(string("IDS_BMD_TC")),towerCreationEventType);

  //bind our delegate function for tower remove events
  EventManager::EventDelegate towerRemoveEventDelegate = std::bind(&BoardManager::handleTowerRemove, this, _1);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerRemoveEventDelegate,
  textLoader -> getString(string("IDS_BMD_TR")),towerRemoveEventType);
}

//genearte a new random map
void BoardManager::newMap(){
  if(mapFactory != NULL){
      mapFactory -> generateMap();
  }
  //set all inner boards to the newly generated ones
  setMapBoards();
}

//generate a new random map with a differnet set of customization options
void BoardManager::newMap(MapChoices * newCustomization){
  if(mapFactory != NULL){
    mapFactory -> setMapCustomizationChoices(newCustomization);
    mapFactory -> generateMap();
  }
  //set all inner boards to the newly generated ones
  setMapBoards();
}

//record all the map boards for the board manager to use
void BoardManager::setMapBoards(){
  floorGrid = mapFactory -> getFloor();
  aboveFloorGrid = mapFactory -> getAboveFloor();
  distances = mapFactory -> getDistances();

  //correct the distances for each path to reflect the distance to the exit
  //accounting only for the length of the path from the path tile to the exit
  //rather than the manhattan distance
  setPathDistanceToReflectRealDistance();
}

/*
 * Set the distance for each path tile  to reflect the distance  to the exit
 */
void BoardManager::setPathDistanceToReflectRealDistance(){

  //start with the position of the exit
  vector<int> exitPos = getExitPositions();
  int exitRow = exitPos.at(1);
  int exitCol = exitPos.at(0);
  vector<vector<int>> traveled (distances.size(), vector<int>(distances.at(0).size(),0));

  //recursively walk back from the exit and keep track of the distance traveled
  walkBackToEntries(exitRow, exitCol, 0, traveled);
}

/*
 * Recursively follow back from the pased row and col
 * and mark any path spaces with the correct distance
 */
 void BoardManager::walkBackToEntries(int row, int col, int distanceSoFar, vector<vector<int>> traveled){
   if(isInMap(row,col)){
     //mark the current position as having been visited
     traveled.at(row).at(col) = 1;

     for(vector<int> dir : dirs){
       int newRow = row + dir.at(0);
       int newCol = col + dir.at(1);
       //if this is not the direction we came from
       if(!(newRow == row && newCol == col)){
         //if this is still in the map
         if(isInMap(newRow, newCol)){
           //if this is a path
           if(isPath(newRow, newCol)){
             //if we have not gone here before
             //and the current marked distance is less
             if(traveled.at(newRow).at(newCol) == 0){
               walkBackToEntries(newRow, newCol, distanceSoFar+1, traveled);
             }
           }
         }
       }
     }
     //update the distance
     distances.at(row).at(col) = distanceSoFar;
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

  //the combined interger ID identifying the towers position
  int towerPosID = tcEventData -> towerPosID;
  //the string ID identifying the towers
  string towerTypeID = tcEventData -> towerTypeID;

  //get the numeric identifier for the tower type
  int towerTypeNum = textLoader -> getInteger(string("IDS_"+towerTypeID));

  //decode the ID so that it is a row and column
  int row = towerPosID / getYDim();
  int col = towerPosID % getXDim();

  //place the tower value on the above floor grid
  addTower(row,col,towerTypeNum);
}

/*
 * Add a tower to the specified position to the board that represents placed
 * towers and obstacles
 * @param row: row index of the tower
 * @param col: col index of the tower
 * @param towerTypeNum: the number associated with the type of tower being built
 */
void BoardManager::addTower(int row, int col, int towerTypeNum){
  aboveFloorGrid.at(row).at(col) = towerTypeNum;
}

/*
 * Handle a tower remove event
 * @param event: the tower remove event
 */
void BoardManager::handleTowerRemove(const EventInterface& event){
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
  int row = towerPosID / getYDim();
  int col = towerPosID % getXDim();

  //remove the tower value on the above floor grid
  clearTowerOrObstacle(row,col);

}

/*
 * Clear the tile of the obstacle or tower currently there
 * @param row: the row index for the obstacle/tower
 * @param col: the col index for the obstacle/tower
 */
void BoardManager::clearTowerOrObstacle(int row, int col){
  aboveFloorGrid.at(row).at(col) = emptyTile;
}

/*
 * @return true if no map is stored
 */
bool BoardManager::hasMap(){
  return floorGrid.size()!=0 || distances.size()!=0 || aboveFloorGrid.size()!=0;
}

/*
 * @return true if this position is in the map
 */
bool BoardManager::isInMap(int row, int col){
  return mapFactory -> isInMap(row, col);
}

/*
 * @return true if the selected grid has a tower
 */
bool BoardManager::isTower(int row, int col){
  assert(hasMap()==true);
  return aboveFloorGrid.at(row).at(col) > 0;
}

/*
 * @return true if the selected grid has a tower or an obstacle
 */
bool BoardManager::isTowerOrObstacle(int row, int col){
  assert(hasMap()== true);
  return aboveFloorGrid.at(row).at(col) > 0 || aboveFloorGrid.at(row).at(col) < -1;
}
/*
 * @return true if the selected grid has an entrance
 */
bool BoardManager::isEntrance(int row, int col){
  vector<int> entrances = getEntryPositions();

  for(int pair = 0; pair < entrances.size(); pair+=2){
    int pairRow = entrances.at(pair+1);
    int pairCol = entrances.at(pair);

    if(pairRow == row && pairCol == col){
      return true;
    }
  }
  return false;
}

/*
 * @return true if the selected grid has an exit
 */
bool BoardManager::isExit(int row, int col){
  assert(hasMap()== true);
  return aboveFloorGrid.at(row).at(col) == 0;
}
/*
 * @return true if the selected grid has a path
 */
bool BoardManager::isPath(int row, int col){
  assert(hasMap()== true);
  return floorGrid.at(row).at(col) > 0 ;
}
/*
 * @return true if the selected grid has a path
 */
bool BoardManager::isObstacle(int row, int col){
  assert(hasMap()== true);
  return aboveFloorGrid.at(row).at(col) < -1 ;
}


int BoardManager::getYDim(){
  assert(hasMap()== true);
  return mapFactory -> getYDim();
}
int BoardManager::getXDim(){
  assert(hasMap()== true);
  return mapFactory -> getXDim();
}

/*
 * @return MapChoices: all customizaton options for this map
 */
MapChoices&  BoardManager::getMapCustomizationChoices(){
  return mapFactory -> getMapCustomizationChoices();
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
  assert(hasMap()== true);
  return distances;
}
vector<int>const & BoardManager::getDistancesRow(int row){
  assert(hasMap()== true);
  return distances.at(row);
}
vector<int>const & BoardManager::getDistanceCol(int col){
  assert(hasMap()== true);
  static vector<int> distanceCol;
  distanceCol.clear();

  for(int row = 0; row < mapFactory -> getYDim(); row++){
    distanceCol.push_back(distances.at(row).at(col));
  }
  return distanceCol;
}

int BoardManager::getDistanceRowCol(int row, int col){
  assert(hasMap()== true);
  return distances.at(row).at(col);
}

vector<vector<int>>const & BoardManager::getAboveFloor(){
  assert(hasMap()== true);
  return aboveFloorGrid;
}
vector<int>const & BoardManager::getAboveFloorRow(int row){
  assert(hasMap()== true);
  return aboveFloorGrid.at(row);
}
vector<int>const & BoardManager::getAboveFloorCol(int col){
  assert(hasMap()== true);
  static vector<int> aboveFloorCol;
  aboveFloorCol.clear();

  for(int row = 0; row < mapFactory -> getYDim(); row++){
    aboveFloorCol.push_back(aboveFloorGrid.at(row).at(col));
  }
  return aboveFloorCol;
}
int BoardManager::getAboveFloorRowCol(int row, int col){
  assert(hasMap()== true);
  return aboveFloorGrid.at(row).at(col);
}

vector<vector<int>>const & BoardManager::getFloor(){
  assert(hasMap()== true);
  return floorGrid;
}
vector<int>const & BoardManager::getFloorRow(int row){
  assert(hasMap()== true);
  return floorGrid.at(row);
}
vector<int>const & BoardManager::getFloorCol(int col){
  assert(hasMap()== true);
  static vector<int> floorCol;
  floorCol.clear();

  for(int row = 0; row < mapFactory -> getYDim(); row++){
    floorCol.push_back(floorGrid.at(row).at(col));
  }
  return floorCol;
}
int BoardManager::getFloorRowCol(int row, int col){
  assert(hasMap()== true);
  return floorGrid.at(row).at(col);
}

vector<int>& BoardManager::getExitPositions(){
  assert(hasMap()==true);
  return mapFactory->getExitPos();
}

vector<int>& BoardManager::getEntryPositions(){
  assert(hasMap()== true);
  return mapFactory->getEntryPos();
}

unordered_map<int,pair<int,int>>& BoardManager::getAllObstacles(){
  assert(hasMap()== true);
  if(allObstacles.size() != 0){
    return allObstacles;
  }
  for(int i=0; i<getYDim(); i++){
    for(int j=0; j<getXDim(); j++){
      if(aboveFloorGrid.at(i).at(j) < -2){
        intPair pos (i,j);
        allObstacles.insert({aboveFloorGrid.at(i).at(j), pos});
      }
    }
  }
  return allObstacles;
}
