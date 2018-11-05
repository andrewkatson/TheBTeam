#include "../include/Towers/Soda.hpp"

Soda::Soda(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SOT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SOT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SOT_PR"));
}

void Soda::upgrade(){}

void Soda::setProjectile(){
  this-> currentProjectile = make_shared<SodaProjectile>(textLoader, eventManager);
}
