#include "Projectiles/SlushieProjectile.hpp"

SlushieProjectile::SlushieProjectile(shared_ptr<TextLoader> textLoader,  shared_ptr<EventManager> eventManager) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_SL_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_SL_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_SL_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_SL_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_SL_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_SL_AR"));;
}
