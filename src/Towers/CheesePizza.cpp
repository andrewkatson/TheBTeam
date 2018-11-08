#include "Towers/CheesePizza.hpp"

CheesePizza::CheesePizza(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_CPT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_CPT_RA"));
  this -> price = textLoader->getInteger(string("IDS_CPT_PR"));
}

void CheesePizza::upgrade(){}

void CheesePizza::setProjectile(){
  this-> currentProjectile = make_shared<CheesePizzaProjectile>(textLoader, eventManager);
}
