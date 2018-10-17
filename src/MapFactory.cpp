 #include "MapFactory.hpp"


MapFactory::MapFactory(MapChoices *mapCustomizationChoices){
  this -> mapCustomizationChoices = unique_ptr<MapChoices>(mapCustomizationChoices);

  //generate the dimensions of the board using the cafeteria size choice
  generateDimensions();



  //set seed for random number generator from file rngs
  time_t t;
  PutSeed(time(&t));
}

//a higher cafeteria choice means a larger cafeteria
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

//fill all four grids with valid values for a map
void MapFactory::generateMap(){
  for(int i = 0; i < 10; i++){
  //initializes all vector indicies to -1
  this -> initGridArrays();

  //initialize the floor pattern
  this -> makeFloor();
  
  //place an exit on all boards
  this -> makeExit();

  //initialize the distances pattern
  this -> makeDistances();

  //place an entry on all boards
  for(int e = 0; e < mapCustomizationChoices -> pathEntryChoice; e++){
    // add one because the path number should always start at 1 since 0
    // is the exit
    this -> makeEntry(e + 1);
  }

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
  //place obstacles on the board
  this -> makeObstacles();

  //TODO remove when done checking grids
  this -> printVector(this -> paths);
  //this -> printVector(this -> unavailableSpots);
  //this -> printVector(this -> distances);
  this -> printVector(this -> floorGrid);
  //this -> printVector(this -> aboveFloorGrid);
  //this -> printVector(this -> adjacientPathSpots);
  //this -> printUnorderedMap(this -> pathAdjacient);

  paths.clear();
  unavailableSpots.clear();
  distances.clear();
  floorGrid.clear();
  aboveFloorGrid.clear();
  exitPos.clear();
  entryPos.clear();
  entryDirections.clear();
  pathAdjacient.clear();
  adjacientPathSpots.clear();
}
}

//set all values in each map grid to -1
void MapFactory::initGridArrays(){

  //set each row to -1
  for(int i = 0; i < this -> yDim; i++) {
      this -> paths.push_back(vector<int>(this -> xDim, -1));
      this -> unavailableSpots.push_back(vector<int>(this -> xDim, -1));
      this -> distances.push_back(vector<int>(this -> xDim, -1));
      this -> floorGrid.push_back(vector<int>(this -> xDim, -1));
      this -> aboveFloorGrid.push_back(vector<int>(this -> xDim, -1));
      this -> adjacientPathSpots.push_back(vector<int>(this -> xDim, -1));
      this -> markPathSoFar.push_back(vector<int>(this -> xDim, -1));
  }
}

//set the exit on each map grid
void MapFactory::makeExit(){
  //choose one of the four sides of the grid
  int chosenSide = (int)this->Equilikely(0,3);

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

/* choose index of the exit that is determined by what side of the grid it will
 * sit on
 */
int MapFactory::chooseIndexOfExit(int side){
  //if this is the left or right side
  if(side < 2){
    return (int) this -> Equilikely(0, this -> floorGrid.size() - 1);
  }
  //if this is the Top or Bottom side
  else{
    return (int) this -> Equilikely(0, this -> floorGrid[0].size() - 1);
  }
}

/* set an exit marker (0) on each 2d array to show where the exit is
 * will switch the order of exitSide and exitIndexOnSide in [row][col]
 * notation to recognize that which side is chosen will determine
 * whether the index is the row or the column. i.e. if the left side (0)
 * is chosen then the index will be the row since the column will be the first
 * one.
 */
void MapFactory::placeExit(int exitSide, int exitIndexOnSide){

  //set the stored exit position to be the row and column specified by the params
  // passed
  switch(exitSide){
      case 0:
        this -> exitPos.push_back(0);
        this -> exitPos.push_back(exitIndexOnSide);
        break;
      case 1:
        this -> exitPos.push_back(this -> floorGrid[0].size() - 1);
        this -> exitPos.push_back(exitIndexOnSide);
        break;
      case 2:
        this -> exitPos.push_back(exitIndexOnSide);
        this -> exitPos.push_back(0);
        break;
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

  this -> setUnavailableSpotsFromExit(exitPos[0], exitPos[1]);
}

//mark indicies as unavaiable for an entry given the exit position
void MapFactory::setUnavailableSpotsFromExit(int exitXPos, int exitYPos){
  switch(exitDirection.facing){
    case Direction::Left:
      this -> setUnavailableSpotsFromLeftExit(exitXPos, exitYPos);
      break;
    case Direction::Right:
      this -> setUnavailableSpotsFromRightExit(exitXPos, exitYPos);
      break;
    case Direction::Top:
      this -> setUnavailableSpotsFromTopExit(exitXPos, exitYPos);
      break;
    case Direction::Bottom:
    default:
      this -> setUnavailableSpotsFromBottomExit(exitXPos, exitYPos);
      break;
  }
}

//mark indicies as unavaiable for an entry given the left exit position
//first set the row/col the exit is on to all unavailable
//then set 1/3 of the row/col adjacient to the exit row/col as unavailable
// which should ensure no paths start too close to the exit to be manageable
void MapFactory::setUnavailableSpotsFromLeftExit(int exitXPos, int exitYPos){
  //set all the spots in the left column to 0
  for(int i = 0; i < yDim; i++){
    //if we are in the first row or the last row
    //then set a third of the columns extending out to 0
    if(i == 0 || i == yDim - 1){
      for(int j = 0; j < 3*(xDim/4); j++){
        unavailableSpots[i][j] = 0;
      }
    }
    unavailableSpots[i][0] = 0;
  }

}
//mark indicies as unavaiable for an entry given the right exit position
//first set the row/col the exit is on to all unavailable
//then set 1/3 of the row/col adjacient to the exit row/col as unavailable
// which should ensure no paths start too close to the exit to be manageable
void MapFactory::setUnavailableSpotsFromRightExit(int exitXPos, int exitYPos){
  for(int i = 0; i < yDim; i++){
    //if we are in the first row or the last row
    //then set a third of the columns extending out to 0
    if(i == 0 || i == yDim - 1){
      for(int j = xDim - 1; j >= (xDim / 4); j--){
        unavailableSpots[i][j] = 0;
      }
    }
    unavailableSpots[i][xDim - 1] = 0;
  }
}
//mark indicies as unavaiable for an entry given the top exit position
//first set the row/col the exit is on to all unavailable
//then set 1/3 of the row/col adjacient to the exit row/col as unavailable
// which should ensure no paths start too close to the exit to be manageable
void MapFactory::setUnavailableSpotsFromTopExit(int exitXPos, int exitYPos){
  for(int i = 0; i < xDim; i++){
    //if we are in the first col or the last col
    //then set a third of the row starting indicies extending out to 0
    if(i == 0 || i == xDim - 1){
      for(int j = 0; j < 3*(yDim/4); j++){
        unavailableSpots[j][i] = 0;
      }
    }
    unavailableSpots[0][i] = 0;
  }
}
//mark indicies as unavaiable for an entry given the bottom exit position
//first set the row/col the exit is on to all unavailable
//then set 1/3 of the row/col adjacient to the exit row/col as unavailable
// which should ensure no paths start too close to the exit to be manageable
void MapFactory::setUnavailableSpotsFromBottomExit(int exitXPos, int exitYPos){
  for(int i = 0; i < xDim; i++){
    //if we are in the first col or the last col
    //then set a third of the row starting indicies extending out to 0
    if(i == 0 || i == xDim - 1){
      for(int j = yDim - 1; j >= (yDim / 4); j--){
        unavailableSpots[j][i] = 0;
      }
    }
    unavailableSpots[yDim - 1][i] = 0;
  }
}

//set each entry on all the map grids
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
        chosenSideIndex = (int)this->Equilikely(0,2);

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
   int index = (int) Equilikely(0, entriesOnSide.size() - 1);
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
       currSideEntries.push_back(row);
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
       currSideEntries.push_back(col);
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

//return true is at least one of the three sides the exit is not on
// can have an entry placed on it
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

//return true if the side specified has room for an entry on it
//also fill possibleEntries with the indicies of poetential places
// for an entry
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

//check the left side for having a space for an entry and fill the vector
//with possible entry indicies if there are spaces
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

//check the right side for having a space for an entry and fill the vector
//with possible entry indicies if there are spaces
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

//check the top side for having a space for an entry and fill the vector
//with possible entry indicies if there are spaces
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

//check the bottom side for having a space for an entry and fill the vector
//with possible entry indicies if there are spaces
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


/* set an entry marker (pathNumberOfEntry) on each 2d array to show where the entry is
 * will switch the order of entrySide and entryIndexOnSide in [row][col]
 * notation to recognize that which side is chosen will determine
 * whether the index is the row or the column. i.e. if the left side (0)
 * is chosen then the index will be the row since the column will be the first
 * one.
 */
void MapFactory::placeEntry(Direction::Directions &entrySide, int entryIndexOnSide, int pathNumberOfEntry){

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

  //record all tiles next to this one
  addAdjacientsTiles(entryPos[entryPos.size() - 1],entryPos[entryPos.size() - 2]);

  //mark the spots around this entrance as unavailabe for future entry positions
  this -> setUnavailableSpotsFromEntry(entryPos[entryPos.size() - 2], entryPos[entryPos.size() - 1]);
}

//mark indicies as unavaiable for an entry given the entry position
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

//mark indicies as unavaiable for an entry given the entry position is on the left side
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

//mark indicies as unavaiable for an entry given the entry position is on the right side
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

//mark indicies as unavaiable for an entry given the entry position is on the Top side
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

//mark indicies as unavaiable for an entry given the entry position is on the Bottom side
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

//make the floor with an alternating pattern of negative numbers to
//set everything as a non-path tile (except the exit which is marked already)
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
 * find a recursive path and then execute it
 * TODO Optimize if have time
 */
void MapFactory::makePathRecursively(int pathNumber){
  vector<Direction::Directions> moveToMake;

  //grab the starting row and column
  int currRowNum = entryPos.at(2*(pathNumber - 1) + 1);
  int currColNum = entryPos.at(2*(pathNumber - 1));

  //remove the current tile from the adjacientTiles if it exists there
  removeAdjacientTiles(currRowNum, currColNum);

  //the direction the entry faces in
  Direction::Directions entryDirection = entryDirections[pathNumber - 1].facing;
  //the direction we cannot expand towards
  Direction::Directions directionExpandedFrom = entryDirection;

  //the starting distance
  int distance = distances.at(currRowNum).at(currColNum);

  vector<vector<int>> keepTrack = markPathSoFar;


  bool possible = recursiveMakePath(pathNumber, currRowNum, currColNum, moveToMake, directionExpandedFrom, 0 , keepTrack, distance);

  for(Direction::Directions move : moveToMake){

    //update the row to the exapnded direction
    currRowNum = expandInRow(currRowNum, move);
    //update the column to the exapnded direction
    currColNum = expandInCol(currColNum, move);

    //place a path value at the current tile
    paths.at(currRowNum).at(currColNum) = pathNumber;

    //mark this spot as unavailable for use later
    unavailableSpots.at(currRowNum).at(currRowNum) = 0;

    //record all tiles next to this one
    addAdjacientsTiles(currRowNum, currColNum);

    //remove the current tile from the adjacientTiles if it exists there
    removeAdjacientTiles(currRowNum, currColNum);
  }

}

/*
 * recursively find a path and return a random one
 */

 bool MapFactory::recursiveMakePath(int pathNumber, int row, int col, vector<Direction::Directions> &pathDirects, Direction::Directions cameFrom, int recurLevel, vector<vector<int>> &keepTrack, int lastDistance){


   vector<Direction::Directions> goInto = exitDirection.allOtherDirections(cameFrom);

   if(connectedWithExit(row, col) || connectedWithExitPath(row, col, pathNumber) || recurLevel > 30){
     return true;
   }

   int distance = distances.at(row).at(col);
   if(lastDistance < distance - 1){
     return false;
   }



   if(keepTrack.at(row).at(col) >= 0){
     return false;
   }
   //let us know we have been here before on this path
   keepTrack.at(row).at(col) = recurLevel;
   vector<Direction::Directions> canMove;
   for(Direction::Directions d : goInto){
     if(canExpand(d,row, col, pathNumber)){
       canMove.push_back(d);
     }
   }

   vector<vector<Direction::Directions>> allPaths;
   vector<bool> pathPossible;
   for(int i= 0; i < canMove.size(); i++){
     int newcol = col;
     int newrow = row;
     Direction::Directions curr = canMove.at(i);
     switch(curr){
       case Direction::Left:
         newcol--;
         break;
       case Direction::Right:
         newcol++;
         break;
       case Direction::Top:
         newrow--;
         break;
       case Direction::Bottom:
       default:
         newrow++;
         break;
     }

      if(connectedWithSamePath( row, col,newrow, newcol, pathNumber, keepTrack)){
          continue;
      }

     vector<vector<int>> keepTrackPlus = keepTrack;
     vector<Direction::Directions> path = pathDirects;

     pathPossible.push_back(recursiveMakePath(pathNumber, newrow, newcol, path, exitDirection.oppositeDirection(curr), recurLevel+1, keepTrackPlus, distance));


     if(pathPossible.at(pathPossible.size() - 1)){
      allPaths.push_back(path);
     }
   }

   if(allPaths.size() == 0){
     return false;
   }

   int pickPath = (int) Equilikely(0, allPaths.size() -1 );

   random_shuffle(allPaths.begin(), allPaths.end());
   for(Direction::Directions d : allPaths.at(pickPath)){
     pathDirects.push_back(d);
   }

   if(canMove.size() == 0){
     return false;
   }
   vector<int> nonExitPaths =  connectedWithNonExitPath(row, col, pathNumber);
   if(nonExitPaths.size() != 0){
     for(int nonExitPath : nonExitPaths){
       entrysToExit.at(nonExitPath - 1) = 1;
     }
   }
 }

//make a path for the specified path on the board
void MapFactory::makePath(int pathNumber){
  //grab the starting row and column
  int currRowNum = entryPos.at(2*(pathNumber - 1) + 1);
  int currColNum = entryPos.at(2*(pathNumber - 1));

  //a variable that tells whether this is the first step or not
  bool firstStep = true;

  //remove the current tile from the adjacientTiles if it exists there
  removeAdjacientTiles(currRowNum, currColNum);

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

      //flip a coin and 1/3 the time we will not take the shortest path
      int shortestOrNot = Equilikely(0,5);

      //current space distance from the exit
      int currDistance = distances.at(currRowNum).at(currColNum);

      //only take a non shortest path when the coin flip is correct
      //and we are far from the exit
      if(shortestOrNot < 4 || currDistance < 4 || firstStep == true || abs(currRowNum - exitPos.at(1)) < 2 || abs(currColNum - exitPos.at(0)) < 2){
        nextSteps = calcNextShortestStep(currRowNum, currColNum, lastShortestDistance);
      }
      else{
        nextSteps = calcNextShortestOrEqualStep(currRowNum, currColNum, pathNumber, lastShortestDistance);

        stripOfDeadEnds(nextSteps, currRowNum, currColNum, lastShortestDistance);

        if(nextSteps.size() == 0){
          nextSteps =  calcNextShortestStep(currRowNum, currColNum, lastShortestDistance);
        }
      }


      random_shuffle(nextSteps.begin(), nextSteps.end());

      int randomStep = Equilikely(0, nextSteps.size() - 1);

      //pick a random direction to step in from the possible options
      Direction::Directions expandInto = nextSteps.at(randomStep);

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

      //record all tiles next to this one
      addAdjacientsTiles(currRowNum, currColNum);

      //remove the current tile from the adjacientTiles if it exists there
      removeAdjacientTiles(currRowNum, currColNum);

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
 * Add every adjacient tile to the passed one that is not on a path or the exit
 * and is not already in the unordered_map of adjacient tiles
 */
void MapFactory::addAdjacientsTiles(int row, int col){

  vector<vector<int>> adjacientPositions;
  if(col - 1 >= 0){
    if(paths.at(row).at(col - 1) < 0){

      vector<int> v{row,col - 1};
      adjacientPositions.push_back(v);
    }
  }
  if(col + 1 < xDim){
    if(paths.at(row).at(col + 1) < 0){

      vector<int> v{row,col + 1};
      adjacientPositions.push_back(v);
    }
  }
  if(row - 1 >= 0){
    if(paths.at(row - 1).at(col) < 0){

      vector<int> v{row - 1,col};
      adjacientPositions.push_back(v);
    }
  }
  if(row + 1 < yDim){
    if(paths.at(row + 1).at(col) < 0){

      vector<int> v{row + 1,col};
      adjacientPositions.push_back(v);
    }
  }

  //iterate through the positions we identiifed and add them
  //to the hashtable of all the possible positions for obstacles
  //if they are not already in it
  for(vector<int> pos : adjacientPositions){
    //look for row
    unordered_map<int, unordered_map<int,bool>>::const_iterator rowLookup = pathAdjacient.find(pos.at(0));
    //if the current row is not recorded
    if(rowLookup == pathAdjacient.end()){
      //then add a new entry in the unordered_map for the row
      //and the column because that will not be in the map either
      unordered_map<int,bool> toInsert;
      toInsert.insert({pos.at(1), true});
      pathAdjacient.insert({pos.at(0), toInsert});

      adjacientPathSpots.at(pos.at(0)).at(pos.at(1)) = 0;
    }
    //if the current row is recorded we check to see if this column is recorded
    else{
        //look for column
        unordered_map<int,bool>::const_iterator colLookup = pathAdjacient.at(pos.at(0)).find(pos.at(1));
        //if the current column is not recorded
        if(colLookup == pathAdjacient.at(pos.at(0)).end()){
          //then add a new entry in the unordered_map assocaited with the row
          //for this new column entry
          pathAdjacient.at(pos.at(0)).insert({pos.at(1), true});
          adjacientPathSpots.at(pos.at(0)).at(pos.at(1)) = 0;
        }
    }
  }
}

/*
 * Remove the current tile from the list of adjacient tiles if it is in there
 */
 void MapFactory::removeAdjacientTiles(int row, int col){
   //look for row
   unordered_map<int, unordered_map<int,bool>>::const_iterator rowLookup = pathAdjacient.find(row);
   //if the current row is recorded
   if(rowLookup != pathAdjacient.end()){
     //then search for the column
     //look for column
    unordered_map<int,bool>::const_iterator colLookup = pathAdjacient.at(row).find(col);
    if(colLookup != pathAdjacient.at(row).end()){
      //if we have found the tile we remove it
      pathAdjacient.at(row).erase(col);
      adjacientPathSpots.at(row).at(col) = -2;
    }
   }
 }

 /*
  * return true if the direction specified can be exapnded into by this path
  * false when the spot specified is off the board or touching a current space
  * in this same path (do not want overlap on same path)
  */
bool MapFactory::canExpand(Direction::Directions &expand, int row, int col, int path){
  int newrow = row;
  int newcol = col;
  switch(expand){
    case Direction::Left:
      newcol--;
      break;
    case Direction::Right:
      newcol++;
      break;
    case Direction::Top:
      newrow--;
      break;
    case Direction::Bottom:
    default:
      newrow++;
      break;
  }


  if(newrow < 0 || newrow >= yDim){
    return false;
  }
  else if(newcol < 0 || newcol >= xDim){
    return false;
  }
  else if(connectedWithSamePath(row, col, newrow, newcol, path)){

    return false;
  }
  return true;
}

/*
 * return true if the passed tile is connected to the exit
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
 * checks to see if there is a path connected to this tile that is
 * on the same path as the path specified
 */
 bool MapFactory::connectedWithSamePath(int row, int col, int newrow, int newcol, int path){

   //check left
   if(newcol - 1 >= 0 && !(col == newcol - 1 && newrow == row)){
     if(paths.at(newrow).at(newcol - 1) == path){
       return true;
     }
   }
   if(newcol + 1 < xDim && !(col == newcol + 1 && newrow == row)){
     //check right
     if(paths.at(newrow).at(newcol + 1) == path){
       return true;
     }
   }
   if(newrow - 1 >= 0 && !(col == newcol && newrow - 1 == row)){
     //check top
     if(paths.at(newrow - 1).at(newcol) == path){
       return true;
     }
   }
   if(newrow + 1 < yDim && !(col == newcol && newrow + 1 == row)){
     //check bottom
     if(paths.at(newrow + 1).at(newcol) == path){
       return true;
     }
   }

   return false;
 }

 /*
  * checks to see if there is a path connected to this tile that is
  * on the same path that is marked in the passed vector of the marked path
  * every marked path section should be >=0
  */
  bool MapFactory::connectedWithSamePath(int row, int col, int newrow, int newcol, int path, vector<vector<int>> &markedPath){

    //check left
    if(newcol - 1 >= 0 && !(col == newcol - 1 && newrow == row)){
      if(markedPath.at(newrow).at(newcol - 1) >=0){
        return true;
      }
    }
    if(newcol + 1 < xDim && !(col == newcol + 1 && newrow == row)){
      //check right
      if(markedPath.at(newrow).at(newcol + 1) >=0){
        return true;
      }
    }
    if(newrow - 1 >= 0 && !(col == newcol && newrow - 1 == row)){
      //check top
      if(markedPath.at(newrow - 1).at(newcol) >=0){
        return true;
      }
    }
    if(newrow + 1 < yDim && !(col == newcol && newrow + 1 == row)){
      //check bottom
      if(markedPath.at(newrow + 1).at(newcol) >=0){
        return true;
      }
    }

    return false;
  }


/*
 * checks to see if there is a path connected to this tile that is not
 * on the same path as the path specified and that path is an exit path
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
  */
  vector<Direction::Directions> MapFactory::calcNextShortestStep(int row, int col, int lastShortestDistance){
    int topDist = 0x1FFF;
    int bottomDist = 0x1FFF;
    int leftDist = 0x1FFF;
    int rightDist = 0x1FFF;

    vector<Direction::Directions> shortestSteps;

    /*
     * We do not look in directions that are on one of the edges to avoid
     * paths that run along the edge and miss the first step
     * each path takes
     */
    //check left
    if(col - 1 > 0){
      leftDist = distances.at(row).at(col - 1);
    }
    //check right
    if(col + 1 < xDim - 1){
      rightDist = distances.at(row).at(col + 1);
    }
    //check top
    if(row - 1 > 0){
      topDist = distances.at(row - 1).at(col);
    }
    //check bottom
    if(row + 1 < yDim - 1){
      bottomDist = distances.at(row + 1).at(col);
    }

    int shortestDist = min(leftDist, min(rightDist, min(topDist, bottomDist)));
    //if the last shortest distance was longer than the current one we just
    //take a normal path
    if(shortestDist > lastShortestDistance){
      //check left
      if(col - 1 >= 0){
        leftDist = distances.at(row).at(col - 1);
      }
      //check right
      if(col + 1 < xDim){
        rightDist = distances.at(row).at(col + 1);
      }
      //check top
      if(row - 1 >= 0){
        topDist = distances.at(row - 1).at(col);
      }
      //check bottom
      if(row + 1 < yDim){
        bottomDist = distances.at(row + 1).at(col);
      }

      shortestDist = min(leftDist, min(rightDist, min(topDist, bottomDist)));
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
 * return a vector with the directions of every possible step (i.e.) not onto a
 * step that exists
 */
vector<Direction::Directions> MapFactory::calcNextShortestOrEqualStep(int row, int col, int path, int lastShortestDistance){

    vector<Direction::Directions> otherSteps;


    //add a step for every direction that is not on a path already
    //check left
    if(col - 1 >= 0){
      //if the tile is not on a path
      if(paths.at(row).at(col-1) < 0){
        //if the tile is not touching a tile of the same path other than this one
        if(!connectedWithSamePath(row, col, row, col - 1, path)){
          //cannot be further away from the exit
          int distance = distances.at(row).at(col - 1);
          if(distance <= lastShortestDistance ){
              otherSteps.push_back(Direction::Left);
          }
        }
      }
    }
    //check right
    if(col + 1 < xDim){
      if(paths.at(row).at(col+1) < 0){
        //if the tile is not touching a tile of the same path other than this one
        if(!connectedWithSamePath(row, col, row, col + 1, path)){
            //cannot be further away from the exit
            int distance = distances.at(row).at(col + 1);
            if(distance <= lastShortestDistance ){
                otherSteps.push_back(Direction::Right);
            }
          }
        }
      }
    //check top
    if(row - 1 >= 0){
      if(paths.at(row - 1).at(col) < 0){
        //if the tile is not touching a tile of the same path other than this one
        if(!connectedWithSamePath(row, col, row - 1, col, path)){
            //cannot be further away from the exit
            int distance = distances.at(row - 1).at(col);
            if(distance <= lastShortestDistance ){
                otherSteps.push_back(Direction::Top);
            }
          }
        }
      }
    //check bottom
    if(row + 1 < yDim){
      if(paths.at(row + 1).at(col) < 0){
        //if the tile is not touching a tile of the same path other than this one
        if(!connectedWithSamePath(row, col, row + 1, col, path)){
            //cannot be further away from the exit
            int distance = distances.at(row + 1).at(col);
            if(distance <= lastShortestDistance ){
                otherSteps.push_back(Direction::Bottom);
            }
          }
        }
      }

    return otherSteps;
  }

/*
 * remove any step that leads to a dead end (i.e. a positon with no moves)
 */
  void MapFactory::stripOfDeadEnds(vector<Direction::Directions> &expandOptions, int row, int col, int lastShortestDistance){

    vector<Direction::Directions> possibleDirections;
    for(Direction::Directions d : expandOptions){
      if(possibleMoves(d, row, col, lastShortestDistance)){
        possibleDirections.push_back(d);
      }
    }
    expandOptions = possibleDirections;
  }

  /*
   * check if the passed tile could move in a direction other than the one it stepped from
   */
  bool MapFactory::possibleMoves(Direction::Directions &expand,  int row, int col, int lastShortestDistance){
    int oldrow = row;
    int oldcol = col;
    switch(expand){
      case Direction::Left:
        col--;
        break;
      case Direction::Right:
        col++;
        break;
      case Direction::Top:
        row--;
        break;
      case Direction::Bottom:
      default:
        row++;
        break;
    }

    //add a step for every direction that is not on a path already
    //check left
    if(col - 1 >= 0){
      //if the tile is not on a path
      if(paths.at(row).at(col-1) < 0){
        //if this is not the path we moved from
        if(!(oldcol == col - 1 && oldrow == row)){
          //cannot be further away from the exit
          int distance = distances.at(row).at(col - 1);
          if(distance <= lastShortestDistance + 1){
              return true;
          }
        }
      }
    }
    //check right
    if(col + 1 < xDim){
      if(paths.at(row).at(col+1) < 0){
        //if this is not the path we moved from
        if(!(oldcol == col + 1 && oldrow == row)){
        //if the tile is not touching a tile of the same path other than this one
            //cannot be further away from the exit
            int distance = distances.at(row).at(col + 1);
            if(distance <= lastShortestDistance + 1){
                return true;
            }
          }
        }
    }
    //check top
    if(row - 1 >= 0){
      if(paths.at(row - 1).at(col) < 0){
        //if this is not the path we moved from
        if(!(oldcol == col && oldrow == row - 1)){
        //if the tile is not touching a tile of the same path other than this one
            //cannot be further away from the exit
            int distance = distances.at(row - 1).at(col);
            if(distance <= lastShortestDistance + 1){
                return true;
            }
          }
        }
      }
    //check bottom
    if(row + 1 < yDim){
      if(paths.at(row + 1).at(col) < 0){
        //if this is not the path we moved from
        if(!(oldcol == col && oldrow == row + 1)){
        //if the tile is not touching a tile of the same path other than this one
            //cannot be further away from the exit
            int distance = distances.at(row + 1).at(col);
            if(distance <= lastShortestDistance + 1){
                return true;
            }
          }
        }
      }
    return false;
  }

 /*
  * return a new row number that is expanded in the specified direction
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
  int numPathAdjacient = countPathAdjacient();

  //while we have not placed the maximum specified number of obstacles
  //and there are still adjacient path spots to place them
  while(placedObstacles < mapCustomizationChoices -> obstacleChoice &&
        placedObstacles < numPathAdjacient){

    //select a random row value
    int randRowChosen = (int) Equilikely(0, yDim - 1);
    //find that row in the hash table of path adjacient tiles
    unordered_map<int, unordered_map<int,bool>>::const_iterator randRowIterator = pathAdjacient.find(randRowChosen);

    while(randRowIterator == pathAdjacient.end()){
      randRowChosen = (int) Equilikely(0, yDim - 1);
      randRowIterator = pathAdjacient.find(randRowChosen);
    }

    //if we picked an empty row just go around while loop again after it is removed
    if(pathAdjacient.at(randRowChosen).size() == 0){
      pathAdjacient.erase(randRowChosen);
      continue;
    }

    //select a random column value
    int randColChosen = (int) Equilikely(0, xDim - 1);
    //find that column in the hash table for the row
    unordered_map<int,bool>::const_iterator randColIterator = pathAdjacient.at(randRowChosen).find(randColChosen);

    while(randColIterator == pathAdjacient.at(randRowChosen).end()){
      randColChosen = (int) Equilikely(0, xDim - 1);
      randColIterator = pathAdjacient.at(randRowChosen).find(randColChosen);
    }

    //place an obstacle at the chosen row and column
    aboveFloorGrid.at(randRowChosen).at(randColChosen) = -2;

    //remove the obstacle from the map
    pathAdjacient.at(randRowChosen).erase(randColChosen);

    placedObstacles++;

  }
}

/*
 * count and return the number of path adjacinet tiles
 */
int MapFactory::countPathAdjacient(){
  int counter = 0;
  for(auto uo: pathAdjacient){
    for(auto dt: uo.second){
      counter++;
    }
  }
  return counter;
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


double  MapFactory::Equilikely (double a, double b){
  /* ---------------------------------------------------
   * generate an Equilikely random variate, use a < b
   * ---------------------------------------------------
   */
	return (a+ (long) ((b-a+ 1) * Random()));
}


double MapFactory::Geometric(double p)
/* ---------------------------------------------------
 * generate an Geometric random variate, use 0.0 < p < 1.0
 * ---------------------------------------------------
*/
{
return ((log(1.0 - Random()) / log(p)));
}

double MapFactory::Exponential(double m)
/* ---------------------------------------------------
* generate an Exponential random variate, use m > 0.0
* ---------------------------------------------------
*/
{
return (-m * log(1.0 - Random()));
}


double MapFactory::Uniform(double a, double b)
/* --------------------------------------------
* generate a Uniform random variate, use a < b
* --------------------------------------------
*/
{
return (a + (b - a) * Random());
}
