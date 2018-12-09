#include "Towers/WaffleFry.hpp"

int WaffleFry::priceMult = 1;

WaffleFry::WaffleFry(shared_ptr<TextLoader> textLoader, int maxMeleeUnits, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader, bool setUpUnits) : MeleeTower( eventManager, textLoader){
  this -> totalUnits = maxMeleeUnits;
  this -> textLoader = textLoader;
  this -> respawnSpeed = textLoader->getInteger(string("IDS_WFT_RS"));
  this -> radius = textLoader->getInteger(string("IDS_WFT_RA"));
  this -> price = textLoader->getInteger(string("IDS_WFT_PR"));
  this -> typeID = textLoader->getTypeID(string("IDS_WFT"));
  this -> textureLoader = textureLoader;
  this -> textures = textureLoader -> getTexture(typeID);
  this -> level = 3;
  this -> logUnitsForCollisions = setUpUnits;
  this -> initSprite();
  this -> setUpUnits();
}

void WaffleFry::upgrade(){}

/*
 * Initialize the vector of units that spawn from this tower
 */
void WaffleFry::setUpUnits(){
  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<WaffleFryUnit>(textLoader, eventManager, textureLoader);
    currentUnits.push_back(unitToAdd);
  }
  //call the super version to set the position of the units
  MeleeTower::setUpUnits();
}
