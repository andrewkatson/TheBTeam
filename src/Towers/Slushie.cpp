#include "Towers/Slushie.hpp"

Slushie::Slushie(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : RangeTower(eventManager, textLoader){
  this -> typeID = textLoader->getTypeID(string("IDS_SLT"));
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SLT_PR"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 3;
  this-> setProjectile();
  this -> initSprite();
}

void Slushie::upgrade(){}

void Slushie::setProjectile(){
  this-> currentProjectile = make_shared<SlushieProjectile>(textLoader, eventManager, textureLoader);
}

shared_ptr<ActorInterface> Slushie::createProjectile(){
  shared_ptr<ActorInterface> newProjecitle = make_shared<SlushieProjectile>(textLoader, eventManager, textureLoader);
  return newProjecitle;
}
