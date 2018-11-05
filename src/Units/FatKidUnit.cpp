//
// Created by jeremy on 10/26/18.
//

#include "../include/Units/FatKidUnit.hpp"

FatKidUnit::FatKidUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_FK_HP"));;
  this->damage=textLoader->getInteger(string("IDS_FK_DM"));;
  this->armor=textLoader->getInteger(string("IDS_FK_AM"));;
  this->speed=textLoader->getInteger(string("IDS_FK_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_FK_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_FK_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_FK_LM"));;
}
