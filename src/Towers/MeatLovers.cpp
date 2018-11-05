#include "../include/Towers/MeatLovers.hpp"
MeatLovers::MeatLovers(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_MLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_MLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_MLT_PR"));
}

void MeatLovers::upgrade(){}

void MeatLovers::setProjectile(){
  this-> currentProjectile = make_shared<MeatLoversProjectile>(textLoader, eventManager);
}
