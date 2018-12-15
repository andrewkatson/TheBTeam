#include "Towers/EnergyDrink.hpp"

int EnergyDrink::priceMult=1;

EnergyDrink::EnergyDrink(shared_ptr<TextLoader> textLoader,  shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader) {
  this -> typeID = textLoader->getTypeID(string("IDS_EDT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_EDT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_EDT_RA"));
  this -> price = textLoader->getInteger(string("IDS_EDT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 2;
  this -> setProjectile();
  this -> initSprite();
}

void EnergyDrink::upgrade(){}

void EnergyDrink::setProjectile(){
  this-> currentProjectile = make_shared<EnergyDrinkProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> EnergyDrink::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<EnergyDrinkProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
