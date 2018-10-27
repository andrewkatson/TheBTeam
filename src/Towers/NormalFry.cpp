#include "../include/Towers/NormalFry.hpp"



NormalFry::NormalFry(shared_ptr<TextLoader> textLoader, string towerTypeID, int maxMeleeUnits) : MeleeTower(){
  this -> totalUnits = maxMeleeUnits;
  this -> respawnSpeed = textLoader -> getConstant(string("IDS_NFT_RS"));
  this -> towerTypeID = towerTypeID;
  this -> setUpUnits();
}

void NormalFry::upgrade(){

}

/*
 * Initialize the vector of units that spawn from this tower
 */
void NormalFry::setUpUnits(){
  //constants for the Normaly Fry
  //health
  int normalFryHP = textLoader -> getConstant(string("IDS_NF_HP"));
  //damage
  int normalFryDM = textLoader -> getConstant(string("IDS_NF_DM"));
  //armor
  int normalFryAM = textLoader -> getConstant(string("IDS_NF_AM"));
  //speed
  int normalFrySP = textLoader -> getConstant(string("IDS_NF_SP"));
  //armor penetration
  int normalFryAP = textLoader -> getConstant(string("IDS_NF_AP"));

  //create the maximum number of possible units
  for(int i = 0; i < totalUnits; i++){
    shared_ptr<MeleeUnit> unitToAdd = make_shared<NormalFryUnit>(NormalFryUnit(normalFryHP, normalFryDM, normalFryAM, normalFrySP, normalFryAP));
    currentUnits.push_back(unitToAdd);
  }
}
