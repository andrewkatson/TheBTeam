#include "Projectiles/PepperoniPizzaProjectile.hpp"
PepperoniPizzaProjectile::PepperoniPizzaProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_PP_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_PP_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_PP_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_PP_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_PP_AP"));;
  this -> areaOfEffect = textLoader->getInteger(string("IDS_PP_AR"));;
  this -> actorTypeID = textLoader->getTypeID(string("IDS_PPP"));
  this -> textures = textureLoader -> getTexture(actorTypeID);
}
