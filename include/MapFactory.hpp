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
#include <unordered_map>

using std::vector;
using std::unique_ptr;
using std::abs;
using std::min;
using std::random_shuffle;
using std::fill;
using std::cout;
using std::endl;
using std::iota;
using std::unordered_map;

class MapFactory{
private:

  unique_ptr<MapChoices> mapCustomizationChoices;

  //x dimension of board
  int xDim;
  //y dimension of board
  int yDim;

  /* the side the exit is on
   * so if it is in the right hand column then
   * the direction is right
   */
  Direction exitDirection;

  /* the side of the entry starting positiions
   */
  vector<Direction> entryDirections;

  //array identifying the exit position (x_1,y_1)
  vector<int> exitPos;

  //array with each entry position (x_1,y_1,x_2,y_2,...)
  vector<int> entryPos;

  //array to keep track of which paths lead to exit. 0 is no and 1 is yes
  vector<int> entrysToExit;

  /* 2d array where any index not related to a path tile
   * is a -1, the exit is 0, and any path is identified with n >= 1
   */
  vector<vector<int>> paths;

  /* 2d array where any index will be marked to indicate if an entry can be
   * placed at that position (-1 is default, 0 is no, and 1 is yes);
   */
  vector<vector<int>> unavailableSpots;

  /*
   * unordered_map where each key is row on the board
   * and each value is another unordered_map with the columns
   * that unordered_map has a boolean that has no purpose at the moment
   */
   unordered_map<int, unordered_map<int, bool>> pathAdjacient;

  /*
   *  2d array to complement the unordered_map of adjacient spaces
   *  use it to visualize what spaces are being marked off as path adjacient
   *  no other purpose
   */
  vector<vector<int>> adjacientPathSpots;

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
  Direction::Directions entriesOnFurthestSide(vector<int> &possibleEntries);
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

  void makeFloor();

  void makeDistances();

  void makePath(int pathNumber);
  void addAdjacientsTiles(int row, int col);
  void removeAdjacientTiles(int row, int col);
  bool canExpand(Direction::Directions expand, int row, int col, int path);
  bool connectedWithExit(int row, int col);
  bool connectedWithSamePath(int row, int col, int newrow, int newcol, int path);
  bool connectedWithExitPath(int row, int col , int path);
  vector<int> connectedWithNonExitPath(int row, int col, int path);
  vector<Direction::Directions> calcNextShortestStep(int row, int col, int lastShortestDistance);
  int expandInRow(int row, Direction::Directions expandDirection);
  int expandInCol(int col, Direction::Directions expandDirection);

  void makeObstacles();

  template <class T>
  void printVector(vector<vector<T>> &v);
  template <class T>
  void printVector(vector<T> &v);
  template <class T, class T2>
  void printUnorderedMap(unordered_map<T,unordered_map<T,T2>> &uo);

  double Equilikely(double a, double b);
  double Geometric(double p);
  double Exponential(double m);
  double Uniform(double a, double b);

};

#endif
