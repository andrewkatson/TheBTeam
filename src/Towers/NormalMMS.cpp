#include "../include/Towers/NormalMMS.hpp"

NormalMMS::NormalMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader -> getConstant(string("IDS_NMMT_ROF"));
  this -> radius = textLoader -> getConstant(string("IDS_NMMT_RA"));
  this -> price = textLoader -> getConstant(string("IDS_NMMT_PR"));
}

void NormalMMS::upgrade(){}

void NormalMMS::setProjectile(){
  //constants for the NormalMMS
  //health
  int normalMMSHP = textLoader -> getConstant(string("IDS_NMM_HP"));
  //damage
  int normalMMSDM = textLoader -> getConstant(string("IDS_NMM_DM"));
  //armor
  int normalMMSAM = textLoader -> getConstant(string("IDS_NMM_AM"));
  //speed
  int normalMMSSP = textLoader -> getConstant(string("IDS_NMM_SP"));
  //armor penetration
  int normalMMSAP = textLoader -> getConstant(string("IDS_NMM_AP"));
  //area of effect
  int normalMMSAR = textLoader -> getConstant(string("IDS_NMM_AR"));

  this-> currentProjectile = make_shared<NormalMMSProjectile>(
    normalMMSHP, normalMMSDM, normalMMSAM, normalMMSSP, normalMMSAP, normalMMSAR);
}
