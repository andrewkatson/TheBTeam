#include "Towers/PeanutMMS.hpp"

PeanutMMS::PeanutMMS(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PMMT_PR"));
}

void PeanutMMS::upgrade(){}

void PeanutMMS::setProjectile(){

  this-> currentProjectile = make_shared<PeanutMMSProjectile>(textLoader, eventManager);
}
