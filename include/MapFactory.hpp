#ifndef MAPFACTORY_H
#define MAPFACTORY_H
#include "Direction.hpp"
#include "MapChoices.hpp"
#include "RandomVariates.hpp"
#include <vector>
#include <memory>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <iterator>
#include <stdexcept>

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
using std::next;
using std::begin;
using std::out_of_range;

class MapFactory{
private:

  //a container class with customization options for this map
  unique_ptr<MapChoices> mapCustomizationChoices;

  // a minimum number of invisible obstacles used to make
  //the path more windy. they do not block tower placement
  int minimumInvisibleObstacles = 6;

  //x dimension of board
  int xDim;
  //y dimension of board
  int yDim;

  /* the side the exit is on
   * so if it is in the right hand column then
   * the direction is right
   */
  Direction exitDirection;;

  /* the side of the entry starting positiions
   */
  vector<Direction> entryDirections;

  //array identifying the exit position (x_1,y_1)
  vector<int> exitPos;

  //array with each entry position (x_1,y_1,x_2,y_2,...)
  vector<int> entryPos;

  //array to keep track of which paths lead to exit. 0 is no and 1 is yes
  vector<int> entrysToExit;

  /*
   * 2d array used by recursive functions to mark where that path has gone before
   */
  vector<vector<int>> markPathSoFar;

  /*
   * 2d array where any index not related to a path tile
   * is a -1, the exit is 0, and any path is identified with n >= 1
   */
  vector<vector<int>> paths;

  /*
   * 2d array where any index will be marked to indicate if an entry or obstacle can be
   * placed at that position ( 1 is no to anything, 0 is no to entries but yes to obstacles
   * , and -1 is anything can be placed);
   */
  vector<vector<int>> unavailableSpots;

  /*
   * 2d array where the index has a value indicating the distance
   * from the exit from that spot. a -1 is used for a tile that is not
   * a tile on a path and 0 is used for the exit. any path tile is
   * assigned a value n >= 1
   */
  vector<vector<int>> distances;

   /*
    * 2d array where the index has a value indicating the texture used
    * on the board at that position. only considers the "floor" so any non path
    * tile, a path tile, or the exit tile. 0 is reserved for the exit. posiitve
    * numbers are for path tiles. negative values are for non path tiles.
    */
   vector<vector<int>> floorGrid;

    /*
     * 2d array where the index has a value indicating the texture used on the
     * board at that position ABOVE the floor level. These values correspond
     * to towers and obstacles. -1 indicates nothing is at this space.
     * 0 is the exit. positive numbers are towers. negative numbers less than
     * -1 are different obstacles (-2 means an invisible obstacle, i.e. no
     * obstacle texture is rendered and it will not matter for tower placement
     * but the path will avoid it)
     */
  vector<vector<int>> aboveFloorGrid;

  /*
   * generate any random variates needed by the map factory
   */
  unique_ptr<RandomVariates> randomVariates = unique_ptr<RandomVariates>(new RandomVariates());

  void generateDimensions();

  void initGridArrays();

  void makeExit();
  int chooseIndexOfExit(int side);
  void placeExit(int exitSide, int exitIndexOnSide);
  void makeDistances();
  void setUnavailableSpotsFromExit(int exitXPos, int exitYPos);


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

  void makePath(int pathNumber);
  bool connectedWithExit(int row, int col);
  bool connectedWithExitPath(int row, int col , int path);
  vector<int> connectedWithNonExitPath(int row, int col, int path);
  vector<Direction::Directions> calcNextShortestStep(int row, int col, int lastRow, int lastCol);
  bool connectedWithSamePath(int newrow, int newcol, int row, int col, int path);
  void removeObstacleInShortestStep(int row, int col);
  int expandInRow(int row, Direction::Directions expandDirection);
  int expandInCol(int col, Direction::Directions expandDirection);

  void makeObstacles();
  int countPossibleObstaclePositions();
  bool completesWings(int row, int col);
  void setBlockedSides(vector<int> &blockedSides);
  int markUnavailableSpotsNearObstacle(int row, int col, int currentOpenSpaces, vector<int> &blockedSides);
  void placeRemainingInvisibleObstacles(int placedInvisibleObstacles, int possiblePlacements);

  bool isInMap(int row, int col);
  bool rowIsInMap(int row);
  bool colIsInMap(int col);

  template <class T>
  void printVector(vector<vector<T>> &v);
  template <class T>
  void printVector(vector<T> &v);
  template <class T, class T2>
  void printUnorderedMap(unordered_map<T,unordered_map<T,T2>> &uo);

public:

  MapFactory(MapChoices *mapCustomizationChoices);

  void generateMap();
  vector<int>& getExitPos();
  vector<int>& getEntryPos();
  vector<vector<int>>& getDistances();
  vector<vector<int>>& getFloor();
  vector<vector<int>>& getAboveFloor();
  int getXDim();
  int getYDim();

  void setMapCustomizationChoices(MapChoices * newCustomization);
  void setMapObstacleChoice(int obstacleChoice);
  void setMapCafeteriaChoice(int cafeteriaChoice);
  void setMapEntryChoice(int pathEntryChoice);

};

#endif
