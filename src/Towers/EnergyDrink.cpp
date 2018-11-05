#include "../include/Towers/EnergyDrink.hpp"

EnergyDrink::EnergyDrink(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_EDT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_EDT_RA"));
  this -> price = textLoader->getInteger(string("IDS_EDT_PR"));
}

void EnergyDrink::upgrade(){}

void EnergyDrink::setProjectile(){
  //constants for the EnergyDrink
  //health
  int energyDrinkHP = textLoader->getInteger(string("IDS_ED_HP"));
  //damage
  int energyDrinkDM = textLoader->getInteger(string("IDS_ED_DM"));
  //armor
  int energyDrinkAM = textLoader->getInteger(string("IDS_ED_AM"));
  //speed
  int energyDrinkSP = textLoader->getInteger(string("IDS_ED_SP"));
  //armor penetration
  int energyDrinkAP = textLoader->getInteger(string("IDS_ED_AP"));
  //area of effect
  int energyDrinkAR = textLoader->getInteger(string("IDS_ED_AR"));

  this-> currentProjectile = make_shared<EnergyDrinkProjectile>(
    energyDrinkHP, energyDrinkDM, energyDrinkAM, energyDrinkSP, energyDrinkAP, energyDrinkAR);
}
