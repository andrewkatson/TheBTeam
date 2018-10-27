#include "../include/Towers/CrinkleFry.hpp"


CrinkleFry::CrinkleFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> respawnSpeed = textLoader -> getConstant(string("IDS_CFT_RS"));
  this -> towerTypeID = towerTypeID;
  this -> setUpUnits();
}

void CrinkleFry::upgrade(){}

/*
 * Initialize the vector of units that spawn from this tower
 */
void CrinkleFry::setUpUnits(){
  //constants for the Crinkle Fry
  //health
  int crinkleFryHP = textLoader -> getConstant(string("IDS_CF_HP"));
  //damage
  int crinkleFryDM = textLoader -> getConstant(string("IDS_CF_DM"));
  //armor
  int crinkleFryAM = textLoader -> getConstant(string("IDS_CF_AM"));
  //speed
  int crinkleFrySP = textLoader -> getConstant(string("IDS_CF_SP"));
  //armor penetration
  int crinkleFryAP = textLoader -> getConstant(string("IDS_CF_AP"));

  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<CrinkleFryUnit>(CrinkleFryUnit(crinkleFryHP, crinkleFryDM, crinkleFryAM, crinkleFrySP, crinkleFryAP));
    currentUnits.push_back(unitToAdd);
  }
}
