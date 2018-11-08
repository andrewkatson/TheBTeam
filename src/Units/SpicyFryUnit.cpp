#include "Units/SpicyFryUnit.hpp"
SpicyFryUnit::SpicyFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_SF_HP"));;
  this -> maxHitpoints=hitpoints;
  this->damage=textLoader->getInteger(string("IDS_SF_DM"));;
  this->armor=textLoader->getInteger(string("IDS_SF_AM"));;
  this->speed=textLoader->getInteger(string("IDS_SF_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_SF_AP"));;
  this->attackRadius= textLoader->getInteger(string("IDS_SF_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_SF_LM"));;
}
