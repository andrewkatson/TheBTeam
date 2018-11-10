//
// Created by jeremy on 10/26/18.
//

#include "Units/SkinnyKidUnit.hpp"

SkinnyKidUnit::SkinnyKidUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_SK_HP"));;
  this->damage=textLoader->getInteger(string("IDS_SK_DM"));;
  this->armor=textLoader->getInteger(string("IDS_SK_AM"));;
  this->speed=textLoader->getInteger(string("IDS_SK_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_SK_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_SK_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_SK_LM"));;
  this->actorTypeID=textLoader->getTypeID(string("IDS_SKU"));
}
