#include "../include/Towers/CrinkleFry.hpp"


CrinkleFry::CrinkleFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> textLoader = textLoader;
  this -> respawnSpeed = textLoader -> getConstant(string("IDS_CFT_RS"));
  this -> radius = textLoader -> getConstant(string("IDS_CFT_RA"));
  this -> price = textLoader -> getConstant(string("IDS_CFT_PR"));
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
  //attack radius
  int crinkleFryAR = textLoader -> getConstant(string("IDS_CF_AR"));
  //lunch money
  int crinkleFryLM = textLoader -> getConstant(string("IDS_CF_LM"));

  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<CrinkleFryUnit>(crinkleFryHP,
       crinkleFryDM, crinkleFryAM, crinkleFrySP, crinkleFryAP, crinkleFryAR, crinkleFryLM);
    currentUnits.push_back(unitToAdd);
  }
}
