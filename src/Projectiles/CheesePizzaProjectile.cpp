#include "Projectiles/CheesePizzaProjectile.hpp"


CheesePizzaProjectile::CheesePizzaProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_CP_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_CP_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_CP_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_CP_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_CP_AP"));;
  this -> radius = textLoader->getInteger(string("IDS_CP_AR"));;
  this -> typeID = textLoader->getTypeID(string("IDS_CPP"));
  this -> textures = textureLoader -> getTexture(typeID);
  //set the initial sprite texture
  this ->current_sprite = 0;
  //load in the initial texture for sizing
  initSprite();

  //set the sprite for the actor to have a position that is equivalent to its center
  setToCenter();
}
