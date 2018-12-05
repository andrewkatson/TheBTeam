#include "Units/WaffleFryUnit.hpp"

WaffleFryUnit::WaffleFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeUnit(eventManager, textLoader){
  this->hitpoints=textLoader->getInteger(string("IDS_WF_HP"));;
  this -> maxHitpoints=hitpoints;
  this->damage=textLoader->getInteger(string("IDS_WF_DM"));;
  this->armor=textLoader->getInteger(string("IDS_WF_AM"));;
  this->speed=textLoader->getInteger(string("IDS_WF_SP"));;
  this->armorPenetration=textLoader->getInteger(string("IDS_WF_AP"));;
  this->radius=textLoader->getInteger(string("IDS_WF_AR"));;
  this->lunchMoney=textLoader->getInteger(string("IDS_WF_LM"));;
  this->typeID=textLoader->getTypeID(string("IDS_WFU"));
  this->attackRate=textLoader->getInteger(string("IDS_WF_Attack_Rate"));
  this -> textures = textureLoader -> getTexture(typeID);
  this -> isAlly = true;
  //set the initial sprite texture
  this ->current_sprite = 0;
  //load in the initial texture for sizing
  initSprite();
}
