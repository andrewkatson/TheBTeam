#include "Units/CrinkleFryUnit.hpp"
CrinkleFryUnit::CrinkleFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_CF_HP"));;
  this -> maxHitpoints= hitpoints;
  this->damage=textLoader->getInteger(string("IDS_CF_DM"));;
  this->armor=textLoader->getInteger(string("IDS_CF_AM"));;
  this->speed=textLoader->getInteger(string("IDS_CF_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_CF_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_CF_AR"));;;
  this->lunchMoney= textLoader->getInteger(string("IDS_CF_LM"));;
  this->actorTypeID=textLoader->getTypeID(string("IDS_CFU"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
}
