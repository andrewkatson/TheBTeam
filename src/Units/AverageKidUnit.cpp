//
// Created by jeremy on 10/26/18.
//

#include "Units/AverageKidUnit.hpp"

AverageKidUnit::AverageKidUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_AK_HP"));;
  this->damage=textLoader->getInteger(string("IDS_AK_DM"));;
  this->armor=textLoader->getInteger(string("IDS_AK_AM"));;
  this->speed=textLoader->getInteger(string("IDS_AK_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_AK_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_AK_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_AK_LM"));;
  this->actorTypeID=textLoader->getTypeID(string("IDS_AKU"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
}
