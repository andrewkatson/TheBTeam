#include "../include/Towers/WaffleFry.hpp"

WaffleFry::WaffleFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> respawnSpeed = textLoader -> getConstant(string("IDS_WFT_RS"));
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
  int waffleFryHP = textLoader -> getConstant(string("IDS_WF_HP"));
  //damage
  int waffleFryDM = textLoader -> getConstant(string("IDS_WF_DM"));
  //armor
  int waffleFryAM = textLoader -> getConstant(string("IDS_WF_AM"));
  //speed
  int waffleFrySP = textLoader -> getConstant(string("IDS_WF_SP"));
  //armor penetration
  int waffleFryAP = textLoader -> getConstant(string("IDS_WF_AP"));

  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<WaffleFryUnit>(WaffleFryUnit(waffleFryHP, waffleFryDM, waffleFryAM, waffleFrySP, waffleFryAP));
    currentUnits.push_back(unitToAdd);
  }
}
