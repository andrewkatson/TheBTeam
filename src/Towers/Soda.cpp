#include "Towers/Soda.hpp"

int Soda::priceMult = 1;

Soda::Soda(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> typeID = textLoader->getTypeID(string("IDS_SOT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SOT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SOT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SOT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 1;
  this -> setProjectile();
  this -> initSprite();
}

void Soda::upgrade(){}

void Soda::setProjectile(){
  this-> currentProjectile = make_shared<SodaProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> Soda::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<SodaProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
