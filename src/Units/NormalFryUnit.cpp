#include "Units/NormalFryUnit.hpp"
NormalFryUnit::NormalFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_NF_HP"));;
  this -> maxHitpoints=hitpoints;
  this->damage=textLoader->getInteger(string("IDS_NF_DM"));;
  this->armor=textLoader->getInteger(string("IDS_NF_AM"));;
  this->speed=textLoader->getInteger(string("IDS_NF_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_NF_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_NF_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_NF_LM"));;
}
