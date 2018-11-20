#include "Towers/MiniMMS.hpp"
MiniMMS::MiniMMS(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = textLoader->getTypeID(string("IDS_MMMT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_MMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_MMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_MMMT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setProjectile();
  this -> initSprite();
}

void MiniMMS::upgrade(){}

void MiniMMS::setProjectile(){
  this-> currentProjectile = make_shared<MiniMMSProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> MiniMMS::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<MiniMMSProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
