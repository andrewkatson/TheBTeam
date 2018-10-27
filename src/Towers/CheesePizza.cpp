#include "../include/Towers/CheesePizza.hpp"

CheesePizza::CheesePizza(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
}

void CheesePizza::upgrade(){}

void CheesePizza::setProjectile(){
  //constants for the CheesePizza
  //health
  int cheesePizzaHP = textLoader -> getConstant(string("IDS_CP_HP"));
  //damage
  int cheesePizzaDM = textLoader -> getConstant(string("IDS_CP_DM"));
  //armor
  int cheesePizzaAM = textLoader -> getConstant(string("IDS_CP_AM"));
  //speed
  int cheesePizzaSP = textLoader -> getConstant(string("IDS_CP_SP"));
  //armor penetration
  int cheesePizzaAP = textLoader -> getConstant(string("IDS_CP_AP"));
  //area of effect
  int cheesePizzaAR = textLoader -> getConstant(string("IDS_CP_AR"));

  this-> currentProjectile = make_shared<CheesePizzaProjectile>(CheesePizzaProjectile(
    cheesePizzaHP, cheesePizzaDM, cheesePizzaAM, cheesePizzaSP, cheesePizzaAP, cheesePizzaAR));
}
