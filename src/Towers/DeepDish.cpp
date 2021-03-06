#include "Towers/DeepDish.hpp"

int DeepDish::priceMult = 1;

DeepDish::DeepDish(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader) {
  this -> typeID = textLoader->getTypeID(string("IDS_DDT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_DDT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_DDT_RA"));
  this -> price = textLoader->getInteger(string("IDS_DDT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 3;
  this -> setProjectile();
  this -> initSprite();
}

void DeepDish::upgrade(){}

void DeepDish::setProjectile(){
  this-> currentProjectile = make_shared<DeepDishProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> DeepDish::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<DeepDishProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
