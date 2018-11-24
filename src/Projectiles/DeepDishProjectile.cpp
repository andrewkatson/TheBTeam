#include "Projectiles/DeepDishProjectile.hpp"

DeepDishProjectile::DeepDishProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_DD_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_DD_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_DD_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_DD_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_DD_AP"));;
  this -> radius = textLoader->getInteger(string("IDS_DD_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_DDP"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
  this -> initSprite();
}
