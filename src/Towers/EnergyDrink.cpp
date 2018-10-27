#include "../include/Towers/EnergyDrink.hpp"

EnergyDrink::EnergyDrink(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
}

void EnergyDrink::upgrade(){}

void EnergyDrink::setProjectile(){
  //constants for the EnergyDrink
  //health
  int energyDrinkHP = textLoader -> getConstant(string("IDS_ED_HP"));
  //damage
  int energyDrinkDM = textLoader -> getConstant(string("IDS_ED_DM"));
  //armor
  int energyDrinkAM = textLoader -> getConstant(string("IDS_ED_AM"));
  //speed
  int energyDrinkSP = textLoader -> getConstant(string("IDS_ED_SP"));
  //armor penetration
  int energyDrinkAP = textLoader -> getConstant(string("IDS_ED_AP"));
  //area of effect
  int energyDrinkAR = textLoader -> getConstant(string("IDS_ED_AR"));

  this-> currentProjectile = make_shared<EnergyDrinkProjectile>(EnergyDrinkProjectile(
    energyDrinkHP, energyDrinkDM, energyDrinkAM, energyDrinkSP, energyDrinkAP, energyDrinkAR));
}
