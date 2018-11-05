#include "../include/Projectiles/MiniMMSProjectile.hpp"

MiniMMSProjectile::MiniMMSProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_MMM_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_MMM_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_MMM_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_MMM_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_MMM_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_MMM_AR"));;
}
