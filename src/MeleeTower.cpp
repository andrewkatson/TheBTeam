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

/*
 * Initialize all the units that will spawn for this tower
 */
void MeleeTower::setUpUnits(){}

/*
 * Set the point where the melee units attached to this tower will go back to
 * when they are not fighting
 * @param x: the x coordinate
 * @param y: the y coordinate
 */
void MeleeTower::resetRallyPoint(int x, int y){
  //if this rally point is not in the prescribed radius around the tower
  if(x<xCoordinate-radius || x>xCoordinate+radius || y<yCoordinate-radius || y>yCoordinate+radius){
    return;
  }
  this -> xRally = x;
  this -> yRally = y;
}

int MeleeTower::getPrice(){
  return this -> price;
}
