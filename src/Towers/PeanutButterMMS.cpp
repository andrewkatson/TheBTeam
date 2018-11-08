#include "Towers/PeanutButterMMS.hpp"
PeanutButterMMS::PeanutButterMMS(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PBMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PBMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PBMMT_PR"));
}

void PeanutButterMMS::upgrade(){}

void PeanutButterMMS::setProjectile(){
  this-> currentProjectile = make_shared<PeanutButterMMSProjectile>(textLoader, eventManager);
}
