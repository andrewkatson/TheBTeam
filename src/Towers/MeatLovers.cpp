#include "../include/Towers/MeatLovers.hpp"
MeatLovers::MeatLovers(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_MLT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_MLT_RA"));
  this -> price = textLoader->getInteger(string("IDS_MLT_PR"));
}

void MeatLovers::upgrade(){}

void MeatLovers::setProjectile(){
  //constants for the MeatLovers
  //health
  int meatLoversHP = textLoader->getInteger(string("IDS_ML_HP"));
  //damage
  int meatLoversDM = textLoader->getInteger(string("IDS_ML_DM"));
  //armor
  int meatLoversAM = textLoader->getInteger(string("IDS_ML_AM"));
  //speed
  int meatLoversSP = textLoader->getInteger(string("IDS_ML_SP"));
  //armor penetration
  int meatLoversAP = textLoader->getInteger(string("IDS_ML_AP"));
  //area of effect
  int meatLoversAR = textLoader->getInteger(string("IDS_ML_AR"));

  this-> currentProjectile = make_shared<MeatLoversProjectile>(
    meatLoversHP, meatLoversDM, meatLoversAM, meatLoversSP, meatLoversAP, meatLoversAR);
}
