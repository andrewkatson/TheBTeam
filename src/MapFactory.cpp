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
MapFactory::MapFactory(MapChoices *mapCustomizationChoices, shared_ptr<TextLoader> textLoader) : mt(std::random_device()()) {
  this -> mapCustomizationChoices = unique_ptr<MapChoices>(mapCustomizationChoices);
  this -> textLoader = textLoader;
  this -> maxObstacleVal = 4;

  //generate the dimensions of the board using the cafeteria size choice
  generateDimensions();



  //set seed for random number generator from file rngs
  time_t t;
  PutSeed(time(&t));
}


/*
 * set the dimensions for the map (a higher cafeteria choice is larger)
 * the minimum size is 6x6
 */
void MapFactory::generateDimensions(){
  //cout << "MAKE VERIFIER FOR ALL ENTRIES TO EXIT OTHERWISE REMAKE" << endl;
  //cout << "IF ALL ENTRIES TO EXIT MARK AS YOU GO AND THEN REMOVE UNMARKED PATH ELEMENTS" << endl;
  //cout << "FIX WEIRD OUT OF RANGE EXCEPTION" << endl;
  //cout << "ALSO DEVELOP A METRIC FOR % BOARD COVERED (I.E. OBSTACLES OR PATH) " << endl;

  int modifier = textLoader -> getInteger(string("IDS_Cafeteria_Size_Modifier"));

  //the cafeteria choice serves as the primer for our dimensions
  int primerNum = (int) mapCustomizationChoices -> cafeteriaChoice * modifier;

  //the distribution we generate numbers for
  std::uniform_int_distribution<int> dist((-1)*primerNum, primerNum);

  //the minimum dimensions of the board
  int minimumDimensions = textLoader->getInteger(string("IDS_Minimum_Board_Dimensions"));

  int xDim = (int) (abs(dist(mt))) + minimumDimensions;
  int yDim = (int) (abs(dist(mt)))  + minimumDimensions;

  //the maximum allowed difference between an x and a y dimension
  int maxDisparity = textLoader->getInteger(string("IDS_Max_X_Y_Disparity"));

  //we decrement the larger dimension until the disparity is fixed
  while(abs(xDim - yDim >= maxDisparity)){
    if(xDim > yDim){
      xDim--;
    }
    else{
      yDim--;
    }
  }

  //checks to ensure that the dimensions are never negative or 0
  if(xDim <= minimumDimensions){
    xDim = minimumDimensions;
  }
  if(yDim <= minimumDimensions){
    yDim = minimumDimensions;
  }

  //the divisor that determines the number of invisible obstacles
  int minimumInvisibleObstacleModifier = textLoader -> getInteger(string("IDS_Invisible_Obstacle_Modifier"));

  minimumInvisibleObstacles =  (xDim*yDim)/minimumInvisibleObstacleModifier;

  this -> xDim = xDim;
  this -> yDim = yDim;
}

/*
 * make a map and fill the 2d vectors describing the map
 * with the appropriate values
 */
void MapFactory::generateMap(){
  cout << "here " << endl;
  int fails = 0;
  int notAnExit = 0;
  for(int i = 0; i < 1; i++){
    s.str("");
    cout << "made map " << i << endl;
    //try to make a map
    bool makeMap = false;

    while(!makeMap){
      resetEverything();
      makeMap = tryAMap();
      if(!makeMap){
        fails++;
      }
      //if not every path led to the exit this is a failure
      if(!allPathsToExit()){
        makeMap = false;
        fails++;
        notAnExit++;
      }
    }

    //TODO remove when done checking grids
    //this -> printVector(this -> paths);
    //this -> printVector(this -> unavailableSpots);
    //this -> printVector(this -> distances);
    //this -> printVector(this -> floorGrid);
    //this -> printVector(this -> aboveFloorGrid);

    //some paths may be covered by the nature of the program so just set
    //them on the board to help with interpretation
    putEmptyEntriesOnBoard();
    int tilesCleaned = cleanupMap();
    if(tilesCleaned){
        cout << "Tiles Cleaned " << tilesCleaned << endl;
    }
  }
  cout << "Failures " << fails << endl;
  cout << "Not An Exit " << notAnExit << endl;
}

/*
 * Try to generate a map
 * @param bool: false if we cannot
 */
bool MapFactory::tryAMap(){
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

    //only do the path logic if we have not reached the exit
    if(entrysToExit.at(p) != 1){
      // add one because the path number should always start at 1 since 0
      // is the exit
      bool pathMade = this -> makePathBFS(p+1);

      //if we fail to make a legitimate map
      if(!pathMade){
        return false;
      }
    }

    if(p < entrysToExit.size()){
      //add this path to the list of paths to the exit
      entrysToExit.at(p) = 1;
    }
  }

  return true;
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
      this -> extraneousPaths.push_back(vector<int>(this -> xDim, -1));
  }
}
/*
 * Clears all the data on the map (used for restart and debugging)
 */
void MapFactory::resetEverything(){
  paths.clear();
  unavailableSpots.clear();
  distances.clear();
  floorGrid.clear();
  aboveFloorGrid.clear();
  extraneousPaths.clear();
  exitPos.clear();
  entryPos.clear();
  entryDirections.clear();
}

/*
 * Walk from every entry to the end of the board
 * and mark the path tile you took
 * @return if you cannot go anywhere you have not already gone
 */
bool MapFactory::allPathsToExit(){

  s.str("");
  s << "checking paths " << endl;

  int exitRow = exitPos.at(1);
  int exitCol = exitPos.at(0);

  //the directions we can go in
  vector<intPair> dirs = {make_pair(0,1), make_pair(0,-1),make_pair(1,0),make_pair(-1,0)};

  //places we cannot visit again
  vector<vector<int>> closedList (yDim, vector<int>(xDim, -1));

  //open list
  set<intPair> openList;

  //push the exit space
  openList.insert(make_pair(exitRow, exitCol));

  while(!openList.empty()){

    intPair check = *openList.begin();
    openList.erase(openList.begin());

    closedList.at(check.first).at(check.second) = 1;
    extraneousPaths.at(check.first).at(check.second) = 1;

    for(intPair dir : dirs){
      int newRow = check.first + dir.first;
      int newCol = check.second + dir.second;

      if(!isInMap(newRow, newCol)){
        continue;
      }
      intPair newPair = make_pair(newRow, newCol);

      if(openList.find(newPair) != openList.end() || closedList.at(newRow).at(newCol) != -1 || paths.at(newRow).at(newCol) < 0){
        continue;
      }
      else{
        openList.insert(newPair);
      }
    }
  }

  int pathNum = 0;
  for(int entryPair = 0; entryPair < entryPos.size(); entryPair +=2){
    int row = entryPos.at(entryPair+1);
    int col = entryPos.at(entryPair);

    bool check = checkPathToExit(row, col);
    if(!check){
      return false;
    }
    pathNum++;
  }
  return true;
}

/*
 * check the row and col (should be an entry) if it has been visited
 * @return true if this entry can be reached from the exit
 */
bool MapFactory::checkPathToExit(int row, int col){
  if(extraneousPaths.at(row).at(col) != 1){
    printVector(extraneousPaths);
    return false;
  }
  return true;
}

/*
 * Any path pieces unvisited will be marked back to nothing
 * so that the paths do not make irregular jutting patterns
 */
int MapFactory::cleanupMap(){
  int tilesCleaned = 0;
  for(int row = 0; row < yDim; row++){
    for(int col = 0; col < xDim; col++){
      if(floorGrid.at(row).at(col) > 0 && extraneousPaths.at(row).at(col) == -1){
        floorGrid.at(row).at(col) = -1;
        tilesCleaned++;
      }
    }
  }
  return tilesCleaned;
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
         currSideEntries.push_back(row);
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
       if(row == 0){
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
  //we mark the entry as unavaible to everything including obstacles
  this -> unavailableSpots.at(entryYPos).at(entryXPos) = 1;
  int distanceForEntry = distances.at(entryYPos).at(entryXPos);

  //loop over up to two rows above the entry and
  //the two rows below the entry to mark off any spots as unavaiable for placement
  for(int row = entryYPos - 4; row < entryYPos + 4; row++){
    for(int col = entryXPos - 4; col < entryXPos + 4; col++){
      //if the position we are checking is within bounds
      if(row >= 0  && col >= 0 && col < xDim && row <yDim){

        //do not alter if this is the entrance because we already marked
        if(entryXPos == col && entryYPos == row){
          continue;
        }
        int currDistance = distances.at(row).at(col);
        int difference = abs(distanceForEntry - currDistance);
        if(difference < 3){
          unavailableSpots.at(row).at(col) = 1;
        }
      }
    }
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
          floorGrid.at(row).at(col) = (2 * ((int)(mapCustomizationChoices -> cafeteriaChoice))) * (-1);
        }
        else{
          floorGrid.at(row).at(col) = (2 * ((int)(mapCustomizationChoices -> cafeteriaChoice)) - 1) * (-1);
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
 * Make a path using an A* BFS
 * @param path: the path number identifier for this path
 */
bool MapFactory::makePathBFS(int path){
  //hold details for each tile
  vector<vector<CellNode>> board (yDim, vector<CellNode>(xDim));
  //hold the last position visited
  vector<int> lastPos(2);
  bool foundPath = getAStarDistances(board, path, lastPos);

  //if we find no path return false
  if(!foundPath){
    return false;
  }
  //otherwise mark the path on the grids
  else{
    markPath(board, path, lastPos);
    return true;
  }

}

/*
 * Iterate through the board and do an A*Search to find
 * the true distance from the path entrance to the
 * exit so that the path knows where to be generated
 * @param board: grid with a struct with details on each board position
 * @param path: the path identifier
 * @param lastPos: the last position we were at (assumed connected to the exit)
 */
bool MapFactory::getAStarDistances(vector<vector<CellNode>>& board, int path, vector<int>& lastPos){
  //make a pair for the entry
  intPair entryPosPair(entryPos.at((2*(path-1)+1)),entryPos.at(2*(path-1)));
  //make a pair for the exit
  intPair exitPosPair(exitPos.at(1),exitPos.at(0));

  //check the entrance is in the grid
  assert(isInMap(entryPosPair.first, entryPosPair.second));
  //check the exit is in the grid
  assert(isInMap(exitPosPair.first, exitPosPair.second));
  //check that the entrance is not an obstacle
  assert(aboveFloorGrid.at(entryPosPair.first).at(entryPosPair.second) > -2);
  //check that the exit is not an obstacle
  assert(aboveFloorGrid.at(exitPosPair.first).at(exitPosPair.second) > -2);

  //open list
  set<fPair> openList;
  //close list
  vector<vector<bool>> closedList(yDim, vector<bool>(xDim, false));

  for(int i=0;i<yDim;i++){
    for(int j=0;j<xDim;j++){
      board.at(i).at(j).f =  numeric_limits<double>::max() ;
      board.at(i).at(j).h =  numeric_limits<double>::max() ;
      board.at(i).at(j).g =  numeric_limits<double>::max() ;
      board.at(i).at(j).rowParent = -1;
      board.at(i).at(j).colParent = -1;
    }
  }

  //setup the starting cellNode
  int entryRow = entryPosPair.first;
  int entryCol = entryPosPair.second;

  board.at(entryRow).at(entryCol).f=0;
  board.at(entryRow).at(entryCol).h=0;
  board.at(entryRow).at(entryCol).g=0;
  board.at(entryRow).at(entryCol).rowParent=entryRow;
  board.at(entryRow).at(entryCol).colParent=entryCol;

  //if we are already connected with a path to the exit
  if(connectedWithExitPath(entryRow, entryCol, path)){
    lastPos.at(0) = entryRow;
    lastPos.at(1) = entryCol;
    return true;
  }

  //put the starting cell on the open list
  openList.insert(make_pair(0.0,make_pair(entryRow, entryCol)));

  bool atExit = false;

  //the directions we can go in
  vector<intPair> dirs = {make_pair(0,1), make_pair(0,-1),make_pair(1,0),make_pair(-1,0)};
  //while there are more cells to traverse
  while(!openList.empty()){
    //grabt the first thing in the set
    fPair current = *openList.begin();
    //remove it from the set
    openList.erase(openList.begin());

    //add the current row/tile to the closedList
    int closeRow = current.second.first;
    int closeCol = current.second.second;
    closedList.at(closeRow).at(closeCol) = true;

    //for all four directions check if they are the destination
    //if not check if they have been visited before or
    //if the current path is better than the path on the openList for it already
    for( intPair dir : dirs){
      int newRow = dir.first+closeRow;
      int newCol = dir.second+closeCol;


      int foundExit = evaluateDirection(newRow,newCol,closeRow,closeCol,
                      openList, closedList, board, path);
      if(foundExit){
        lastPos.at(0) = newRow;
        lastPos.at(1) = newCol;
        return true;
      }
    }
  }
  return false;
}

/*
 * If the current row and column are the exit position return true
 * else return false and add the current position to the open list if it has
 * not been visited. if is on the open list but the current path is better than
 * replace it
 * @param row: current row
 * @param col: current col
 * @param oldRow: the parent row
 * @param oldCol: the parent col
 * @param openList: the set of all nodes to visit
 * @param closedList: the grid of all nodes we have visited
 * @param board: a grid of with statistics on all the grids and their distances
 * @param path: current path
 */
bool MapFactory::evaluateDirection(int row, int col,int oldRow, int oldCol, set<fPair>& openList,
              vector<vector<bool>>& closedList, vector<vector<CellNode>>& board, int path){

  //only check if we are on the grid
  if(isInMap(row,col)){
    //if we are at the exit
    if(paths.at(row).at(col) == 0){
      board.at(row).at(col).rowParent=oldRow;
      board.at(row).at(col).colParent=oldCol;
      return true;
    }
    //if the tile has an obstacle or is on the list of visited nodes
    //ignore else do the following
    //or if there is an entrance already there
    else if(aboveFloorGrid.at(row).at(col) > -2 && closedList.at(row).at(col) != true
          &&!(isEntrance(row,col))){
      double g = board.at(oldRow).at(oldCol).g + 1.0;
      double h = distances.at(row).at(col);
      double f = g + h;
      if(board.at(row).at(col).f == numeric_limits<double>::max() || board.at(row).at(col).f > f){
        openList.insert(make_pair(f, make_pair(row,col)));
        board.at(row).at(col).f=f;
        board.at(row).at(col).g=g;
        board.at(row).at(col).h=h;
        board.at(row).at(col).rowParent=oldRow;
        board.at(row).at(col).colParent=oldCol;
      }
    }
  }
  return false;
}

/*
 * True if the current row and column are an entrance
 */
bool MapFactory::isEntrance(int row, int col){
  for(int pair = 0; pair < entryPos.size(); pair+=2){
    int checkrow = entryPos.at(pair+1);
    int checkcol = entryPos.at(pair);
    if(row == checkrow && col == checkcol){
      return true;
    }
  }
  return false;
}

/*
 * Follow the path to the exit and mark it on the grids
 * once it reaches the exit or a path leading to the exit we stop
 * @param board: the board with details on the distances
 * @param path: the integer we will use to mark this path
 */
void MapFactory::markPath(vector<vector<CellNode>>& board, int path, vector<int>& lastPos){
    //start at the index of your last position (could be the exit or adjacent to some other path)
    int currRow = lastPos.at(0);
    int currCol = lastPos.at(1);

    //if not at the exit poisiton mark the current space as a path
    if(!(currRow == exitPos.at(1) && currCol == exitPos.at(0))){
      //mark the space ass a path if it is not touching an exit path
      //and is not touching the exit itself
      if(!connectedWithExitPath(currRow, currCol, path) && !connectedWithExit(currRow, currCol)){
        paths.at(currRow).at(currCol) = path;
        floorGrid.at(currRow).at(currCol) = path;
      }
    }

    while(!(board.at(currRow).at(currCol).rowParent == currRow &&
            board.at(currRow).at(currCol).colParent == currCol) ){

      int tempRow = board.at(currRow).at(currCol).rowParent;
      int tempCol = board.at(currRow).at(currCol).colParent;

      //if not at the exit poisiton
      if(!(currRow == exitPos.at(1) && currCol == exitPos.at(0))){
        //if the next tile is not connected with an exit path but the current one is
        //we do actually mark it to make sure they are connected
        if(connectedWithExitPath(currRow, currCol, path) && !connectedWithExitPath(tempRow, tempCol, path)){
          paths.at(currRow).at(currCol) = path;
          floorGrid.at(currRow).at(currCol) = path;
        }
      }

      currRow = tempRow;
      currCol = tempCol;

      //mark the space as the path if there is not already a path
      if(!(paths.at(currRow).at(currCol) > -1)){
        //mark the space ass a path if it is not touching an exit path
        if(!connectedWithExitPath(currRow, currCol, path)){
          paths.at(currRow).at(currCol) = path;
          floorGrid.at(currRow).at(currCol) = path;
        }
      }
      //if we are adjacent to another path then we must mark that path as
      //to the exit
      vector<int> possibleConnections;
      possibleConnections = connectedWithNonExitPath(currRow, currCol, path);
      if(possibleConnections.size()!=0){
        for(int nonExitPath : possibleConnections){
          entrysToExit.at(nonExitPath - 1) = 1;
        }
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
   * @param newrow: the row index in the direction we are expanding (Y)
   * @param newcol: the col index in the direction we are expanding (X)
   * @param row: row index
   * @param col: col index
   * @param path: the numeric path indentifier
   * @return bool: whether the new row and column is touching the same path we are on
   */
 bool MapFactory::connectedWithSamePath(int newrow, int newcol, int row, int col, int path){

   return false;
   /*
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
   */
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
         //cout << "TOP" << endl;
         //cout << rowMinusOne << " " << newcol << endl;
         return true;
       }
     }
   }
   if(rowPlusOneIn){
     if(!(rowPlusOne == row && newcol == col)){
       if(paths.at(rowPlusOne).at(newcol) == path){
         //cout << "BOTTOM" << endl;
         //cout << rowPlusOne << " " << newcol << endl;
         return true;
       }
     }
   }
   if(colMinusOneIn){
     if(!(newrow == row && colMinusOne == col)){
       if(paths.at(newrow).at(colMinusOne) == path){
         //cout << "LEFT" << endl;
         //cout << newrow << " " << colMinusOne << endl;
         return true;
       }
     }
   }
   if(colPlusOneIn){
     if(!(newrow == row && colPlusOne == col)){
       if(paths.at(newrow).at(colPlusOne) == path){
         //cout << "RIGHT" << endl;
         //cout << newrow << " " << colPlusOne << endl;
         return true;
       }
     }
   }
   return false;
 }


  /*
   * @param newrow: the row index in the direction we are expanding (Y)
   * @param newcol: the col index in the direction we are expanding (X)
   * @param row: row index
   * @param col: col index
   * @param path: the numeric path indentifier
   * @return bool: whether the new row and column is completely surrounded by the same path
   */
  bool MapFactory::surroundedWithSamePath(int newrow, int newcol, int row, int col, int path){
    return false;
    int rowMinusOne = row -1;
    int rowPlusOne = row +1;
    int colMinusOne = col -1;
    int colPlusOne = col + 1;

    bool rowMinusOneIn = rowIsInMap(rowMinusOne);
    bool rowPlusOneIn = rowIsInMap(rowPlusOne);
    bool colMinusOneIn = colIsInMap(colMinusOne);
    bool colPlusOneIn = colIsInMap(colPlusOne);

    if(rowMinusOneIn){
      if(paths.at(rowMinusOne).at(newcol) != path){
        return false;
      }
    }
    if(rowPlusOneIn){
      if(paths.at(rowPlusOne).at(newcol) != path){
        return false;
    }
    }
    if(colMinusOneIn){
      if(paths.at(newrow).at(colMinusOne) != path){
        return false;
      }
    }
    if(colPlusOneIn){
      if(paths.at(newrow).at(colPlusOne) != path){
        return false;
      }
    }
    return true;
  }

 /*
  * @param newrow: the row index in the direction we are expanding (Y)
  * @param newcol: the col index in the direction we are expanding (X)
  * @param row: row index
  * @param col: col index
  * @param path: the numeric path indentifier
  * @return bool: whether the new row and column is touching the a different path than we are on
  */
 bool MapFactory::connectedWithOtherPath(int newrow, int newcol, int row, int col, int path){

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
       if(paths.at(rowMinusOne).at(newcol) != path && paths.at(rowMinusOne).at(newcol) > 0){
         return true;
       }
     }
   }
   if(rowPlusOneIn){
     if(!(rowPlusOne == row && newcol == col)){
       if(paths.at(rowPlusOne).at(newcol) != path && paths.at(rowPlusOne).at(newcol) > 0){
         return true;
       }
     }
   }
   if(colMinusOneIn){
     if(!(newrow == row && colMinusOne == col)){
       if(paths.at(newrow).at(colMinusOne) != path && paths.at(newrow).at(colMinusOne) > 0){
         return true;
       }
     }
   }
   if(colPlusOneIn){
     if(!(newrow == row && colPlusOne == col)){
       if(paths.at(newrow).at(colPlusOne) != path && paths.at(newrow).at(colPlusOne) > 0){
         return true;
       }
     }
   }
   return false;
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

  int randRowChosen = (int) randomVariates -> Equilikely(0, yDim-1);
  int randColChosen = (int) randomVariates -> Equilikely(0, xDim-1);

  //place obstacles until we have hit the specified number
  //or there are no more spaces
  while(placedObstacles < mapCustomizationChoices -> obstacleChoice &&
        placedObstacles < possiblePlacements){

    while(unavailableSpots.at(randRowChosen).at(randColChosen) == 1){
      randRowChosen = (int) randomVariates -> Equilikely(0, yDim-1);
      randColChosen = (int) randomVariates -> Equilikely(0, xDim-1);
    }

    //if there is already an obstacle there then do not place one
    //or is the space is marked off
    if (aboveFloorGrid.at(randRowChosen).at(randColChosen) <= -2 ||
        unavailableSpots.at(randRowChosen).at(randColChosen) == 1 ){
      continue;
    }

    //randomly decide if this obstacle is actually invisible and does
    //not count towards the total number of obstacles
    int isInvisible = randomVariates -> Equilikely(0,3);
    if(isInvisible > 2){
      aboveFloorGrid.at(randRowChosen).at(randColChosen) = -2;
      unavailableSpots.at(randRowChosen).at(randColChosen) = 1;
      vector<int> blockedSides(8);
      setBlockedSides(blockedSides,10);
      possiblePlacements = markUnavailableSpotsNearObstacle(randRowChosen, randColChosen, possiblePlacements, blockedSides, 10);
      placedInvisibleObstacles++;
      continue;
    }

    //roll a die to determine what type of obstacle will go here
    int obstacleType = (-1) * (int) randomVariates->Equilikely(3,maxObstacleVal);

    //place an obstacle at the chosen row and column
    aboveFloorGrid.at(randRowChosen).at(randColChosen) = obstacleType;
    unavailableSpots.at(randRowChosen).at(randColChosen) = 1;

    //vector where each index corresponds to a true (1) or false (1)
    //for left, right, top, bottom, top left, top right, bottom left, bottom right
    //and determines which sides around this obstacle can be blocked for future
    //placements (allows for multiple length or side obstacles)
    vector<int> blockedSides(8);
    setBlockedSides(blockedSides,6);

    //mark any spaces adjacient to the obstacle as unavaialble
    //for future path or entry or obstace placement
    //get the updated number of placement options
    possiblePlacements = markUnavailableSpotsNearObstacle(randRowChosen, randColChosen, possiblePlacements, blockedSides, 6);

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
  * @param maxVal: set what the maximum value generated for each tile being blocked
  */
void MapFactory::setBlockedSides(vector<int> &blockedSides, int maxVal){

    int isBlocked = (int) randomVariates -> Equilikely(0,maxVal);

    for(auto it = blockedSides.begin(); it != blockedSides.end(); ++it){
      *it = isBlocked;
      isBlocked = (int) randomVariates -> Equilikely(0,maxVal);
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
 * @param maxVal: the maximum value generated for a side to be blocked
 * @return int: the number of spots open left
 */

int MapFactory::markUnavailableSpotsNearObstacle(int row, int col, int currentOpenSpaces, vector<int> &blockedSides, int maxVal){
  //mark the spot as unavaiable for the placement of future obstacles
  // or paths
  unavailableSpots.at(row).at(col) = 1;
  currentOpenSpaces--;


  int rowMinus = row - 1;
  int rowPlus = row + 1;
  int colMinus = col - 1;
  int colPlus = col + 1;

  //value that the blocked path has to be higher than for a horizontal or vertical to be blocked
  int normalThreshold = (int) randomVariates -> Equilikely(0, maxVal/2);
  //value tha the blocked path has to higher than for a diagonal to be blocked
  int diagonalThreshold  = (int) randomVariates -> Equilikely(0, maxVal/2);

  //check all the directions
  //to see if they are in bounds and mark the spots as unavaiable
  //only checks marks them off if the passed value in
  //blockedSides vector is true (1)

  if(colMinus >= 0){
    //left
    if(blockedSides.at(0) > normalThreshold && unavailableSpots.at(row).at(colMinus) != 1){
      unavailableSpots.at(row).at(colMinus) = 1;
      currentOpenSpaces--;
    }

    //top left diagonal
    if(rowMinus >= 0){
      if(blockedSides.at(4) > diagonalThreshold && unavailableSpots.at(rowMinus).at(colMinus) != 1){
        unavailableSpots.at(rowMinus).at(colMinus) = 1;
        currentOpenSpaces--;
      }
    }
    //bottom left diagonal
    if(rowPlus < yDim){
      if(blockedSides.at(5) > diagonalThreshold && unavailableSpots.at(rowPlus).at(colMinus) != 1){
        unavailableSpots.at(rowPlus).at(colMinus) = 1;
        currentOpenSpaces--;
      }
    }
  }
  if(colPlus < xDim){
    //right
    if(blockedSides.at(1) > normalThreshold && unavailableSpots.at(row).at(colPlus) != 1){
      unavailableSpots.at(row).at(colPlus) = 1;
      currentOpenSpaces--;
    }

    //top right diagonal
    if(rowMinus >= 0){
      if(blockedSides.at(6) > diagonalThreshold && unavailableSpots.at(rowMinus).at(colPlus) != 1){
        unavailableSpots.at(rowMinus).at(colPlus) = 1;
        currentOpenSpaces--;
      }
    }
    //bottom right diagonal
    if(rowPlus < yDim){
      if(blockedSides.at(7) > diagonalThreshold && unavailableSpots.at(rowPlus).at(colPlus) != 1){
        unavailableSpots.at(rowPlus).at(colPlus) = 1;
        currentOpenSpaces--;
      }
    }
  }
  if(rowMinus >= 0){
    //top
    if(blockedSides.at(2) > normalThreshold && unavailableSpots.at(rowMinus).at(col) != 1){
      unavailableSpots.at(rowMinus).at(col) = 1;
      currentOpenSpaces--;
    }
  }
  if(rowPlus < yDim){
    //bottom
    if(blockedSides.at(3) > normalThreshold && unavailableSpots.at(rowPlus).at(col) != 1){
      unavailableSpots.at(rowPlus).at(col) = 1;
      currentOpenSpaces--;
    }
  }
 /*

  if(colMinus >= 0){
    //left
    unavailableSpots.at(row).at(colMinus) = 1;
    currentOpenSpaces--;


    //top left diagonal
    if(rowMinus >= 0){
        unavailableSpots.at(rowMinus).at(colMinus) = 1;
        currentOpenSpaces--;
      }

    //bottom left diagonal
    if(rowPlus < yDim){
      unavailableSpots.at(rowPlus).at(colMinus) = 1;
      currentOpenSpaces--;
    }
  }
  if(colPlus < xDim){
    //right
    unavailableSpots.at(row).at(colPlus) = 1;
    currentOpenSpaces--;

    //top right diagonal
    if(rowMinus >= 0){
      unavailableSpots.at(rowMinus).at(colPlus) = 1;
      currentOpenSpaces--;
    }
    //bottom right diagonal
    if(rowPlus < yDim){
      unavailableSpots.at(rowPlus).at(colPlus) = 1;
      currentOpenSpaces--;
      }
  }
  if(rowMinus >= 0){
    //top
    unavailableSpots.at(rowMinus).at(col) = 1;
    currentOpenSpaces--;
  }
  if(rowPlus < yDim){
    //bottom
    unavailableSpots.at(rowPlus).at(col) = 1;
    currentOpenSpaces--;
  }
  */
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
  int randRowChosen = (int) randomVariates -> Equilikely(0, yDim-1);
  int randColChosen = (int) randomVariates -> Equilikely(0, xDim-1);
  //if there are still spots on the board to place obstacles and
  //we still have more invisible obstacles to place
  while(placedInvisibleObstacles < minimumInvisibleObstacles && possiblePlacements > 0){
    while(unavailableSpots.at(randRowChosen).at(randColChosen) == 1){
      randRowChosen = (int) randomVariates -> Equilikely(0, yDim-1);
      randColChosen = (int) randomVariates -> Equilikely(0, xDim-1);
    }
    aboveFloorGrid.at(randRowChosen).at(randColChosen) = -2;
    unavailableSpots.at(randRowChosen).at(randColChosen) = 1;
    placedInvisibleObstacles++;
    vector<int> blockedSides(8);
    setBlockedSides(blockedSides,10);
    possiblePlacements = markUnavailableSpotsNearObstacle(randRowChosen, randColChosen, possiblePlacements, blockedSides, 10);
  }
}


/*
 * Any entry that is on the board and covered by another path value
 * will have its value placed back for cosmetic purposes
 */
void MapFactory::putEmptyEntriesOnBoard(){
  int pathNum = 1;
  for(int pair = 0; pair < entryPos.size(); pair+=2){
    int row = entryPos.at(pair+1);
    int col = entryPos.at(pair);

    if(paths.at(row).at(col) != pathNum){
      paths.at(row).at(col) = pathNum;
      floorGrid.at(row).at(col) = pathNum;
    }
    pathNum++;
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
        s << *it << " ";
      }
      else{
        cout << *it << "  ";
        s << *it << "  ";
      }
    }
    cout << endl;
    s << endl;
  }
  cout <<endl;
  s << endl;
}

template <class T>
void MapFactory::printVector(vector<T> &v){
  for(T &vec : v){
    cout << vec << " ";
    s << vec << " ";
  }
  cout <<endl;
  s << endl;
}

template <class T, class T2>
void MapFactory::printUnorderedMap(unordered_map<T,unordered_map<T,T2>> &uo){
  for(auto it: uo){
    cout << "Row " << (it).first << endl;
    s << "Row " << (it).first << endl;
    for(auto dt: it.second){
      cout <<  dt.first << " ";
      s <<  dt.first << " ";
    }
    cout << endl;
    s << endl;
  }
}

void MapFactory::printVectorCells(vector<vector<CellNode>>& board){
  for(int i = 0; i < yDim; i++){
    for(int j = 0; j < xDim; j++){
      s << (board.at(i).at(j).f < 100 ? board.at(i).at(j).f : -1)  << " ";
    }
    s << endl;
  }
  s << endl;
}

/*
 * Print the paths, and the aboveFloorGrid with some explanation when
 * an error occurs
 * @param errorType: the string identifier of the error
 */
void MapFactory::printError(string errorType){
  cout << errorType << endl << endl;

  cout << "Paths grid " << endl;
  cout << "0 is the exit " << endl;
  cout << "Positive integers are paths " << endl;
  cout << "Negative Integers indicate nothing is there " << endl;
  printVector(paths);

  cout << "Above Floor Grid " << endl;
  cout << "Shows placed obstacles " << endl;
  cout << "0 is the exit " << endl;
  cout << "-1 is empty" << endl;
  cout << "-2 is an invisible obstacle, so used only in map generation to make map twisting" << endl;
  cout << "-3 or less is a visible obstacle that blocks tower and path" << endl;
  printVector(aboveFloorGrid);
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

/*
 * @return MapChoices: all customizaton options for this map
 */
MapChoices& MapFactory::getMapCustomizationChoices(){
  return *(mapCustomizationChoices.get());
}

void MapFactory::setMapCustomizationChoices(MapChoices * newCustomization){
  this -> mapCustomizationChoices.reset(newCustomization);
}
void MapFactory::setMapObstacleChoice(int obstacleChoice){
  mapCustomizationChoices -> obstacleChoice = obstacleChoice;
}
void MapFactory::setMapCafeteriaChoice(cafeteria cafeteriaChoice){
  mapCustomizationChoices -> cafeteriaChoice = cafeteriaChoice;
}
void MapFactory::setMapEntryChoice(int pathEntryChoice){
  mapCustomizationChoices -> pathEntryChoice = pathEntryChoice;
}
