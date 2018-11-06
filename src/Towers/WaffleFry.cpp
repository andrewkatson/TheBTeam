#include "../include/Towers/WaffleFry.hpp"

WaffleFry::WaffleFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits, shared_ptr<EventManager> eventManager) : MeleeTower( eventManager, textLoader){
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
  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<WaffleFryUnit>(textLoader, eventManager);
    currentUnits.push_back(unitToAdd);
  }
}
