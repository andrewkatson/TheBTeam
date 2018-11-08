#include "Towers/NormalMMS.hpp"

NormalMMS::NormalMMS(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_NMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_NMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_NMMT_PR"));
}

void NormalMMS::upgrade(){}

void NormalMMS::setProjectile(){
  this-> currentProjectile = make_shared<NormalMMSProjectile>(textLoader, eventManager);
}
