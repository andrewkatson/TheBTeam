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

  //TODO remove when done checking grids
  this -> printVector(this -> paths);
  this -> printVector(this -> distances);
  this -> printVector(this -> floorGrid);
  this -> printVector(this -> aboveFloorGrid);
  cout << endl << endl;

  paths.clear();
  distances.clear();
  floorGrid.clear();
  aboveFloorGrid.clear();
  exitPos.clear();
}
}

//set all values in each map grid to -1
void MapFactory::initGridArrays(){

  //set each row to -1
  for(int i = 0; i < this -> yDim; i++) {
      this -> paths.push_back(vector<int>(this -> xDim, -1));
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
   * value will be the row. if you have selected up or down side
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
  //if this is the up or down side
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
        this -> exitPos.push_back(exitIndexOnSide);
        this -> exitPos.push_back(0);
        break;
      case 1:
        this -> exitPos.push_back(exitIndexOnSide);
        this -> exitPos.push_back(this -> floorGrid[0].size() - 1);
        break;
      case 2:
        this -> exitPos.push_back(0);
        this -> exitPos.push_back(exitIndexOnSide);
        break;
      case 3:
      default:
        this -> exitPos.push_back(this -> floorGrid.size() - 1);
        this -> exitPos.push_back(exitIndexOnSide);
        break;
  }

  //set a 0 at the index specified as exit in each of the grid arrays
  this -> paths[exitPos[0]][exitPos[1]] = 0;
  this -> distances[exitPos[0]][exitPos[1]] = 0;
  this -> floorGrid[exitPos[0]][exitPos[1]] = 0;
  this -> aboveFloorGrid[exitPos[0]][exitPos[1]] = 0;
}

//set each entry on all the map grids
void MapFactory::makeEntry(){

}

template <class T>
void MapFactory::printVector(vector<vector<T>> v){
  for(vector<int> vec : v){
    for(auto it = vec.begin(); it != vec.end(); ++it){
      cout << *it << " ";
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
