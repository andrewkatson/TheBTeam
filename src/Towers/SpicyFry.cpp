#include "Towers/SpicyFry.hpp"
SpicyFry::SpicyFry(shared_ptr<TextLoader> textLoader, int maxMeleeUnits, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : MeleeTower(eventManager, textLoader){
  this -> totalUnits = maxMeleeUnits;
  this -> textLoader = textLoader;
  this -> respawnSpeed = textLoader->getInteger(string("IDS_SFT_RS"));
  this -> radius = textLoader->getInteger(string("IDS_SFT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SFT_PR"));
  this -> towerTypeID = textLoader->getTypeID(string("IDS_SFT"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(towerTypeID);
  this -> setUpUnits();
  this -> initSprite();
}

void SpicyFry::upgrade(){}

/*
 * Initialize the vector of units that spawn from this tower
 */
void SpicyFry::setUpUnits(){
  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<SpicyFryUnit>(textLoader, eventManager, textureLoader);
    currentUnits.push_back(unitToAdd);
  }
  //call the super version to set the position of the units
  MeleeTower::setUpUnits();
}
