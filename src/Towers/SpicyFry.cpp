#include "../include/Towers/SpicyFry.hpp"
SpicyFry::SpicyFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> textLoader = textLoader;
  this -> respawnSpeed = textLoader->getInteger(string("IDS_SFT_RS"));
  this -> radius = textLoader->getInteger(string("IDS_SFT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SFT_PR"));
  this -> towerTypeID = towerTypeID;
  this -> setUpUnits();
}

void SpicyFry::upgrade(){}

/*
 * Initialize the vector of units that spawn from this tower
 */
void SpicyFry::setUpUnits(){
  //constants for the Spicy Fry
  //health
  int spicyFryHP = textLoader->getInteger(string("IDS_SF_HP"));
  //damage
  int spicyFryDM = textLoader->getInteger(string("IDS_SF_DM"));
  //armor
  int spicyFryAM = textLoader->getInteger(string("IDS_SF_AM"));
  //speed
  int spicyFrySP = textLoader->getInteger(string("IDS_SF_SP"));
  //armor penetration
  int spicyFryAP = textLoader->getInteger(string("IDS_SF_AP"));
  //attack radius
  int spicyFryAR = textLoader->getInteger(string("IDS_SF_AR"));
  //lunch money
  int spicyFryLM = textLoader->getInteger(string("IDS_SF_LM"));


  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<SpicyFryUnit>(
      spicyFryHP, spicyFryDM, spicyFryAM, spicyFrySP, spicyFryAP, spicyFryAR, spicyFryLM);
    currentUnits.push_back(unitToAdd);
  }
}
