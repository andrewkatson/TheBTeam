#include "../include/Towers/NotATower.hpp"

NotATower::NotATower(string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
}

void NotATower::upgrade(){}

void NotATower::setProjectile(){}
