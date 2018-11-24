#include "Projectiles/PeanutMMSProjectile.hpp"

PeanutMMSProjectile::PeanutMMSProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_PMM_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_PMM_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_PMM_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_PMM_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_PMM_AP"));;
  this -> radius = textLoader->getInteger(string("IDS_PMM_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_PMMP"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
  this -> initSprite();
}
