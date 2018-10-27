#include "../include/Towers/MiniMMS.hpp"
MiniMMS::MiniMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
}

void MiniMMS::upgrade(){}

void MiniMMS::setProjectile(){
  //constants for the MiniMMS
  //health
  int miniMMSHP = textLoader -> getConstant(string("IDS_MMM_HP"));
  //damage
  int miniMMSDM = textLoader -> getConstant(string("IDS_MMM_DM"));
  //armor
  int miniMMSAM = textLoader -> getConstant(string("IDS_MMM_AM"));
  //speed
  int miniMMSSP = textLoader -> getConstant(string("IDS_MMM_SP"));
  //armor penetration
  int miniMMSAP = textLoader -> getConstant(string("IDS_MMM_AP"));
  //area of effect
  int miniMMSAR = textLoader -> getConstant(string("IDS_MMM_AR"));

  this-> currentProjectile = make_shared<MiniMMSProjectile>(MiniMMSProjectile(
    miniMMSHP, miniMMSDM, miniMMSAM, miniMMSSP, miniMMSAP, miniMMSAR));
  }
