#include "Towers/NormalMMS.hpp"

NormalMMS::NormalMMS(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_NMMT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_NMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_NMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_NMMT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setProjectile();
}

void NormalMMS::upgrade(){}

void NormalMMS::setProjectile(){
  this-> currentProjectile = make_shared<NormalMMSProjectile>(textLoader, eventManager, textureLoader);
}
