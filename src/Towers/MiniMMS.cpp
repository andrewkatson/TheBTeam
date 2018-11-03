#include "../include/Towers/MiniMMS.hpp"
MiniMMS::MiniMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_MMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_MMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_MMMT_PR"));
}

void MiniMMS::upgrade(){}

void MiniMMS::setProjectile(){
  //constants for the MiniMMS
  //health
  int miniMMSHP = textLoader->getInteger(string("IDS_MMM_HP"));
  //damage
  int miniMMSDM = textLoader->getInteger(string("IDS_MMM_DM"));
  //armor
  int miniMMSAM = textLoader->getInteger(string("IDS_MMM_AM"));
  //speed
  int miniMMSSP = textLoader->getInteger(string("IDS_MMM_SP"));
  //armor penetration
  int miniMMSAP = textLoader->getInteger(string("IDS_MMM_AP"));
  //area of effect
  int miniMMSAR = textLoader->getInteger(string("IDS_MMM_AR"));

  this-> currentProjectile = make_shared<MiniMMSProjectile>(
    miniMMSHP, miniMMSDM, miniMMSAM, miniMMSSP, miniMMSAP, miniMMSAR);
  }
