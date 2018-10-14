#ifndef MAPFACTORY_H
#define MAPFACTORY_H
#include "Direction.hpp"
#include "MapChoices.hpp"
#include "rngs.hpp"
#include <vector>
#include <memory>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <numeric>

using std::vector;
using std::unique_ptr;
using std::abs;
using std::random_shuffle;
using std::fill;
using std::cout;
using std::endl;
using std::iota;

class MapFactory{
private:

  unique_ptr<MapChoices> mapCustomizationChoices;

  //x dimension of board
  int xDim;
  //y dimension of board
  int yDim;

  /* the direction the exit is facing
   * so if it is in the right hand column then
   * the direction is Left
   */
  Direction exitDirection;

  //array identifying the exit position (x_1,y_1)
  vector<int> exitPos;

  //array with each entry position (x_1,y_1,x_2,y_2,...)
  vector<int> entryPos;

  /* 2d array where any index not related to a path tile
   * is a -1, the exit is 0, and any path is identified with n >= 1
   */
  vector<vector<int>> paths;

  /* 2d array where any index will be marked to indicate if an entry can be
   * placed at that position (-1 is defualt, 0 is no, and 1 is yes);
   */
  vector<vector<int>> unavailableSpots;

  /* 2d array where the index has a value indicating the distance
   * from the exit from that spot. a -1 is used for a tile that is not
   * a tile on a path and 0 is used for the exit. any path tile is
   * assigned a value n >= 1
   */
  vector<vector<int>> distances;

   /* 2d array where the index has a value indicating the texture used
    * on the board at that position. only considers the "floor" so any non path
    * tile, a path tile, or the exit tile. 0 is reserved for the exit. posiitve
    * numbers are for path tiles. negative values are for non path tiles.
    */
   vector<vector<int>> floorGrid;

    /* 2d array where the index has a value indicating the texture used on the
     * board at that position ABOVE the floor level. These values correspond
     * to towers and obstacles. -1 indicates nothing is at this space.
     * 0 is the exit. positive numebers are towers. negative numbers less than
     * -1 are different obstacles
     */
    vector<vector<int>> aboveFloorGrid;

public:

  MapFactory(MapChoices *mapCustomizationChoices, int xDim, int yDim);

  void generateMap();

  void initGridArrays();

  void makeExit();
  int chooseIndexOfExit(int side);
  void placeExit(int exitSide, int exitIndexOnSide);
  void setUnavailableSpotsFromExit(int exitXPos, int exitYPos);
  void setUnavailableSpotsFromLeftExit(int exitXPos, int exitYPos);
  void setUnavailableSpotsFromRightExit(int exitXPos, int exitYPos);
  void setUnavailableSpotsFromTopExit(int exitXPos, int exitYPos);
  void setUnavailableSpotsFromBottomExit(int exitXPos, int exitYPos);

  void makeEntry(int pathNumber);
  bool aSideIsNotFull(vector<Direction::Directions> &sides);
  bool sideIsNotFull(Direction::Directions &side, vector<int> &possibleEntries);
  bool leftSideIsNotFull(vector<int> &possibleEntries);
  bool rightSideIsNotFull(vector<int> &possibleEntries);
  bool topSideIsNotFull(vector<int> &possibleEntries);
  bool bottomSideIsNotFull(vector<int> &possibleEntries);
  void placeEntry(Direction::Directions &entrySide, int entryIndexOnSide, int pathNumberOfEntry);
  void setUnavailableSpotsFromEntry(int entryXPos, int entryYPos);
  void setUnavailableSpotsFromLeftEntry(int entryXPos, int entryYPos);
  void setUnavailableSpotsFromRightEntry(int entryXPos, int entryYPos);
  void setUnavailableSpotsFromTopEntry(int entryXPos, int entryYPos);
  void setUnavailableSpotsFromBottomEntry(int entryXPos, int entryYPos);

  template <class T>
  void printVector(vector<vector<T>> &v);

  double Equilikely(double a, double b);
  double Geometric(double p);
  double Exponential(double m);
  double Uniform(double a, double b);

};

#endif
