#include "Towers/Slushie.hpp"

Slushie::Slushie(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_SLT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SLT_PR"));
  this -> textureLoader = textureLoader;
  this-> setProjectile();
}

void Slushie::upgrade(){}

void Slushie::setProjectile(){
  this-> currentProjectile = make_shared<SlushieProjectile>(textLoader, eventManager, textureLoader);
}
