#include "Projectiles/PeanutMMSProjectile.hpp"

PeanutMMSProjectile::PeanutMMSProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_PMM_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_PMM_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_PMM_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_PMM_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_PMM_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_PMM_AR"));;
}
