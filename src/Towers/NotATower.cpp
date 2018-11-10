#include "Towers/NotATower.hpp"

NotATower::NotATower(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = textLoader->getTypeID(string("IDS_NT"));
}

void NotATower::upgrade(){}

void NotATower::setProjectile(){}
