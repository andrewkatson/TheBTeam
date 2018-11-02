#include "../include/Towers/DeepDish.hpp"

DeepDish::DeepDish(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> rateOfFire = textLoader->getInteger(string("IDS_DDT_ROF"));
  this -> radius = textLoader->getInteger(string("IDS_DDT_RA"));
  this -> price = textLoader->getInteger(string("IDS_DDT_PR"));
}

void DeepDish::upgrade(){}

void DeepDish::setProjectile(){
  //constants for the DeepDish
  //health
  int deepDishHP = textLoader->getInteger(string("IDS_DD_HP"));
  //damage
  int deepDishDM = textLoader->getInteger(string("IDS_DD_DM"));
  //armor
  int deepDishAM = textLoader->getInteger(string("IDS_DD_AM"));
  //speed
  int deepDishSP = textLoader->getInteger(string("IDS_DD_SP"));
  //armor penetration
  int deepDishAP = textLoader->getInteger(string("IDS_DD_AP"));
  //area of effect
  int deepDishAR = textLoader->getInteger(string("IDS_DD_AR"));

  this-> currentProjectile = make_shared<DeepDishProjectile>(
    deepDishHP, deepDishDM, deepDishAM, deepDishSP, deepDishAP, deepDishAR);
}
