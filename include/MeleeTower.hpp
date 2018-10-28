/*
  MeleeTower.hpp

  Purpose: A defensive tower unit that spawns actor units to fight enemy npc actors

  @author Andrew Katson
 */

 #ifndef MELEETOWER_H
 #define MELEETOWER_H
#include "TowerInterface.hpp"
#include "MeleeUnit.hpp"
#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;
using std::make_shared;
class MeleeTower : public TowerInterface{
protected:
  //the total number of units that a melee tower can have
  int totalUnits;
  //the speed that dead units will respawn
  int respawnSpeed;
  //the x coordinate of the rally point for this tower
  int xRally;
  //the y coordinate of the rally point for this tower
  int yRally;
  //the specific tower of melee type this is
  shared_ptr<MeleeTower> currentTower;
  //the specific units that are fighitng for this tower
  vector<shared_ptr<MeleeUnit>> currentUnits;

public:
  MeleeTower();
  MeleeTower(shared_ptr<MeleeTower> startingTower);

  virtual void upgrade();
  virtual void setUpUnits();
  void resetRallyPoint(int x, int y);
  /*
   * @return the price of the tower
   */
  int getPrice();
};

 #endif
