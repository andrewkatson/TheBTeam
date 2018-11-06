#include "../include/Towers/Slushie.hpp"

Slushie::Slushie(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SLT_PR"));
}

void Slushie::upgrade(){}

void Slushie::setProjectile(){
  this-> currentProjectile = make_shared<SlushieProjectile>(textLoader, eventManager);
}
