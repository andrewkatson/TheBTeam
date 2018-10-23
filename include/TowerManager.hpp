/*
  TowerManager.hpp

  Purpose: Manage the defensive tower units on the map

  @author Andrew Katson
 */

#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H
#include "TowerInterface.hpp"
#include <vector>

using std::vector;
class TowerManager{

//All possible towers that can be purchased
vector<TowerInterface> towersToChoose;

//Towers placed on the board
vector<TowerInterface> towersPlaced;

public:
  TowerManager();
};
#endif
