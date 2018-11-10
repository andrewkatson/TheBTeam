#include "Towers/PeanutButterMMS.hpp"
PeanutButterMMS::PeanutButterMMS(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_PBMMT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PBMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PBMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PBMMT_PR"));
  this -> textureLoader = textureLoader;
  this -> setProjectile();
}

void PeanutButterMMS::upgrade(){}

void PeanutButterMMS::setProjectile(){
  this-> currentProjectile = make_shared<PeanutButterMMSProjectile>(textLoader, eventManager, textureLoader);
}
