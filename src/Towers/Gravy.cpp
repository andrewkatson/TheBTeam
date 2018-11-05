#include "../include/Towers/Gravy.hpp"

Gravy::Gravy(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_GT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_GT_RA"));
  this -> price = textLoader->getInteger(string("IDS_GT_PR"));
}

void Gravy::upgrade(){}

void Gravy::setProjectile(){
  this-> currentProjectile = make_shared<GravyProjectile>(textLoader, eventManager);
}
