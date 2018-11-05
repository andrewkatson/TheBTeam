#include "../include/Towers/CheesePizza.hpp"

CheesePizza::CheesePizza(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_CPT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_CPT_RA"));
  this -> price = textLoader->getInteger(string("IDS_CPT_PR"));
}

void CheesePizza::upgrade(){}

void CheesePizza::setProjectile(){
  //constants for the CheesePizza
  //health
  int cheesePizzaHP = textLoader->getInteger(string("IDS_CP_HP"));
  //damage
  int cheesePizzaDM = textLoader->getInteger(string("IDS_CP_DM"));
  //armor
  int cheesePizzaAM = textLoader->getInteger(string("IDS_CP_AM"));
  //speed
  int cheesePizzaSP = textLoader->getInteger(string("IDS_CP_SP"));
  //armor penetration
  int cheesePizzaAP = textLoader->getInteger(string("IDS_CP_AP"));
  //area of effect
  int cheesePizzaAR = textLoader->getInteger(string("IDS_CP_AR"));

  this-> currentProjectile = make_shared<CheesePizzaProjectile>(cheesePizzaHP, cheesePizzaDM, cheesePizzaAM, cheesePizzaSP, cheesePizzaAP, cheesePizzaAR);
}
