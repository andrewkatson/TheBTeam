#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "MapFactory.hpp"
#include "EventManager.hpp"
#include "TextLoader.hpp"
#include "../include/Events/TowerCreationEvent.hpp"
#include <functional>
#include <assert.h>

using namespace std::placeholders;
class BoardManager{
private:

    //int pair (used to assocaite a row and col)
    typedef pair<int,int> intPair;

    //Store the textLoader to make requests for strings and constants
    shared_ptr<TextLoader> textLoader;
    //random map generator
    unique_ptr<MapFactory> mapFactory;

    //event manager (used to register, deregister from events, and create them)
    shared_ptr<EventManager> eventManager;

    // grid of the distance from the exit from each tile
    // exit is 0 and all the others are positive numbers
    vector<vector<int>> distances;

    //grid of the placement of obstacles (and towers) above the board
    // 0 is the exit, -1 is nothing there, any value below -1 is an obstacle
    // any value above 0 is a tower.
    vector<vector<int>> aboveFloorGrid;

    //grid of the placement of normal tiles and the path on the board
    // 0 is the exit. negative numbers are floor tiles and posiitve numbers
    // are the path to the exit
    vector<vector<int>> floorGrid;

    /*
     * Holds every obstacle on the above floor grid
     * keyed by their type with a value of their position
     */
    unordered_map<int, intPair> allObstacles;

public:
  BoardManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  void registerDelegates();

  void newMap();
  void newMap(MapChoices * newCustomization);

  void setMapBoards();

  void handleTowerCreation(const EventInterface& event);

  bool hasMap();
  bool isTowerOrObstacle(int row, int col);
  bool isExit(int row, int col);
  bool isPath(int row, int col);
  bool isObstacle(int row, int col);

  int getYDim();
  int getXDim();

  void setMapCustomizationChoices(MapChoices * newCustomization);
  void setMapObstacleChoice(int obstacleChoice);
  void setMapCafeteriaChoice(int cafeteriaChoice);
  void setMapEntryChoice(int pathEntryChoice);

  vector<vector<int>>const & getDistances();
  vector<int>const & getDistancesRow(int row);
  vector<int>const & getDistanceCol(int col);
  int getDistanceRowCol(int row, int col);

  vector<vector<int>>const & getAboveFloor();
  vector<int>const & getAboveFloorRow(int row);
  vector<int>const & getAboveFloorCol(int col);
  int getAboveFloorRowCol(int row, int col);

  vector<vector<int>>const & getFloor();
  vector<int>const & getFloorRow(int row);
  vector<int>const & getFloorCol(int col);
  int getFloorRowCol(int row, int col);

  vector<int>& getEntryPositions();

  unordered_map<int,intPair>& getAllObstacles();
};
#endif
