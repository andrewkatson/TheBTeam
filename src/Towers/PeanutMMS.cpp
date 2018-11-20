#include "Towers/PeanutMMS.hpp"

PeanutMMS::PeanutMMS(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_PMMT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PMMT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setProjectile();
  this -> initSprite();
}

void PeanutMMS::upgrade(){}

void PeanutMMS::setProjectile(){

  this-> currentProjectile = make_shared<PeanutMMSProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> PeanutMMS::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<PeanutMMSProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
