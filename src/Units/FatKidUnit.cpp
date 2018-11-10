//
// Created by jeremy on 10/26/18.
//

#include "Units/FatKidUnit.hpp"

FatKidUnit::FatKidUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_FK_HP"));;
  this->damage=textLoader->getInteger(string("IDS_FK_DM"));;
  this->armor=textLoader->getInteger(string("IDS_FK_AM"));;
  this->speed=textLoader->getInteger(string("IDS_FK_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_FK_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_FK_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_FK_LM"));;
  this->actorTypeID=textLoader->getTypeID(string("IDS_FKU"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
}
