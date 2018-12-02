#include "Towers/MeatLovers.hpp"
MeatLovers::MeatLovers(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> typeID = textLoader->getTypeID(string("IDS_MLT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_MLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_MLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_MLT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 2;
  this -> setProjectile();
  this -> initSprite();
}

void MeatLovers::upgrade(){}

void MeatLovers::setProjectile(){
  this-> currentProjectile = make_shared<MeatLoversProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> MeatLovers::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<MeatLoversProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
