/*

  MapFactory.cpp

  Purpose: Generate a unique random grid map with obstacles, an exit, and path(s)
            to the exit

  @author Andrew Katson
*/

 #include "MapFactory.hpp"

/*
 * Initialize a map factory
 * @param mapCustomizationChoices: container with customization options for generation
 */
MapFactory::MapFactory(MapChoices *mapCustomizationChoices){
  this -> mapCustomizationChoices = unique_ptr<MapChoices>(mapCustomizationChoices);

  //generate the dimensions of the board using the cafeteria size choice
  generateDimensions();



  //set seed for random number generator from file rngs
  time_t t;
  PutSeed(time(&t));
  //PutSeed(822567306);
}


/*
 * set the dimensions for the map (a higher cafeteria choice is larger)
 * the minimum size is 6x6
 */
void MapFactory::generateDimensions(){
  int xDim = mapCustomizationChoices -> cafeteriaChoice * 6;
  int yDim = mapCustomizationChoices -> cafeteriaChoice * 6;

  //checks to ensure that the dimensions are never negative or 0
  if(xDim <= 0){
    xDim = 6;
  }
  if(yDim <= 0){
    yDim = 6;
  }
  this -> xDim = xDim;
  this -> yDim = yDim;
}

/*
 * make a map and fill the 2d vectors describing the map
 * with the appropriate values
 */
void MapFactory::generateMap(){
  for(int i = 0; i < 1; i++){
  //initializes all vector indicies to -1
  this -> initGridArrays();

  //initialize the floor pattern
  this -> makeFloor();

  //place an exit on all boards
  //in here we also set the distances grid
  this -> makeExit();

  //place an entry on all boards
  for(int e = 0; e < mapCustomizationChoices -> pathEntryChoice; e++){
    // add one because the path number should always start at 1 since 0
    // is the exit
    this -> makeEntry(e + 1);
  }

  //place obstacles on the board
  this -> makeObstacles();


  //initilize the array indicating whether an entry leads to the exit
  entrysToExit.resize(entryPos.size() /2);
  fill(entrysToExit.begin(), entrysToExit.end(), 0);


  //place a path for each entry
  for(int p = 0; p < entryPos.size() / 2; p++){
    // add one because the path number should always start at 1 since 0
    // is the exit
    this -> makePath(p + 1);
    //now this path leads to the exit
    entrysToExit.at(p) = 1;

  }


  //TODO remove when done checking grids
  //this -> printVector(this -> paths);
  //this -> printVector(this -> unavailableSpots);
  //this -> printVector(this -> distances);
  //this -> printVector(this -> floorGrid);
  //this -> printVector(this -> aboveFloorGrid);

  paths.clear();
  unavailableSpots.clear();
  distances.clear();
  floorGrid.clear();
  aboveFloorGrid.clear();
  exitPos.clear();
  entryPos.clear();
  entryDirections.clear();
}
}

/*
 * set all values in the grids to -1 as the default
 */
void MapFactory::initGridArrays(){

  //set each row to -1
  for(int i = 0; i < this -> yDim; i++) {
      this -> paths.push_back(vector<int>(this -> xDim, -1));
      this -> unavailableSpots.push_back(vector<int>(this -> xDim, -1));
      this -> distances.push_back(vector<int>(this -> xDim, -1));
      this -> floorGrid.push_back(vector<int>(this -> xDim, -1));
      this -> aboveFloorGrid.push_back(vector<int>(this -> xDim, -1));
      this -> markPathSoFar.push_back(vector<int>(this -> xDim, -1));
  }
}

/*
 * set the exit space on the board
 */
void MapFactory::makeExit(){
  //choose one of the four sides of the grid
  int chosenSide = (int)randomVariates -> Equilikely(0,3);

  //set the side that the exit sits on
  this -> exitDirection = Direction(chosenSide);

  /* choose the row or column that the exit will sit in on the
   * side selected. if you have selected the left or right side
   * then you know col = 0 or col = floorGrid[0].size() - 1 so the below
   * value will be the row. if you have selected Top or Bottom side
   * then you know row = 0 or row = floorGrid.size() - 1 so the below value
   * will be the col.
   */
   int indexChosen = this -> chooseIndexOfExit(chosenSide);

   //set a 0 on each grid where the exit should be
   placeExit(chosenSide, indexChosen);

}

/*
 * choose index of the exit that is determined by what side of the grid it will
 * sit on
 * @param side: the side of the exit (side < 2 is left or right, side >= 2 is up or down )
 * @return int: the index on the side chosen where the exit will be
 */
int MapFactory::chooseIndexOfExit(int side){
  //if this is the left or right side
  if(side < 2){
    return (int) randomVariates -> Equilikely(0, this -> floorGrid.size() - 1);
  }
  //if this is the Top or Bottom side
  else{
    return (int)randomVariates -> Equilikely(0, this -> floorGrid[0].size() - 1);
  }
}

/* set an exit marker (0) on each 2d array to show where the exit is
 * will switch the order of exitSide and exitIndexOnSide in [row][col]
 * notation to recognize that which side is chosen will determine
 * whether the index is the row or the column. i.e. if the left side (0)
 * is chosen then the index will be the row since the column will be the first
 * one.
 * @param exitSide: the side map of the exit
 * @param exitIndexOnSide: the index of the exit on its side
 */
void MapFactory::placeExit(int exitSide, int exitIndexOnSide){

  //set the stored exit position to be the row and column specified by the params
  // passed
  switch(exitSide){
      //left
      case 0:
        this -> exitPos.push_back(0);
        this -> exitPos.push_back(exitIndexOnSide);
        break;
      //right
      case 1:
        this -> exitPos.push_back(this -> floorGrid[0].size() - 1);
        this -> exitPos.push_back(exitIndexOnSide);
        break;
      //up
      case 2:
        this -> exitPos.push_back(exitIndexOnSide);
        this -> exitPos.push_back(0);
        break;
      //down
      case 3:
      default:
        this -> exitPos.push_back(exitIndexOnSide);
        this -> exitPos.push_back(this -> floorGrid.size() - 1);
        break;
  }

  //set a 0 at the index specified as exit in each of the grid arrays
  this -> paths[exitPos[1]][exitPos[0]] = 0;
  this -> distances[exitPos[1]][exitPos[0]] = 0;
  this -> floorGrid[exitPos[1]][exitPos[0]] = 0;
  this -> aboveFloorGrid[exitPos[1]][exitPos[0]] = 0;

  //make the distances before we set unavailable spots
  this -> makeDistances();

  //mark spaces on the grid as not allowing entry or obstacles to be placed
  this -> setUnavailableSpotsFromExit(exitPos[0], exitPos[1]);
}

/*
 * mark indicies as unavaiable given the exit position
 * @param exitXPos: the column index of the exit
 * @param exitYPos: the row index of the exit
 */
void MapFactory::setUnavailableSpotsFromExit(int exitXPos, int exitYPos){
  //the minimum distance any obstacle can be placed near the exit
  int minDistanceObstacle = 2;

  //the minimum distance any entry can be placed near the exit
  int minDistanceEntry = 6;

  for(int row = 0; row < yDim; row++){
    for(int col = 0; col < xDim; col++){
      if(distances.at(row).at(col) < minDistanceEntry){
        //if this is too close for even an obstacle to be placed
        if(distances.at(row).at(col) < minDistanceObstacle){
            unavailableSpots.at(row).at(col) = 1;
        }
        //if this is too close for an entry but not an obstacle
        else{
          unavailableSpots.at(row).at(col) = 0;
        }
      }
    }
  }
}


/*
 * set each entry on all the map grids
 * @param pathNumber: the numeric identifier for this path
 */
void MapFactory::makeEntry(int pathNumber){

  //vector to hold all the entries on the chosen side of the grid
  vector<int> entriesOnSide;

  //side that is furthest away (used only for special case of first path)
  Direction::Directions furthestAway;

  vector<Direction::Directions> otherThreeSides;
  int chosenSideIndex = -1;

  //if this the the first path it is ALWAYS placed on the side with the furthest
  //spot away to ensure at least one entry point can be used for the easy mode
  if(pathNumber == 1){
    furthestAway = entriesOnFurthestSide(entriesOnSide);
  }
  else{

    //get all three other directions that are not on the exit's side of the map
    otherThreeSides = this -> exitDirection.allOtherDirections(this -> exitDirection.facing);

    //shuffle the other sides so we will pick one random side each time
    random_shuffle(otherThreeSides.begin(), otherThreeSides.end());


    //check to make sure that there is room on one of the three sides for an entry
    if(this -> aSideIsNotFull(otherThreeSides)){
      //keep picking a side until you find one that can have an exit placed on it
      do {
        entriesOnSide.clear();
        //choose one of the three sides of the grid the exit is not on
        chosenSideIndex = (int)randomVariates -> Equilikely(0,2);

      }while(!(this ->  sideIsNotFull(otherThreeSides[chosenSideIndex], entriesOnSide)));

    }
    else{
      //return if there are no sides that can have entries placed on them
      return;
    }
  }
  /*
   * generate a value in the range of the possible entries on this side
   * then select one of these indicies
   */
   int index = (int) randomVariates -> Equilikely(0, entriesOnSide.size() - 1);
   int entryIndex = entriesOnSide.at(index);

   if(pathNumber == 1){
     //set a pathNumber on each grid where the first entry should be
     this -> placeEntry(furthestAway, entryIndex, pathNumber);
   }
   else{
     //set a pathNumber on each grid where the entry should be
     this -> placeEntry(otherThreeSides[chosenSideIndex], entryIndex, pathNumber);
   }
}

/*
 * special case for the first entry placed where the side with the
 * furthest distance is chosen and all the tiles on that are
 * poetential entry points
 * @param possibleEntries: a vector of integers with the possible indicies of entry on the furthest side
 * @return Directions: the direction (side) of the map which is the furthest side
 */
 Direction::Directions MapFactory::entriesOnFurthestSide(vector<int> &possibleEntries){
   Direction::Directions furthestSide;
   int maxAverageSumDistance = 0;
   int sideSumDistance = 0;
   int sideNumTiles = 0;

   vector<int> currSideEntries;
   int row = 0;
   int col = 0;

   //check the left and then right columns
   for(col = 0; col < xDim; col += xDim - 1){
     sideNumTiles = 0;
     sideSumDistance = 0;
     currSideEntries.clear();
     //check all the spaces on this row
     for(row = 0; row < yDim; row++){
       if(unavailableSpots.at(row).at(col) == -1){
         currSideEntries.push_back(col);
       }
       sideSumDistance += distances.at(row).at(col);
       sideNumTiles++;
     }
     int averageDistance = sideSumDistance / sideNumTiles;

     //if this side had a larger distance on average than the previous max
     //then set the new max average sum to this one
     //and copy over all the entries
     if(averageDistance > maxAverageSumDistance){
       maxAverageSumDistance = averageDistance;
       possibleEntries.clear();
       possibleEntries = currSideEntries;
       //if this is the left side then the furthest direction is the left
       if(col == 0){
         furthestSide = Direction::Left;
       }
       //else the right side
       else{
         furthestSide = Direction::Right;
       }
     }
   }


   //check the top and bottom rows
   for(row = 0; row < yDim; row += yDim - 1){
     sideNumTiles = 0;
     sideSumDistance = 0;
     currSideEntries.clear();
     //check all the spaces on this col
     for(col = 0; col < xDim; col++){
       if(unavailableSpots.at(row).at(col) == -1){
         currSideEntries.push_back(col);
       }
       sideSumDistance += distances.at(row).at(col);
       sideNumTiles++;
     }
     int averageDistance = sideSumDistance / sideNumTiles;

     //if this side had a larger distance on average than the previous max
     //then set the new max average sum to this one
     //and copy over all the entries
     if(averageDistance > maxAverageSumDistance){
       maxAverageSumDistance = averageDistance;
       possibleEntries.clear();
       possibleEntries = currSideEntries;
       //if this is the left side then the furthest direction is the top
       if(col == 0){
         furthestSide = Direction::Top;
       }
       //else the bottom side
       else{
         furthestSide = Direction::Bottom;
       }
     }
   }
   return furthestSide;
 }

/*
 * return true is at least one of the three sides the exit is not on
 * can have an entry placed on it
 * @param sides: a vector with each side of the map
 * @param bool: true if ANY side is not full(meaning not all marked unavaiable)
 */
bool MapFactory::aSideIsNotFull(vector<Direction::Directions> &sides){
  //vector used to satisfy parameters without having to make a new version of
  // the sideIsNotFull function
  vector<int> notUsed;
  for(Direction::Directions side : sides){
    if(this -> sideIsNotFull(side, notUsed)){
      return true;
    }
  }
  return false;
}

/*
 * return true if the side specified has room for an entry on it
 * also fill possibleEntries with the indicies of poetential places
 * for an entry
 * @param side: the current side of the board
 * @param possibleEntries: used to store the indicies on the side IF it is not full
 * @return bool: true if the side has available spots
 */
bool MapFactory::sideIsNotFull(Direction::Directions &side, vector<int> &possibleEntries){
  switch(side){
      case 0:
        return this -> leftSideIsNotFull(possibleEntries);
        break;
      case 1:
        return this -> rightSideIsNotFull(possibleEntries);
        break;
      case 2:
        return this -> topSideIsNotFull(possibleEntries);
        break;
      case 3:
      default:
        return this -> bottomSideIsNotFull(possibleEntries);
        break;
  }
  return false;
}

/*
 * check the left side for having a space for an entry and fill the vector
 * with possible entry indicies if there are spaces
 * @param possibleEntries: vector to hold all the possible entries on this side that are open
 * @return bool: true if the left side has open spaces
 */
bool MapFactory::leftSideIsNotFull(vector<int> &possibleEntries){
  bool retVal = false;
  for(int i = 0; i < yDim; i++){
    if(unavailableSpots.at(i).at(0) == -1){
      retVal = true;
      possibleEntries.push_back(i);
    }
  }
  return retVal;

}

/*
 * check the right side for having a space for an entry and fill the vector
 * with possible entry indicies if there are spaces
 * @param possibleEntries: vector to hold all the possible entries on this side that are open
 * @return bool: true if the right side has open spaces
 */
bool MapFactory::rightSideIsNotFull(vector<int> &possibleEntries){
  bool retVal = false;
  for(int i = 0; i < yDim; i++){
    if(unavailableSpots.at(i).at(xDim - 1) == -1){
      possibleEntries.push_back(i);
      retVal = true;
    }
  }
  return retVal;

}

/*
 * check the top side for having a space for an entry and fill the vector
 * with possible entry indicies if there are spaces
 * @param possibleEntries: vector to hold all the possible entries on this side that are open
 * @return bool: true if the top side has open spaces
 */
bool MapFactory::topSideIsNotFull(vector<int> &possibleEntries){
  bool retVal = false;
  for(int i = 0; i < xDim; i++){
    if(unavailableSpots.at(0).at(i) == -1){
      possibleEntries.push_back(i);
      retVal = true;
    }
  }
  return retVal;

}

/*
 * check the bottom side for having a space for an entry and fill the vector
 * with possible entry indicies if there are spaces
 * @param possibleEntries: vector to hold all the possible entries on this side that are open
 * @return bool: true if the bottom side has open spaces
 */
bool MapFactory::bottomSideIsNotFull(vector<int> &possibleEntries){
  bool retVal = false;
  for(int i = 0; i < xDim; i++){
    if(unavailableSpots.at(yDim -1 ).at(i) == -1){
      possibleEntries.push_back(i);
      retVal = true;
    }
  }
  return retVal;

}


/*
 * set an entry marker (pathNumberOfEntry) on each 2d array to show where the entry is
 * will switch the order of entrySide and entryIndexOnSide in [row][col]
 * notation to recognize that which side is chosen will determine
 * whether the index is the row or the column. i.e. if the left side (0)
 * is chosen then the index will be the row since the column will be the first
 * one.
 * @param entrySide: the direction (side) of the entry
 * @param entryIndexOnSide: the index on the entry side of the entry
 * @param pathNumberOfEntry: the numeric identifier for the current path
 */
void MapFactory::placeEntry(Direction::Directions &entrySide, int entryIndexOnSide,
                            int pathNumberOfEntry){

  //set the stored entry position to be the row and column specified by the params
  // passed
  switch(entrySide){
      case Direction::Left:
        this -> entryPos.push_back(0);
        this -> entryPos.push_back(entryIndexOnSide);
        break;
      case Direction::Right:
        this -> entryPos.push_back(this -> floorGrid[0].size() - 1);
        this -> entryPos.push_back(entryIndexOnSide);
        break;
      case Direction::Top:
        this -> entryPos.push_back(entryIndexOnSide);
        this -> entryPos.push_back(0);
        break;
      case Direction::Bottom:
      default:
        this -> entryPos.push_back(entryIndexOnSide);
        this -> entryPos.push_back(this -> floorGrid.size() - 1);
        break;
  }

  //set a pathNumberOfEntry at the index specified as entry in the path grid
  //we know that the two most recently pushed entry positions correspond to
  // the x and y of the newest entry
  this -> paths[entryPos[entryPos.size() - 1]][entryPos[entryPos.size() - 2]] = pathNumberOfEntry;
  //mark the entry on the floor grid that will draw the textures
  //will have the path number on it (will always be positive) should allow
  //for different paths to have different textures
  this -> floorGrid[entryPos[entryPos.size() - 1]][entryPos[entryPos.size() - 2]]  = pathNumberOfEntry;

  //set the direction of this entrance
  entryDirections.push_back(Direction(entrySide));

  //mark the spots around this entrance as unavailabe for future entry positions
  this -> setUnavailableSpotsFromEntry(entryPos[entryPos.size() - 2], entryPos[entryPos.size() - 1]);
}

/*
 * mark indicies as unavaiable for an entry given the entry position
 * @param entryXPos: the column index of the entry
 * @param entryYPos: the row index of the entry
 */
void MapFactory::setUnavailableSpotsFromEntry(int entryXPos, int entryYPos){
  this -> unavailableSpots.at(entryYPos).at(entryXPos) = 0;
  //left side
  if (entryXPos == 0){
    this -> setUnavailableSpotsFromLeftEntry(entryXPos, entryYPos);
  }
  //right side
  else if(entryXPos == xDim -1){
    this -> setUnavailableSpotsFromRightEntry(entryXPos, entryYPos);
  }
  //Top side
  else if(entryYPos == 0){
    this -> setUnavailableSpotsFromTopEntry(entryXPos, entryYPos);
  }
  //Bottom side
  else{
    this -> setUnavailableSpotsFromBottomEntry(entryXPos, entryYPos);
  }
}

/*
 * mark indicies as unavaiable for an entry given the entry position is on the left side
 * @param entryXPos: the column index of the entry
 * @param entryYPos: the row index of the entry
 */
void MapFactory::setUnavailableSpotsFromLeftEntry(int entryXPos, int entryYPos){
  //we want to set the value above this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a column over
  if(entryYPos - 1 >= 0){
    unavailableSpots.at(entryYPos - 1).at(entryXPos) = 0;
  }
  else{
    unavailableSpots.at(entryYPos).at(entryXPos + 1) = 0;
  }
  //we want to set the value below this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a column over
  if(entryYPos + 1 < yDim ){
    unavailableSpots.at(entryYPos + 1).at(entryXPos) = 0;
  }
  else{
    unavailableSpots.at(entryYPos).at(entryXPos + 1) = 0;
  }
}

/*
 * mark indicies as unavaiable for an entry given the entry position is on the right side
 * @param entryXPos: the column index of the entry
 * @param entryYPos: the row index of the entry
 */
void MapFactory::setUnavailableSpotsFromRightEntry(int entryXPos, int entryYPos){
  //we want to set the value above this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a column back
  if(entryYPos - 1 >= 0){
    unavailableSpots.at(entryYPos - 1).at(entryXPos) = 0;
  }
  else{
    unavailableSpots.at(entryYPos).at(entryXPos - 1) = 0;
  }
  //we want to set the value below this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a column back
  if(entryYPos + 1 < yDim){
    unavailableSpots.at(entryYPos + 1).at(entryXPos) = 0;
  }
  else{
    unavailableSpots.at(entryYPos).at(entryXPos - 1) = 0;
  }
}

/*
 * mark indicies as unavaiable for an entry given the entry position is on the Top side
 * @param entryXPos: the column index of the entry
 * @param entryYPos: the row index of the entry
 */
void MapFactory::setUnavailableSpotsFromTopEntry(int entryXPos, int entryYPos){
  //we want to set the value to the left of this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a row down
  if(entryXPos - 1 >= 0){
    unavailableSpots.at(entryYPos).at(entryXPos - 1) = 0;
  }
  else{
    unavailableSpots.at(entryYPos - 1).at(entryXPos) = 0;
  }
  //we want to set the value below this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a row down
  if(entryXPos + 1 < xDim){
    unavailableSpots.at(entryYPos).at(entryXPos + 1) = 0;
  }
  else{
    unavailableSpots.at(entryYPos - 1).at(entryXPos) = 0;
  }
}

/*
 * mark indicies as unavaiable for an entry given the entry position is on the Bottom side
 * @param entryXPos: the column index of the entry
 * @param entryYPos: the row index of the entry
 */
void MapFactory::setUnavailableSpotsFromBottomEntry(int entryXPos, int entryYPos){
  //we want to set the value to the left of this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a row up
  if(entryXPos - 1 >= 0){
    unavailableSpots.at(entryYPos).at(entryXPos - 1) = 0;
  }
  else{
    unavailableSpots.at(entryYPos + 1).at(entryXPos) = 0;
  }
  //we want to set the value below this space to indicate it cannot be used
  //however if it cannot be we set the space touching this one a row up
  if(entryXPos + 1 < xDim){
    unavailableSpots.at(entryYPos).at(entryXPos + 1) = 0;
  }
  else{
    unavailableSpots.at(entryYPos + 1).at(entryXPos) = 0;
  }
}

/*
 * make the floor with an alternating pattern of negative numbers to
 * set everything as a non-path tile (except the exit which is marked already)
 */
void MapFactory::makeFloor(){
  for(int row = 0; row < yDim; row++){
    for(int col = 0; col < xDim; col++){
      if(floorGrid.at(row).at(col) != 0){
        if(col % 2 == 0){
          floorGrid.at(row).at(col) = 2 * (mapCustomizationChoices -> cafeteriaChoice - 1) - 1;
        }
        else{
          floorGrid.at(row).at(col) = 2 * (mapCustomizationChoices -> cafeteriaChoice - 1) - 2;
        }
      }
    }
  }
}

/*
 * calculate the distance from the exit for every tile on the grid
 */
void MapFactory::makeDistances(){
  int exitRow = exitPos[1];
  int exitCol = exitPos[0];

  for(int row = 0; row < yDim; row++){
    for(int col = 0; col < xDim; col++){
      if(!(row == exitRow && col == exitCol)){
        //Manhattan Distance
        distances.at(row).at(col) = abs(exitRow - row) + abs(exitCol - col);
      }
    }
  }
}


/*
 * make a path for the specified path on the board
 * @param pathNumber: the numeric identifier for the path
 */
void MapFactory::makePath(int pathNumber){
  //grab the starting row and column
  int currRowNum = entryPos.at(2*(pathNumber - 1) + 1);
  int currColNum = entryPos.at(2*(pathNumber - 1));
  int lastRow = -1;
  int lastCol = -1;

  //a variable that tells whether this is the first step or not
  bool firstStep = true;

  //the direction the entry faces in
  Direction::Directions entryDirection = entryDirections[pathNumber - 1].facing;
  //the direction we cannot expand towards
  Direction::Directions directionExpandedFrom = entryDirection;
  //the directions we can expand towards
  vector<Direction::Directions> directionsCanExpand = entryDirections[pathNumber -1].allOtherDirections(directionExpandedFrom);
  //the direction opposite the exit (going this way will get the path to the exit the fastest)
  Direction::Directions oppositeExit = exitDirection.oppositeDirection(exitDirection.facing);

  //keep track of all non exit paths this path touches along the way to the exit
  vector<int> allNonExitPaths;

  //to keep track of the last shortest direction in case
  // we get to a corner where the only way to the exit is by taking a side path
  int lastShortestDistance = 0x1FFF;
  //while we have not reached another path or the exit tile
  while(paths.at(currRowNum).at(currColNum) < 0 || paths.at(currRowNum).at(currColNum) == pathNumber
        && !(connectedWithExit(currRowNum, currColNum))){

      //if the newest path tile is touching a different path then we are done
      //but only if that path leads to an exit
        if(connectedWithExitPath(currRowNum, currColNum, pathNumber)){
          break;
        }
      //if the newest path tile is touching a differnt path and it is not an
      //exit path than we add it to the list of paths to exit because we can
      //assume that this current path will reach the exit
      vector<int> connectedNonExitPaths = connectedWithNonExitPath(currRowNum, currColNum, pathNumber);
      if(connectedNonExitPaths.size() != 0){
        for(int otherPath : connectedNonExitPaths){
          allNonExitPaths.push_back(otherPath);
        }
      }

      //get all the possible steps
      vector<Direction::Directions> nextSteps;

      //current space distance from the exit
      int currDistance = distances.at(currRowNum).at(currColNum);

      //count the number of times we look for a shortest step
      int timesAround = 0;
      while(nextSteps.size() == 0){

        //get the next posssible steps the path can take
        nextSteps = calcNextShortestStep(currRowNum, currColNum, lastRow, lastCol);

        if(timesAround > 2){
          //if we go around twice we should remove the obstacle in the shortest distance
          removeObstacleInShortestStep(currRowNum, currColNum);
          timesAround = 0;
        }
        timesAround++;
      }
      //shuffle them
      random_shuffle(nextSteps.begin(), nextSteps.end());
      int randomStep = randomVariates -> Equilikely(0, nextSteps.size() - 1);

      //pick a random direction to step in from the possible options
      Direction::Directions expandInto = nextSteps.at(randomStep);

      //store the last row and column we came from
      lastRow = currRowNum;
      lastCol = currColNum;

      //update the row to the exapnded direction
      currRowNum = expandInRow(currRowNum, expandInto);
      //update the column to the exapnded direction
      currColNum = expandInCol(currColNum, expandInto);

      //update the last shortest distance to be the distance of the current space
      lastShortestDistance = distances.at(currRowNum).at(currColNum);

      //place a path value at the current tile
      paths.at(currRowNum).at(currColNum) = pathNumber;

      //place the path indicator on the floor grid array used for textures
      floorGrid.at(currRowNum).at(currColNum) = pathNumber;

      //mark this spot as unavailable for use later
      unavailableSpots.at(currRowNum).at(currRowNum) = 0;

      //reset the direction we exaneded from
      directionExpandedFrom = expandInto;

      //once we have taken a step
      firstStep = false;
  }

  //finally take all non exit paths we touched and mark them as exit paths
  if(allNonExitPaths.size() != 0){
    for(int nonExitPath : allNonExitPaths){
      entrysToExit.at(nonExitPath - 1) = 1;
    }
  }
}
/*
 * return true if the passed tile is connected to the exit
 * @param row: row index (Y)
 * @param col: column index (X)
 * @return bool: whether this tile is connected to the exit
 */
bool MapFactory::connectedWithExit(int row, int col){
  //check left
  if(col - 1 >= 0){
    if(paths.at(row).at(col - 1) == 0){
      return true;
    }
  }
  if(col + 1 < xDim){
    //check right
    if(paths.at(row).at(col + 1) == 0){
      return true;
    }
  }
  if(row - 1 >= 0){
    //check top
    if(paths.at(row - 1).at(col) == 0){
      return true;
    }
  }
  if(row + 1 < yDim){
    //check bottom
    if( paths.at(row + 1).at(col) == 0){
      return true;
    }
  }

  return false;
}


/*
 * checks to see if there is a path connected to this tile that is not
 * on the same path as the path specified and that path is an exit path
 * @param row: row index (Y)
 * @param col: column index (X)
 * @param path: the numeric path identifier
 * @return bool: whether this tile is connected to the exit through another path
 */
 bool MapFactory::connectedWithExitPath(int row, int col, int path){
   bool retVal = false;
   //check left
   if(col - 1 >= 0){
     if(paths.at(row).at(col - 1) != path && paths.at(row).at(col - 1) > 0){
       retVal = (bool) entrysToExit.at(paths.at(row).at(col - 1) - 1);
     }
   }
   if(col + 1 < xDim){
     //check right
     if(paths.at(row).at(col + 1) != path && paths.at(row).at(col + 1) > 0){
       retVal = (bool) entrysToExit.at(paths.at(row).at(col + 1) - 1);
     }
   }
   if(row - 1 >= 0){
     //check top
     if(paths.at(row - 1).at(col) != path && paths.at(row - 1).at(col) > 0){
       retVal = (bool) entrysToExit.at(paths.at(row - 1).at(col) - 1);
     }
   }
   if(row + 1 < yDim){
     //check bottom

     if(paths.at(row + 1).at(col) != path && paths.at(row + 1).at(col) > 0){
       retVal = (bool) entrysToExit.at(paths.at(row + 1).at(col) - 1);
     }
   }

   return retVal;
 }

 /*
  * checks to see if there is a path connected to this tile that is not
  * on the same path as the path specified and that path is not an exit path
  * returns the path number of the path
  * @param row: row index (Y)
  * @param col: column index (X)
  * @param path: the numeric identifier for the path
  * @return vector<int>: the numeric identifiers for all connected non exit paths
  */
  vector<int> MapFactory::connectedWithNonExitPath(int row, int col, int path){
    vector<int> nonExitPaths;
    bool exitPath = false;
    //check left
    if(col - 1 >= 0){
      if(paths.at(row).at(col - 1) != path && paths.at(row).at(col - 1) > 0){
        exitPath = (bool) entrysToExit.at(paths.at(row).at(col - 1) - 1);
        if(!exitPath){
          nonExitPaths.push_back(paths.at(row).at(col - 1));
        }
      }
    }
    if(col + 1 < xDim){
      //check right
      if(paths.at(row).at(col + 1) != path && paths.at(row).at(col + 1) > 0){
        exitPath = (bool) entrysToExit.at(paths.at(row).at(col + 1) - 1);
        if(!exitPath){
          nonExitPaths.push_back(paths.at(row).at(col + 1));
        }
      }
    }
    if(row - 1 >= 0){
      //check top
      if(paths.at(row - 1).at(col) != path && paths.at(row - 1).at(col) > 0){
        exitPath = (bool) entrysToExit.at(paths.at(row - 1).at(col) - 1);
        if(!exitPath){
          nonExitPaths.push_back(paths.at(row - 1).at(col));
        }
      }
    }
    if(row + 1 < yDim){
      //check bottom
      if(paths.at(row + 1).at(col) != path && paths.at(row + 1).at(col) > 0){
        exitPath = (bool) entrysToExit.at(paths.at(row + 1).at(col) - 1);
        if(!exitPath){
          nonExitPaths.push_back(paths.at(row + 1).at(col));
        }
      }
    }

    return nonExitPaths;
  }

 /*
  * return the direction of the next shortest step
  * @param row: row index (Y)
  * @param col: column index (X)
  * @param lastRow: last col we were at
  * @param lastCol: last col we were at
  * @return vector<Direction::Directions>: what directions are considered shortest steps
  */
  vector<Direction::Directions> MapFactory::calcNextShortestStep(int row, int col, int lastRow, int lastCol){
    int topDist = 0x1FFF;
    int bottomDist = 0x1FFF;
    int leftDist = 0x1FFF;
    int rightDist = 0x1FFF;

    //the numeric indicator of the path
    int path = paths.at(row).at(col);

    vector<Direction::Directions> shortestSteps;

    //we do not check last row and last col if this was the first move
    if(lastRow != -1 && lastCol != -1){
      //get the distances in all direcitons that are not blocked
      //check left
      if(col - 1 >= 0){
        if(aboveFloorGrid.at(row).at(col - 1) > -2 && paths.at(row).at(col-1) != path){
          if(!connectedWithSamePath(row, col-1, row, col, path)){
            leftDist = distances.at(row).at(col - 1);
          }
        }
      }
      //check right
      if(col + 1 < xDim){
        if(aboveFloorGrid.at(row).at(col + 1) > -2 && paths.at(row).at(col+1) != path){
          if(!connectedWithSamePath(row, col+1, row, col, path)){
            rightDist = distances.at(row).at(col + 1);
          }
        }
      }
      //check top
      if(row - 1 >= 0){
        if(aboveFloorGrid.at(row - 1).at(col) > -2 && paths.at(row-1).at(col) != path){
          if(!connectedWithSamePath(row-1, col, row, col, path)){
            topDist = distances.at(row - 1).at(col);
          }
        }
      }
      //check bottom
      if(row + 1 < yDim){
        if(aboveFloorGrid.at(row + 1).at(col) > -2 && paths.at(row+1).at(col) != path){
          if(!connectedWithSamePath(row+1, col, row, col, path)){
            bottomDist = distances.at(row + 1).at(col);
          }
        }
      }
    }
    else{
      //get the distances in all direcitons that are not blocked
      //check left
      if(col - 1 >= 0){
        if(aboveFloorGrid.at(row).at(col - 1) > -2){
          if(!connectedWithSamePath(row, col-1, row, col, path)){
            leftDist = distances.at(row).at(col - 1);
          }
        }
      }
      //check right
      if(col + 1 < xDim){
        if(aboveFloorGrid.at(row).at(col + 1) > -2){
          if(!connectedWithSamePath(row, col+1, row, col, path)){
            rightDist = distances.at(row).at(col + 1);
          }
        }
      }
      //check top
      if(row - 1 >= 0){
        if(aboveFloorGrid.at(row - 1).at(col) > -2){
          if(!connectedWithSamePath(row-1, col, row, col, path)){
            topDist = distances.at(row - 1).at(col);
          }
        }
      }
      //check bottom
      if(row + 1 < yDim){
        if(aboveFloorGrid.at(row + 1).at(col) > -2){
          if(!connectedWithSamePath(row+1, col, row , col, path)){
            bottomDist = distances.at(row + 1).at(col);
          }
        }
      }
    }

    int shortestDist = min(leftDist, min(rightDist, min(topDist, bottomDist)));

    //if there was no adequate direction to step in
    if(shortestDist == 0x1FFF){
      return shortestSteps;
    }

    //find out which distance is the shortest and add the distance correspoonding to it
    //to the vector of the possible shortets distances

    if(shortestDist == leftDist){
      shortestSteps.push_back(Direction::Left);
    }
    if(shortestDist == rightDist){
      shortestSteps.push_back(Direction::Right);
    }
    if(shortestDist == topDist){
      shortestSteps.push_back(Direction::Top);
    }
    if(shortestDist == bottomDist){
      shortestSteps.push_back(Direction::Bottom);
    }

    return shortestSteps;
  }

  /*
   * @param newrow: the row index in the direction we are expanding (Y)
   * @param newcol: the col index in the direction we are expanding (X)
   * @param row: row index
   * @param col: col index
   * @param path: the numeric path indentifier
   * @return bool: whether the new row and column is touching the same path we are on
   */
 bool MapFactory::connectedWithSamePath(int newrow, int newcol, int row, int col, int path){

   //TODO SET TO ALWAYS FALSE BECAUSE THIS WILL CAUSE A WERID STEP FUNCTION
   return false;
   cout << "Same path " << endl;
   cout << path << endl;
   cout << row << endl;
   cout << col << endl;
   cout << "NEW" << endl;
   cout << newrow << endl;
   cout << newcol << endl;
   printVector(paths);
   printVector(aboveFloorGrid);
   printVector(distances);

   int rowMinusOne = row -1;
   int rowPlusOne = row +1;
   int colMinusOne = col -1;
   int colPlusOne = col + 1;

   bool rowMinusOneIn = rowIsInMap(rowMinusOne);
   bool rowPlusOneIn = rowIsInMap(rowPlusOne);
   bool colMinusOneIn = colIsInMap(colMinusOne);
   bool colPlusOneIn = colIsInMap(colPlusOne);

   if(rowMinusOneIn){
     if(!(rowMinusOne == row && newcol == col)){
       if(paths.at(rowMinusOne).at(newcol) == path){
         cout << "TOP" << endl;
         cout << rowMinusOne << " " << newcol << endl;
         return true;
       }
     }
   }
   if(rowPlusOneIn){
     if(!(rowPlusOne == row && newcol == col)){
       if(paths.at(rowPlusOne).at(newcol) == path){
         cout << "BOTTOM" << endl;
         cout << rowPlusOne << " " << newcol << endl;
         return true;
       }
     }
   }
   if(colMinusOneIn){
     if(!(newrow == row && colMinusOne == col)){
       if(paths.at(newrow).at(colMinusOne) == path){
         cout << "LEFT" << endl;
         cout << newrow << " " << colMinusOne << endl;
         return true;
       }
     }
   }
   if(colPlusOneIn){
     if(!(newrow == row && colPlusOne == col)){
       if(paths.at(newrow).at(colPlusOne) == path){
         cout << "RIGHT" << endl;
         cout << newrow << " " << colPlusOne << endl;
         return true;
       }
     }
   }
   return false;
 }

/*
 * Remove the obstacle in the shortest distance direction where there is one
 * @param row: row index (Y)
 * @param col: col index (X)
 */
void MapFactory::removeObstacleInShortestStep(int row, int col){
  int rowMinusOne = row -1;
  int rowPlusOne = row +1;
  int colMinusOne = col -1;
  int colPlusOne = col + 1;

  bool rowMinusOneIn = rowIsInMap(rowMinusOne);
  bool rowPlusOneIn = rowIsInMap(rowPlusOne);
  bool colMinusOneIn = colIsInMap(colMinusOne);
  bool colPlusOneIn = colIsInMap(colPlusOne);

  int topDist = 0x1FFF;
  int bottomDist = 0x1FFF;
  int leftDist = 0x1FFF;
  int rightDist = 0x1FFF;

  if(rowMinusOneIn){
    if(aboveFloorGrid.at(rowMinusOne).at(col) < -1){
      topDist = distances.at(rowMinusOne).at(col);
    }
  }
  if(rowPlusOneIn){
    if(aboveFloorGrid.at(rowPlusOne).at(col) < -1){
      bottomDist = distances.at(rowPlusOne).at(col);
    }
  }
  if(colMinusOneIn){
    if(aboveFloorGrid.at(row).at(colMinusOne) < -1){
      leftDist = distances.at(row).at(colMinusOne);
    }
  }
  if(colPlusOneIn){
    if(aboveFloorGrid.at(row).at(colPlusOne) < -1){
      rightDist = distances.at(row).at(colPlusOne);
    }
  }

  int shortestDist = min(leftDist, min(rightDist, min(topDist, bottomDist)));
  //find out which distance is the shortest and remove the obstacle
  if(shortestDist == leftDist){
    aboveFloorGrid.at(row).at(colMinusOne) = -1;
  }
  if(shortestDist == rightDist){
    aboveFloorGrid.at(row).at(colPlusOne) = -1;
  }
  if(shortestDist == topDist){
    aboveFloorGrid.at(rowMinusOne).at(col) = -1;

  }
  if(shortestDist == bottomDist){
    aboveFloorGrid.at(rowPlusOne).at(col) = -1;
  }
}

 /*
  * return a new row number that is expanded in the specified direction
  * @param row: index of the row (Y)
  * @param expandDirection: the direction the path is expanding into
  * @return int: the new row index
  */
int MapFactory::expandInRow(int row, Direction::Directions expandDirection){
  switch(expandDirection){
    case Direction::Left:
      return row;
    case Direction::Right:
      return row;
    case Direction::Top:
      return row - 1;
    case Direction::Bottom:
    default:
      return row + 1;
  }
}
  /*
   * retunr a new col number that is exapnded in the specified direction
   * @param col: index of the column (X)
   * @param expandDirection: the direction the path is expanding into
   * @return int: the new col index
   */
 int MapFactory::expandInCol(int col, Direction::Directions expandDirection){
   switch(expandDirection){
     case Direction::Left:
      return col - 1;
     case Direction::Right:
      return col + 1;
     case Direction::Top:
      return col;
     case Direction::Bottom:
     default:
      return col;
   }
 }

 /*
  * Search through the hash table of path adjacinet tiles until we find one
  * place an obstacle, and repeat until no new obstacles can or need to be placed
  */
void MapFactory::makeObstacles(){

  int placedObstacles = 0;
  int placedInvisibleObstacles = 0;
  int possiblePlacements = countPossibleObstaclePositions();

  int randRowChosen = (int) randomVariates -> Equilikely(1, yDim-2);
  int randColChosen = (int) randomVariates -> Equilikely(1, xDim-2);

  //place obstacles until we have hit the specified number
  //or there are no more spaces
  while(placedObstacles < mapCustomizationChoices -> obstacleChoice &&
        placedObstacles < possiblePlacements){
    randRowChosen = (int) randomVariates -> Equilikely(1, yDim-2);
    randColChosen = (int) randomVariates -> Equilikely(1, xDim-2);

    //if there is already an obstacle there then do not place one
    //or is the space is marked off
    if (aboveFloorGrid.at(randRowChosen).at(randColChosen) <= -2 ||
        unavailableSpots.at(randRowChosen).at(randColChosen) == 1 || completesWings(randRowChosen, randColChosen)){
      continue;
    }

    //randomly decide if this obstacle is actually invisible and does
    //not count towards the total number of obstacles
    int isInvisible = randomVariates -> Equilikely(0,3);
    if(isInvisible > 2){
      aboveFloorGrid.at(randRowChosen).at(randColChosen) = -2;
      placedInvisibleObstacles++;
      possiblePlacements--;
      continue;
    }

    //place an obstacle at the chosen row and column
    aboveFloorGrid.at(randRowChosen).at(randColChosen) = -3;

    //vector where each index corresponds to a true (1) or false (1)
    //for left, right, top, bottom, top left, top right, bottom left, bottom right
    //and determines which sides around this obstacle can be blocked for future
    //placements (allows for multiple length or side obstacles)
    vector<int> blockedSides(8);
    setBlockedSides(blockedSides);

    //mark any spaces adjacient to the obstacle as unavaialble
    //for future path or entry or obstace placement
    //get the updated number of placement options
    possiblePlacements = markUnavailableSpotsNearObstacle(randRowChosen, randColChosen, possiblePlacements, blockedSides);

    placedObstacles++;
  }


  //place invisible obstacles if more need to be placed
  placeRemainingInvisibleObstacles(placedInvisibleObstacles, possiblePlacements);
}

/*
 * count possible places obstacles can go
 * @return int: the number of possible places an obstacle can go
 */
 int MapFactory::countPossibleObstaclePositions(){
   int count = 0;
   for(int row = 0; row < yDim; row++){
     for(int col = 0; col < xDim; col++){
       if(unavailableSpots.at(row).at(col) != 1){
         count++;
       }
     }
   }
   return count;
 }

 /*
  * Checks if the passed potential obstacle position would
  * complete a pattern that allows a path to get to a space between three obstacles
  * that would trap it:    *
  *                      *   *
  * that is called wings
  * @param row: row index (Y)
  * @param col: col index (X)
  * @return bool: whether this placement would result in wings
  */
 bool MapFactory::completesWings(int row, int col){
   int rowMinusOne = row -1;
   int rowMinusTwo = row -2;
   int rowPlusOne = row +1;
   int rowPlusTwo = row+2;
   int colMinusOne = col -1;
   int colMinusTwo = col -2;
   int colPlusOne = col + 1;
   int colPlusTwo = col + 2;

   bool rowMinusOneIn = rowIsInMap(rowMinusOne);
   bool rowMinusTwoIn = rowIsInMap(rowMinusTwo);
   bool rowPlusOneIn = rowIsInMap(rowPlusOne);
   bool rowPlusTwoIn = rowIsInMap(rowPlusTwo);
   bool colMinusOneIn = colIsInMap(colMinusOne);
   bool colMinusTwoIn = colIsInMap(colMinusTwo);
   bool colPlusOneIn = colIsInMap(colPlusOne);
   bool colPlusTwoIn = colIsInMap(colPlusTwo);

   //If we have two obstacles in a wing pattern that would be completeed
   //if the current row and col were used for a new obstacle then we return true
   if(rowMinusOneIn && colPlusOneIn && colPlusTwoIn){
     if(aboveFloorGrid.at(rowMinusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(row).at(colPlusTwo)){
       return true;
     }
   }
   if(rowMinusOneIn && colMinusOneIn && colMinusTwoIn){
     if(aboveFloorGrid.at(rowMinusOne).at(colMinusOne) <-1 && aboveFloorGrid.at(row).at(colMinusTwo)){
       return true;
     }
   }
   if(rowPlusOneIn && colPlusOneIn && colPlusTwoIn){
     if(aboveFloorGrid.at(rowPlusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(row).at(colPlusTwo)){
       return true;
     }
   }
   if(rowPlusOneIn && colMinusOneIn && colMinusTwoIn){
     if(aboveFloorGrid.at(rowPlusOne).at(colMinusOne) <-1 && aboveFloorGrid.at(rowMinusOne).at(colMinusTwo)){
       return true;
     }
   }
   if(rowMinusOneIn && colPlusOneIn && colMinusOneIn){
     if(aboveFloorGrid.at(rowPlusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(rowMinusOne).at(colMinusOne)){
       return true;
     }
   }
   if(rowPlusOneIn && colPlusOneIn && colMinusOneIn){
     if(aboveFloorGrid.at(rowPlusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(rowPlusOne).at(colMinusOne)){
       return true;
     }
   }
   if(rowMinusOneIn && rowPlusOneIn && colPlusOneIn){
     if(aboveFloorGrid.at(rowMinusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(rowPlusOne).at(colPlusOne)){
       return true;
     }
   }
   if(rowMinusOneIn && rowPlusOneIn && colMinusOneIn){
     if(aboveFloorGrid.at(rowMinusOne).at(colMinusOne) <-1 && aboveFloorGrid.at(rowPlusOne).at(colMinusOne)){
       return true;
     }
   }
   if(rowMinusOneIn && rowMinusTwoIn && colMinusOneIn){
     if(aboveFloorGrid.at(rowMinusOne).at(colMinusOne) <-1 && aboveFloorGrid.at(rowMinusTwo).at(col)){
       return true;
     }
   }
   if(rowMinusOneIn && rowMinusTwoIn && colPlusOneIn){
     if(aboveFloorGrid.at(rowMinusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(rowMinusTwo).at(col)){
       return true;
     }
   }
   if(rowPlusOneIn && colMinusOneIn && rowPlusTwoIn){
     if(aboveFloorGrid.at(rowPlusOne).at(colMinusOne) <-1 && aboveFloorGrid.at(rowPlusTwo).at(col)){
       return true;
     }
   }
   if(rowPlusOneIn && colPlusOneIn && rowPlusTwoIn){
     if(aboveFloorGrid.at(rowPlusOne).at(colPlusOne) <-1 && aboveFloorGrid.at(rowPlusTwo).at(col)){
       return true;
     }
   }

   return false;
 }

 /*
  * set up a vector with integers to indicate whether each direction
  * can be blocked for future placements  (paths, obstacles)
  * @param blockedSides: vector with all the sides that are blocked
  *                     for future obstacle placement
  */
  void MapFactory::setBlockedSides(vector<int> &blockedSides){

    int isBlocked = (int) randomVariates -> Equilikely(0,4);

    for(auto it = blockedSides.begin(); it != blockedSides.end(); ++it){
      *it = isBlocked;
      isBlocked = (int) randomVariates -> Equilikely(0,4);
    }

    random_shuffle(blockedSides.begin(), blockedSides.end());
  }

/*
 * after an obstacle is placed mark any spaces next to it as well as its
 * position as off limits for future placement. return the updated
 * number of possible obstacle placements
 * @param row: row index (Y)
 * @param col: col index (X)
 * @param currentOpenSpaces: the number of spaces for obstacles
 * @param blockedSides: all sides that could be blocked (each holds a die roll for the % chance they will be blocked)
 * @return int: the number of spots open left
 */

int MapFactory::markUnavailableSpotsNearObstacle(int row, int col, int currentOpenSpaces, vector<int> &blockedSides){
  //mark the spot as unavaiable for the placement of future obstacles
  // or paths
  unavailableSpots.at(row).at(col) = 1;
  currentOpenSpaces--;

  int rowMinus = row - 1;
  int rowPlus = row + 1;
  int colMinus = col - 1;
  int colPlus = col + 1;

  //check all the directions
  //to see if they are in bounds and mark the spots as unavaiable
  //only checks marks them off if the passed value in
  //blockedSides vector is true (1)
  if(colMinus >= 0){
    //left
    if(blockedSides.at(0)){
      unavailableSpots.at(row).at(colMinus) = 1;
      currentOpenSpaces--;
    }

    //top left diagonal
    if(rowMinus >= 0){
      if(blockedSides.at(4) > 3){
        unavailableSpots.at(rowMinus).at(colMinus) = 1;
        currentOpenSpaces--;
      }
    }
    //bottom left diagonal
    if(rowPlus < yDim){
      if(blockedSides.at(5) > 3){
        unavailableSpots.at(rowPlus).at(colMinus) = 1;
        currentOpenSpaces--;
      }
    }
  }
  if(colPlus < xDim){
    //right
    if(blockedSides.at(1)){
      unavailableSpots.at(row).at(colPlus) = 1;
      currentOpenSpaces--;
    }

    //top right diagonal
    if(rowMinus >= 0){
      if(blockedSides.at(6) > 3){
        unavailableSpots.at(rowMinus).at(colPlus) = 1;
        currentOpenSpaces--;
      }
    }
    //bottom right diagonal
    if(rowPlus < yDim){
      if(blockedSides.at(7) > 3){
        unavailableSpots.at(rowPlus).at(colPlus) = 1;
        currentOpenSpaces--;
      }
    }
  }
  if(rowMinus >= 0){
    //top
    if(blockedSides.at(2)){
      unavailableSpots.at(rowMinus).at(col) = 1;
      currentOpenSpaces--;
    }
  }
  if(rowPlus < yDim){
    //bottom
    if(blockedSides.at(3)){
      unavailableSpots.at(rowPlus).at(col) = 1;
      currentOpenSpaces--;
    }
  }

  return currentOpenSpaces;

}


/*
 * place invisible obstacles on the board if there are spaces and the
 * minimum number have not been placed
 * @param placedInvisibleObstacles: the number of invisible obstacles placed so far
 * @param possiblePlacements: the possible open spaces left on the board
 */
void MapFactory::placeRemainingInvisibleObstacles(int placedInvisibleObstacles,
                                                int possiblePlacements){
  int randRowChosen = (int) randomVariates -> Equilikely(1, yDim-2);
  int randColChosen = (int) randomVariates -> Equilikely(1, xDim-2);
  //if there are still spots on the board to place obstacles and
  //we still have more invisible obstacles to place
  while(placedInvisibleObstacles < minimumInvisibleObstacles && possiblePlacements > 0){
    randRowChosen = (int) randomVariates -> Equilikely(1, yDim-2);
    randColChosen = (int) randomVariates -> Equilikely(1, xDim-2);
    aboveFloorGrid.at(randRowChosen).at(randColChosen) = -2;
    placedInvisibleObstacles++;
    possiblePlacements--;
  }
}

/*
 * Check if the row and column are in the grid
 * @param row: row index (Y)
 * @param col: col index (X)
 * @return bool: if row and col are in the map
 */
bool MapFactory::isInMap(int row, int col){
  return rowIsInMap(row) && colIsInMap(col);
}

/*
 * Row is on the map
 * @param row: row index (Y)
 * @return bool: if the row is on the map
 */
bool MapFactory::rowIsInMap(int row){
  return row >= 0 && row < yDim;
}

/*
 * Col is on the map
 * @param col: col index (X)
 * @return bool: if the col is on the map
 */
bool MapFactory::colIsInMap(int col){
  return col >= 0 && col < xDim;
}

template <class T>
void MapFactory::printVector(vector<vector<T>> &v){
  for(vector<int> vec : v){
    for(auto it = vec.begin(); it != vec.end(); ++it){
      if(*it < 0){
        cout << *it << " ";
      }
      else{
        cout << *it << "  ";
      }
    }
    cout << endl;
  }
  cout <<endl;
}

template <class T>
void MapFactory::printVector(vector<T> &v){
  for(T &vec : v){
    cout << vec << " ";
  }
  cout <<endl;
}

template <class T, class T2>
void MapFactory::printUnorderedMap(unordered_map<T,unordered_map<T,T2>> &uo){
  for(auto it: uo){
    cout << "Row " << (it).first << endl;
    for(auto dt: it.second){
      cout <<  dt.first << " ";
    }
    cout << endl;
  }
}

//------------------------------------------------------------------------------
vector<int>& MapFactory::getExitPos(){
  return exitPos;
}
vector<int>& MapFactory::getEntryPos(){
  return entryPos;
}
vector<vector<int>>& MapFactory::getDistances(){
  return distances;
}
vector<vector<int>>& MapFactory::getFloor(){
  return floorGrid;
}
vector<vector<int>>& MapFactory::getAboveFloor(){
  return aboveFloorGrid;
}
int MapFactory::getXDim(){
  return xDim;
}
int MapFactory::getYDim(){
  return yDim;
}

void MapFactory::setMapCustomizationChoices(MapChoices * newCustomization){
  this -> mapCustomizationChoices.reset(newCustomization);
}
void MapFactory::setMapObstacleChoice(int obstacleChoice){
  mapCustomizationChoices -> obstacleChoice = obstacleChoice;
}
void MapFactory::setMapCafeteriaChoice(int cafeteriaChoice){
  mapCustomizationChoices -> cafeteriaChoice = cafeteriaChoice;
}
void MapFactory::setMapEntryChoice(int pathEntryChoice){
  mapCustomizationChoices -> pathEntryChoice = pathEntryChoice;
}
