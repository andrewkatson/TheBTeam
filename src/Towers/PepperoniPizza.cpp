#include "Towers/PepperoniPizza.hpp"
PepperoniPizza::PepperoniPizza(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> towerTypeID = textLoader->getTypeID(string("IDS_PPT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PPT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PPT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PPT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setProjectile();
  this -> initSprite();
}

void PepperoniPizza::upgrade(){}

void PepperoniPizza::setProjectile(){
  this-> currentProjectile = make_shared<PepperoniPizzaProjectile>(textLoader, eventManager, textureLoader);
}
