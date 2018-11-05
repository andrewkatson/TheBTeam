#include "../include/Towers/NotATower.hpp"

NotATower::NotATower(shared_ptr<TextLoader> textLoader,string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = towerTypeID;
}

void NotATower::upgrade(){}

void NotATower::setProjectile(){}
