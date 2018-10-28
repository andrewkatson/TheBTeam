#include "RangeTower.hpp"

//empty constructor used for derived classes to call
RangeTower::RangeTower(){}

/*
 * Constructor with a reference to another ranged tower (a derived class) that
 * holds the texture, statistics, and the next upgrade for this tower
 * @param startingTower: the starting tower of a branch
 */
RangeTower::RangeTower(shared_ptr<RangeTower> startingTower){
  this -> currentTower = startingTower;
}

void RangeTower::upgrade(){}

void RangeTower::setProjectile(){}

int RangeTower::getPrice(){
  return this -> price;
}
