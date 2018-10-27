#include "../include/Towers/Slushie.hpp"

Slushie::Slushie(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
}

void Slushie::upgrade(){}

void Slushie::setProjectile(){
  //constants for the Slushie
  //health
  int slushieHP = textLoader -> getConstant(string("IDS_SL_HP"));
  //damage
  int slushieDM = textLoader -> getConstant(string("IDS_SL_DM"));
  //armor
  int slushieAM = textLoader -> getConstant(string("IDS_SL_AM"));
  //speed
  int slushieSP = textLoader -> getConstant(string("IDS_SL_SP"));
  //armor penetration
  int slushieAP = textLoader -> getConstant(string("IDS_SL_AP"));
  //area of effect
  int slushieAR = textLoader -> getConstant(string("IDS_SL_AR"));

  this-> currentProjectile = make_shared<SlushieProjectile>(SlushieProjectile(
    slushieHP, slushieDM, slushieAM, slushieSP, slushieAP, slushieAR));
}
