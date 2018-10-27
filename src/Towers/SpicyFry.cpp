#include "../include/Towers/SpicyFry.hpp"
SpicyFry::SpicyFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> respawnSpeed = textLoader -> getConstant(string("IDS_SFT_RS"));
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
  int spicyFryHP = textLoader -> getConstant(string("IDS_SF_HP"));
  //damage
  int spicyFryDM = textLoader -> getConstant(string("IDS_SF_DM"));
  //armor
  int spicyFryAM = textLoader -> getConstant(string("IDS_SF_AM"));
  //speed
  int spicyFrySP = textLoader -> getConstant(string("IDS_SF_SP"));
  //armor penetration
  int spicyFryAP = textLoader -> getConstant(string("IDS_SF_AP"));

  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<SpicyFryUnit>(SpicyFryUnit(spicyFryHP, spicyFryDM, spicyFryAM, spicyFrySP, spicyFryAP));
    currentUnits.push_back(unitToAdd);
  }
}
