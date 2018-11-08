#include "Towers/MiniMMS.hpp"
MiniMMS::MiniMMS(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_MMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_MMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_MMMT_PR"));
}

void MiniMMS::upgrade(){}

void MiniMMS::setProjectile(){


  this-> currentProjectile = make_shared<MiniMMSProjectile>(textLoader, eventManager);
  }
