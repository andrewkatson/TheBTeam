#include "Towers/Soda.hpp"

Soda::Soda(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_SOT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SOT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SOT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SOT_PR"));
  this -> textureLoader = textureLoader;
  this -> setProjectile();
}

void Soda::upgrade(){}

void Soda::setProjectile(){
  this-> currentProjectile = make_shared<SodaProjectile>(textLoader, eventManager, textureLoader);
}
