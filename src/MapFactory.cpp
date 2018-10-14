#include "MapFactory.hpp"


MapFactory::MapFactory(MapChoices *mapCustomizationChoices, int xDim, int yDim){
  this -> mapCustomizationChoices = unique_ptr<MapChoices>(mapCustomizationChoices);

  //checks to ensure that the dimensions are never negative or 0
  if(xDim <= 0){
    xDim = 1;
  }
  if(yDim <= 0){
    yDim = 1;
  }
  this -> xDim = xDim;
  this -> yDim = yDim;

  //set seed for random number generator from file rngs
  time_t t;
  PutSeed(time(&t));
}

//fill all four grids with valid values for a map
void MapFactory::generateMap(){
  for(int i = 0; i < 10; i++){
  //initializes all vector indicies to -1
  this -> initGridArrays();

  //place an exit on all boards
  this -> makeExit();

  //place an entry on all boards
  for(int e = 0; e < this -> mapCustomizationChoices -> pathEntryChoice; e++){
    // add one because the path number should always start at 1 since 0
    // is the exit
    this -> makeEntry(e + 1);
  }

  //TODO remove when done checking grids
  this -> printVector(this -> paths);
  this -> printVector(this -> unavailableSpots);
  //this -> printVector(this -> distances);
  //this -> printVector(this -> floorGrid);
  //this -> printVector(this -> aboveFloorGrid);
  cout << endl << endl;

  paths.clear();
  unavailableSpots.clear();
  distances.clear();
  floorGrid.clear();
  aboveFloorGrid.clear();
  exitPos.clear();
  entryPos.clear();
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
      for(int j = 0; j < xDim/2; j++){
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
      for(int j = xDim - 1; j >= xDim / 2; j--){
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
      for(int j = 0; j < yDim/2; j++){
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
      for(int j = yDim - 1; j >= yDim / 2; j--){
        unavailableSpots[j][i] = 0;
      }
    }
    unavailableSpots[yDim - 1][i] = 0;
  }
}

//set each entry on all the map grids
void MapFactory::makeEntry(int pathNumber){
  vector<Direction::Directions> otherThreeSides;

  //get all three other directions that are not on the exit's side of the map
  otherThreeSides = this -> exitDirection.allOtherDirections(this -> exitDirection.facing);

  //shuffle the other sides so we will pick one random side each time
  random_shuffle(otherThreeSides.begin(), otherThreeSides.end());

  //vector to hold all the entries on the chosen side of the grid
  vector<int> entriesOnSide;

  int chosenSideIndex = -1;

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

  /*
   * generate a value in the range of the possible entries on this side
   * then select one of these indicies
   */
   int index = (int) Equilikely(0, entriesOnSide.size() - 1);
   int entryIndex = entriesOnSide.at(index);

   //set a pathNumber on each grid where the entry should be
   this -> placeEntry(otherThreeSides[chosenSideIndex], entryIndex, pathNumber);
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
    unavailableSpots.at(entryYPos).at(entryXPos - 1) = 0;
  }
  else{
    unavailableSpots.at(entryYPos + 1).at(entryXPos) = 0;
  }
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
