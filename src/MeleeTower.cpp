#include "MeleeTower.hpp"
//empty constructor used for derived classes to call
MeleeTower::MeleeTower(){}

/*
 * Constructor with a reference to another melee tower (a derived class) that
 * holds the texture, statistics, and the next upgrade for this tower
 * @param startingTower: the starting tower of a branch
 */
MeleeTower::MeleeTower(shared_ptr<MeleeTower>  startingTower){
  this -> currentTower = startingTower;
}

void MeleeTower::upgrade(){}
