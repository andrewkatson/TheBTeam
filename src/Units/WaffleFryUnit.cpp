#include "../include/Units/WaffleFryUnit.hpp"

WaffleFryUnit::WaffleFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_WF_HP"));;
  this -> maxHitpoints=hitpoints;
  this->damage=textLoader->getInteger(string("IDS_WF_DM"));;
  this->armor=textLoader->getInteger(string("IDS_WF_AM"));;
  this->speed=textLoader->getInteger(string("IDS_WF_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_WF_AP"));;
  this->attackRadius=textLoader->getInteger(string("IDS_WF_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_WF_LM"));;
}
