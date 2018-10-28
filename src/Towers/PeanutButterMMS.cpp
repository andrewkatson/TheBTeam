#include "../include/Towers/PeanutButterMMS.hpp"
PeanutButterMMS::PeanutButterMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader -> getConstant(string("IDS_PBMMT_ROF"));
  this -> radius = textLoader -> getConstant(string("IDS_PBMMT_RA"));
  this -> price = textLoader -> getConstant(string("IDS_PBMMT_PR"));
}

void PeanutButterMMS::upgrade(){}

void PeanutButterMMS::setProjectile(){
  //constants for the PeanutButterMMS
  //health
  int pbMMSHP = textLoader -> getConstant(string("IDS_PBMM_HP"));
  //damage
  int pbMMSDM = textLoader -> getConstant(string("IDS_PBMM_DM"));
  //armor
  int pbMMSAM = textLoader -> getConstant(string("IDS_PBMM_AM"));
  //speed
  int pbMMSSP = textLoader -> getConstant(string("IDS_PBMM_SP"));
  //armor penetration
  int pbMMSAP = textLoader -> getConstant(string("IDS_PBMM_AP"));
  //area of effect
  int pbMMSAR = textLoader -> getConstant(string("IDS_PBMM_AR"));

  this-> currentProjectile = make_shared<PeanutButterMMSProjectile>(PeanutButterMMSProjectile(
    pbMMSHP, pbMMSDM, pbMMSAM, pbMMSSP, pbMMSAP, pbMMSAR));
}
