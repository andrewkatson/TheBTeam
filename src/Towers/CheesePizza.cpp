#include "Towers/CheesePizza.hpp"

CheesePizza::CheesePizza(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader) {
  this -> towerTypeID = textLoader->getTypeID(string("IDS_CPT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_CPT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_CPT_RA"));
  this -> price = textLoader->getInteger(string("IDS_CPT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setProjectile();
  this -> initSprite();
}

void CheesePizza::upgrade(){}

void CheesePizza::setProjectile(){
  this-> currentProjectile = make_shared<CheesePizzaProjectile>(textLoader, eventManager, textureLoader);
}
