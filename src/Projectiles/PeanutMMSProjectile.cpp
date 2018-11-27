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
  //set the initial sprite texture
  this ->current_sprite = 0;
  //load in the initial texture for sizing
  initSprite();

  //set the sprite for the actor to have a position that is equivalent to its center
  setToCenter();
}
