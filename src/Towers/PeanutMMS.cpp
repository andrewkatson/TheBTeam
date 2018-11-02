#include "../include/Towers/PeanutMMS.hpp"

PeanutMMS::PeanutMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PMMT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PMMT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PMMT_PR"));
}

void PeanutMMS::upgrade(){}

void PeanutMMS::setProjectile(){
  //constants for the PeanutMMS
  //health
  int peanutMMSHP = textLoader->getInteger(string("IDS_PMM_HP"));
  //damage
  int peanutMMSDM = textLoader->getInteger(string("IDS_PMM_DM"));
  //armor
  int peanutMMSAM = textLoader->getInteger(string("IDS_PMM_AM"));
  //speed
  int peanutMMSSP = textLoader->getInteger(string("IDS_PMM_SP"));
  //armor penetration
  int peanutMMSAP = textLoader->getInteger(string("IDS_PMM_AP"));
  //area of effect
  int peanutMMSAR = textLoader->getInteger(string("IDS_PMM_AR"));

  this-> currentProjectile = make_shared<PeanutMMSProjectile>(
    peanutMMSHP, peanutMMSDM, peanutMMSAM, peanutMMSSP, peanutMMSAP, peanutMMSAR);
}
