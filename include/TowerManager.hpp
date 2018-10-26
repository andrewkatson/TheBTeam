/*
  TowerManager.hpp

  Purpose: Manage the defensive tower units on the map

  @author Andrew Katson
 */

#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H
#include "TowerInterface.hpp"
#include "EventManager.hpp"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class TowerManager{

//event manager (used to register, deregister from events, and create them)
shared_ptr<EventManager> eventManager;

//All possible towers that can be purchased
vector<unique_ptr<TowerInterface>> towersToChoose;

//Towers placed on the board
//the integer key is the row*collength + colindex of the tower on the map
unordered_map<int, shared_ptr<TowerInterface>> towersPlaced;

//xdim of map (cols)
int xDim;

//ydim of map(rows)
int yDim;

public:
  TowerManager(shared_ptr<EventManager> eventManager, int yDim ,int xDim);

  vector<unique_ptr<TowerInterface>>& getTowersToChoose();

  unordered_map<int, shared_ptr<TowerInterface>>& getTowersPlaced();

  shared_ptr<TowerInterface> getTowerPlaced(int combinedRowCol);
  shared_ptr<TowerInterface>getTowerPlaced(int row, int col);

private:
  void addTower(int type, int combinedRowCol);
  void addTower(int type, int row, int col);

  void removeTower(int combinedRowCol);
  void removeTower(int row, int col);

  void upgradeTower(int combinedRowCol);
  void upgradeTower(int row, int col);
};
#endif
