#include "Towers/DeepDish.hpp"

DeepDish::DeepDish(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_DDT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_DDT_RA"));
  this -> price = textLoader->getInteger(string("IDS_DDT_PR"));
}

void DeepDish::upgrade(){}

void DeepDish::setProjectile(){
  this-> currentProjectile = make_shared<DeepDishProjectile>(textLoader, eventManager);
}
