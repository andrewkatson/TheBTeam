#include "Towers/PeanutButterMMS.hpp"
PeanutButterMMS::PeanutButterMMS(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_PBMMT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PBMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PBMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PBMMT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> level = 3;
  this -> setProjectile();
  this -> initSprite();
}

void PeanutButterMMS::upgrade(){}

void PeanutButterMMS::setProjectile(){
  this-> currentProjectile = make_shared<PeanutButterMMSProjectile>(textLoader, eventManager, textureLoader);
}
shared_ptr<ActorInterface> PeanutButterMMS::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<PeanutButterMMSProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
