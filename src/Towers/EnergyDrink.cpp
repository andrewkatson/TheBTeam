#include "Towers/EnergyDrink.hpp"

EnergyDrink::EnergyDrink(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_EDT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_EDT_RA"));
  this -> price = textLoader->getInteger(string("IDS_EDT_PR"));
}

void EnergyDrink::upgrade(){}

void EnergyDrink::setProjectile(){
  this-> currentProjectile = make_shared<EnergyDrinkProjectile>(textLoader, eventManager);
}
