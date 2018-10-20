#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "MapFactory.hpp"

class BoardManager{
private:
    //random map generator
    unique_ptr<MapFactory> mapFactory;

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


public:
  BoardManager();

  void newMap();
  void newMap(MapChoices * newCustomization);

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

};
#endif
