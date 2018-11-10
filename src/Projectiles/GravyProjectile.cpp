#include "Projectiles/GravyProjectile.hpp"
GravyProjectile::GravyProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_G_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_G_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_G_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_G_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_G_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_G_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_GP"));
}
