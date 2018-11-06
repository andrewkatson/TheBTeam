#include "../include/Projectiles/DeepDishProjectile.hpp"

DeepDishProjectile::DeepDishProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_DD_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_DD_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_DD_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_DD_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_DD_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_DD_AR"));;
}
