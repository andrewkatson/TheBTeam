#include "Projectiles/CheesePizzaProjectile.hpp"


CheesePizzaProjectile::CheesePizzaProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_CP_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_CP_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_CP_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_CP_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_CP_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_CP_AR"));;
}
