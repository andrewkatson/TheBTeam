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

using std::shared_ptr;
class MeleeTower : public TowerInterface{
private:
//the specific tower of melee type this is
shared_ptr<MeleeTower> currentTower;
//the specific units that are fighitng for this tower
shared_ptr<MeleeUnit> currentUnits;
public:
  MeleeTower();
  MeleeTower(shared_ptr<MeleeTower> startingTower);

  void upgrade();
};

 #endif
