#include "../include/Towers/PepperoniPizza.hpp"
PepperoniPizza::PepperoniPizza(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_PPT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_PPT_RA"));
  this -> price = textLoader->getInteger(string("IDS_PPT_PR"));
}

void PepperoniPizza::upgrade(){}

void PepperoniPizza::setProjectile(){
  //constants for the PepperoniPizza
  //health
  int pepperoniPizzaHP = textLoader->getInteger(string("IDS_PP_HP"));
  //damage
  int pepperoniPizzaDM = textLoader->getInteger(string("IDS_PP_DM"));
  //armor
  int pepperoniPizzaAM = textLoader->getInteger(string("IDS_PP_AM"));
  //speed
  int pepperoniPizzaSP = textLoader->getInteger(string("IDS_PP_SP"));
  //armor penetration
  int pepperoniPizzaAP = textLoader->getInteger(string("IDS_PP_AP"));
  //area of effect
  int pepperoniPizzaAR = textLoader->getInteger(string("IDS_PP_AR"));

  this-> currentProjectile = make_shared<PepperoniPizzaProjectile>(
    pepperoniPizzaHP, pepperoniPizzaDM, pepperoniPizzaAM, pepperoniPizzaSP, pepperoniPizzaAP, pepperoniPizzaAR);
}
