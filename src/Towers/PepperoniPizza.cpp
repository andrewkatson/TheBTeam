#include "Towers/PepperoniPizza.hpp"
PepperoniPizza::PepperoniPizza(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PPT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PPT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PPT_PR"));
}

void PepperoniPizza::upgrade(){}

void PepperoniPizza::setProjectile(){
  this-> currentProjectile = make_shared<PepperoniPizzaProjectile>(textLoader, eventManager);
}
