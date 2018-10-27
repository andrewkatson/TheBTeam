#include "../include/Towers/PeanutMMS.hpp"

PeanutMMS::PeanutMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
}

void PeanutMMS::upgrade(){}

void PeanutMMS::setProjectile(){
  //constants for the PeanutMMS
  //health
  int peanutButterMMSHP = textLoader -> getConstant(string("IDS_PBMM_HP"));
  //damage
  int peanutButterMMSDM = textLoader -> getConstant(string("IDS_PBMM_DM"));
  //armor
  int peanutButterMMSAM = textLoader -> getConstant(string("IDS_PBMM_AM"));
  //speed
  int peanutButterMMSSP = textLoader -> getConstant(string("IDS_PBMM_SP"));
  //armor penetration
  int peanutButterMMSAP = textLoader -> getConstant(string("IDS_PBMM_AP"));
  //area of effect
  int peanutButterMMSAR = textLoader -> getConstant(string("IDS_PBMM_AR"));

  this-> currentProjectile = make_shared<PeanutMMSProjectile>(PeanutMMSProjectile(
    peanutButterMMSHP, peanutButterMMSDM, peanutButterMMSAM, peanutButterMMSSP, peanutButterMMSAP, peanutButterMMSAR));
}
