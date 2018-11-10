#include "Projectiles/NormalMMSProjectile.hpp"
NormalMMSProjectile::NormalMMSProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_NMM_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_NMM_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_NMM_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_NMM_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_NMM_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_NMM_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_NMMP"));
}
