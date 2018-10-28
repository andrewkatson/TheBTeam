#include "../include/Towers/Gravy.hpp"

Gravy::Gravy(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader -> getConstant(string("IDS_GT_ROF"));
  this -> radius = textLoader -> getConstant(string("IDS_GT_RA"));
  this -> price = textLoader -> getConstant(string("IDS_GT_PR"));
}

void Gravy::upgrade(){}

void Gravy::setProjectile(){
  //constants for the Gravy
  //health
  int gravyHP = textLoader -> getConstant(string("IDS_G_HP"));
  //damage
  int gravyDM = textLoader -> getConstant(string("IDS_G_DM"));
  //armor
  int gravyAM = textLoader -> getConstant(string("IDS_G_AM"));
  //speed
  int gravySP = textLoader -> getConstant(string("IDS_G_SP"));
  //armor penetration
  int gravyAP = textLoader -> getConstant(string("IDS_G_AP"));
  //area of effect
  int gravyAR = textLoader -> getConstant(string("IDS_G_AR"));

  this-> currentProjectile = make_shared<GravyProjectile>(GravyProjectile(
    gravyHP, gravyDM, gravyAM, gravySP, gravyAP, gravyAR));
}
