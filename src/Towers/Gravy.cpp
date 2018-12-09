#include "Towers/Gravy.hpp"

int Gravy::priceMult = 1;

Gravy::Gravy(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> typeID = textLoader->getTypeID(string("IDS_GT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_GT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_GT_RA"));
  this -> price = textLoader->getInteger(string("IDS_GT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 3;
  this -> setProjectile();
  this -> initSprite();
}

void Gravy::upgrade(){}

void Gravy::setProjectile(){
  this-> currentProjectile = make_shared<GravyProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> Gravy::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<GravyProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
