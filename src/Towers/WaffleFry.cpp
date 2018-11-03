#include "../include/Towers/WaffleFry.hpp"

WaffleFry::WaffleFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> textLoader = textLoader;
  this -> respawnSpeed = textLoader->getInteger(string("IDS_WFT_RS"));
  this -> radius = textLoader->getInteger(string("IDS_WFT_RA"));
  this -> price = textLoader->getInteger(string("IDS_WFT_PR"));
  this -> towerTypeID = towerTypeID;
  this -> setUpUnits();
}

void WaffleFry::upgrade(){}

/*
 * Initialize the vector of units that spawn from this tower
 */
void WaffleFry::setUpUnits(){
  //constants for the Waffle Fry
  //health
  int waffleFryHP = textLoader->getInteger(string("IDS_WF_HP"));
  //damage
  int waffleFryDM = textLoader->getInteger(string("IDS_WF_DM"));
  //armor
  int waffleFryAM = textLoader->getInteger(string("IDS_WF_AM"));
  //speed
  int waffleFrySP = textLoader->getInteger(string("IDS_WF_SP"));
  //armor penetration
  int waffleFryAP = textLoader->getInteger(string("IDS_WF_AP"));
  //attack radius
  int waffleFryAR = textLoader->getInteger(string("IDS_WF_AR"));
  //lunch money
  int waffleFryLM = textLoader->getInteger(string("IDS_WF_LM"));

  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<WaffleFryUnit>(
      waffleFryHP, waffleFryDM, waffleFryAM, waffleFrySP, waffleFryAP, waffleFryAR, waffleFryLM);
    currentUnits.push_back(unitToAdd);
  }
}
