#include "Projectiles/SodaProjectile.hpp"

SodaProjectile::SodaProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints =  textLoader->getInteger(string("IDS_SO_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_SO_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_SO_AM"));;
  this -> speed =  textLoader->getInteger(string("IDS_SO_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_SO_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_SO_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_SOP"));
}
