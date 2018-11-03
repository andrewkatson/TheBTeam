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
  //int pair (used to assocaite a row and col)
  typedef pair<int,int> intPair;
  //the total number of units that a melee tower can have
  int totalUnits;
  //the speed that dead units will respawn
  int respawnSpeed;
  //the x coordinate of the rally point for this tower
  int xRally;
  //the y coordinate of the rally point for this tower
  int yRally;
  //the specific units that are fighitng for this tower
  vector<shared_ptr<MeleeUnit>> currentUnits;

public:
  MeleeTower();

  virtual void upgrade();
  virtual void setUpUnits();
  void resetRallyPoint(int x, int y);
  /*
   * @return the price of the tower
   */
  int getPrice();

  string getType(){return towerTypeID;}

  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}
};

 #endif
