#include "Units/SpicyFryUnit.hpp"
SpicyFryUnit::SpicyFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_SF_HP"));;
  this -> maxHitpoints=hitpoints;
  this->damage=textLoader->getInteger(string("IDS_SF_DM"));;
  this->armor=textLoader->getInteger(string("IDS_SF_AM"));;
  this->speed=textLoader->getInteger(string("IDS_SF_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_SF_AP"));;
  this->radius= textLoader->getInteger(string("IDS_SF_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_SF_LM"));;
  this->actorTypeID=textLoader->getTypeID(string("IDS_SFU"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
  this -> initSprite();
}
