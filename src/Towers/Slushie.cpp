#include "../include/Towers/Slushie.hpp"

Slushie::Slushie(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_SLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_SLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_SLT_PR"));
}

void Slushie::upgrade(){}

void Slushie::setProjectile(){
  //constants for the Slushie
  //health
  int slushieHP = textLoader->getInteger(string("IDS_SL_HP"));
  //damage
  int slushieDM = textLoader->getInteger(string("IDS_SL_DM"));
  //armor
  int slushieAM = textLoader->getInteger(string("IDS_SL_AM"));
  //speed
  int slushieSP = textLoader->getInteger(string("IDS_SL_SP"));
  //armor penetration
  int slushieAP = textLoader->getInteger(string("IDS_SL_AP"));
  //area of effect
  int slushieAR = textLoader->getInteger(string("IDS_SL_AR"));

  this-> currentProjectile = make_shared<SlushieProjectile>(
    slushieHP, slushieDM, slushieAM, slushieSP, slushieAP, slushieAR);
}
