#include "Projectiles/EnergyDrinkProjectile.hpp"

EnergyDrinkProjectile::EnergyDrinkProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_ED_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_ED_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_ED_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_ED_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_ED_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_ED_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_EDP"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
  this -> initSprite();
}
