#ifndef MAPFACTORY_H
#define MAPFACTORY_H
#include "Direction.hpp"
#include "MapChoices.hpp"
#include "RandomVariates.hpp"
#include "TextLoader.hpp"
#include <vector>
#include <memory>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>
#include <assert.h>
#include <set>
#include <unordered_set>
#include <limits>
#include <random>

using std::vector;
using std::unique_ptr;
using std::shared_ptr;
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
using std::stringstream;
using std::string;
using std::pair;
using std::make_pair;
using std::set;
using std::numeric_limits;
class MapFactory{
private:

  //f = g + h
  //g is the distance from the starting tile to the current tile
  //h is the estimated (Manhattan) distance from the current tile to the end

  //Used to hold row, col data for A* BFS
  struct CellNode{
    double f,g,h;
    int rowParent;
    int colParent;
  };

  //int pair (used to assocaite a row and col)
  typedef pair<int,int> intPair;


  //double - int int pair (used to associate f with a row col)
  typedef pair<double, intPair> fPair;

  //random number generator (seeded in the constructor)
  std::mt19937 mt;

  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;

  //a container class with customization options for this map
  unique_ptr<MapChoices> mapCustomizationChoices;

  // a minimum number of invisible obstacles used to make
  //the path more windy. they do not block tower placement
  int minimumInvisibleObstacles;

  //x dimension of board
  int xDim;
  //y dimension of board
  int yDim;

  //a value for the absolute value of the last obstacle type that can be placed
  //so if a -4 is the last obstacle (the other being -3) then this is 4
  int maxObstacleVal;

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
   * 2d array where any index not related to a path tile
   * is a -1, the exit is 0, and any path is identified with n >= 1
   */
  vector<vector<int>> paths;

  /*
   * 2d array that is used to verify that there are no extraneous tiles generated
   * from paths
   */
  vector<vector<int>> extraneousPaths;

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

  vector<vector<std::unordered_set<int>>> combinedPaths;

  int softReset;
  int hardReset;
  int numObstaclesRemoved;

  stringstream s;

  void generateDimensions();
  bool tryAMap();
  void initGridArrays();
  void resetEverything();
  bool allPathsToExit();
  bool checkPathToExit(int row, int col);
  int cleanupMap();

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

  void makeFloor();

  bool makePathBFS(int path);
  bool getAStarDistances(vector<vector<CellNode>>& board, int path,vector<int>& lastPos);
  bool evaluateDirection(int row, int col, int oldRow, int oldCol, set<fPair>& openList,
              vector<vector<bool>>& closedList, vector<vector<CellNode>>& board, int path);
  bool isEntrance(int row, int col);
  void markPath(vector<vector<CellNode>>& board, int path,vector<int>& lastPos);
  void mergeToMain(vector<vector<CellNode>>& board);


  bool connectedWithExit(int row, int col);
  bool connectedWithExitPath(int row, int col , int path);
  vector<int> connectedWithNonExitPath(int row, int col, int path);
  bool connectedWithSamePath(int newrow, int newcol, int row, int col, int path);
  bool surroundedWithSamePath(int newrow, int newcol, int row, int col, int path);
  bool connectedWithOtherPath(int newrow, int newcol, int row, int col, int path);

  int expandInRow(int row, Direction::Directions expandDirection);
  int expandInCol(int col, Direction::Directions expandDirection);

  void makeObstacles();
  int countPossibleObstaclePositions();
  bool completesWings(int row, int col);
  void setBlockedSides(vector<int> &blockedSides, int maxVal);
  int markUnavailableSpotsNearObstacle(int row, int col, int currentOpenSpaces, vector<int> &blockedSides, int maxVal);
  void placeRemainingInvisibleObstacles(int placedInvisibleObstacles, int possiblePlacements);

  void putEmptyEntriesOnBoard();

  bool rowIsInMap(int row);
  bool colIsInMap(int col);

  void printVectorCells(vector<vector<CellNode>>& board);
  template <class T>
  void printVector(vector<T> &v);
  template <class T, class T2>
  void printUnorderedMap(unordered_map<T,unordered_map<T,T2>> &uo);
  void printError(string errorType);

public:

  MapFactory(MapChoices *mapCustomizationChoices, shared_ptr<TextLoader> textLoader);

  void generateMap();
  vector<int>& getExitPos();
  vector<int>& getEntryPos();
  vector<vector<int>>& getDistances();
  vector<vector<int>>& getFloor();
  vector<vector<int>>& getAboveFloor();
  int getXDim();
  int getYDim();
  MapChoices& getMapCustomizationChoices();

  bool isInMap(int row, int col);

  void setMapCustomizationChoices(MapChoices * newCustomization);
  void setMapObstacleChoice(int obstacleChoice);
  void setMapCafeteriaChoice(cafeteria cafeteriaChoice);
  void setMapEntryChoice(int pathEntryChoice);

  template <class T>
  void printVector(vector<vector<T>> &v);


  vector<vector<std::unordered_set<int>>>& getCombinedPaths();
};

#endif
