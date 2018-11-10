#include "Towers/Gravy.hpp"

Gravy::Gravy(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_GT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_GT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_GT_RA"));
  this -> price = textLoader->getInteger(string("IDS_GT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setProjectile();
  this -> initSprite();
}

void Gravy::upgrade(){}

void Gravy::setProjectile(){
  this-> currentProjectile = make_shared<GravyProjectile>(textLoader, eventManager, textureLoader);
}
