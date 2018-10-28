#include "../include/Towers/MeatLovers.hpp"
MeatLovers::MeatLovers(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader -> getConstant(string("IDS_MLT_ROF"));
  this -> radius = textLoader -> getConstant(string("IDS_MLT_RA"));
  this -> price = textLoader -> getConstant(string("IDS_MLT_PR"));
}

void MeatLovers::upgrade(){}

void MeatLovers::setProjectile(){
  //constants for the MeatLovers
  //health
  int meatLoversHP = textLoader -> getConstant(string("IDS_ML_HP"));
  //damage
  int meatLoversDM = textLoader -> getConstant(string("IDS_ML_DM"));
  //armor
  int meatLoversAM = textLoader -> getConstant(string("IDS_ML_AM"));
  //speed
  int meatLoversSP = textLoader -> getConstant(string("IDS_ML_SP"));
  //armor penetration
  int meatLoversAP = textLoader -> getConstant(string("IDS_ML_AP"));
  //area of effect
  int meatLoversAR = textLoader -> getConstant(string("IDS_ML_AR"));

  this-> currentProjectile = make_shared<MeatLoversProjectile>(MeatLoversProjectile(
    meatLoversHP, meatLoversDM, meatLoversAM, meatLoversSP, meatLoversAP, meatLoversAR));
}
