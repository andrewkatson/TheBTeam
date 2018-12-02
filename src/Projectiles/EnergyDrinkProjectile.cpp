#include "Projectiles/EnergyDrinkProjectile.hpp"

EnergyDrinkProjectile::EnergyDrinkProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Projectile(eventManager, textLoader){
  this -> hitpoints = textLoader->getInteger(string("IDS_ED_HP"));;
  this -> damage = textLoader->getInteger(string("IDS_ED_DM"));;
  this -> armor = textLoader->getInteger(string("IDS_ED_AM"));;
  this -> speed = textLoader->getInteger(string("IDS_ED_SP"));;
  this -> armorPenetration = textLoader->getInteger(string("IDS_ED_AP"));;
  this -> radius = textLoader->getInteger(string("IDS_ED_AR"));;
  this -> typeID = textLoader->getTypeID(string("IDS_EDP"));
  this -> textures = textureLoader -> getTexture(typeID);
  //set the initial sprite texture
  this ->current_sprite = 0;
  //load in the initial texture for sizing
  initSprite();

  //set the sprite for the actor to have a position that is equivalent to its center
  setToCenter();
}
