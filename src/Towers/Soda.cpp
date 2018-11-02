#include "../include/Towers/Soda.hpp"

Soda::Soda(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SOT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SOT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SOT_PR"));
}

void Soda::upgrade(){}

void Soda::setProjectile(){
  //constants for the Soda
  //health
  int sodaHP = textLoader->getInteger(string("IDS_SO_HP"));
  //damage
  int sodaDM = textLoader->getInteger(string("IDS_SO_DM"));
  //armor
  int sodaAM = textLoader->getInteger(string("IDS_SO_AM"));
  //speed
  int sodaSP = textLoader->getInteger(string("IDS_SO_SP"));
  //armor penetration
  int sodaAP = textLoader->getInteger(string("IDS_SO_AP"));
  //area of effect
  int sodaAR = textLoader->getInteger(string("IDS_SO_AR"));

  this-> currentProjectile = make_shared<SodaProjectile>(
    sodaHP, sodaDM, sodaAM, sodaSP, sodaAP, sodaAR);
}
