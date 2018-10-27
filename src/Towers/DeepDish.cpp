#include "../include/Towers/DeepDish.hpp"

DeepDish::DeepDish(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
}

void DeepDish::upgrade(){}

void DeepDish::setProjectile(){
  //constants for the DeepDish
  //health
  int deepDishHP = textLoader -> getConstant(string("IDS_DD_HP"));
  //damage
  int deepDishDM = textLoader -> getConstant(string("IDS_DD_DM"));
  //armor
  int deepDishAM = textLoader -> getConstant(string("IDS_DD_AM"));
  //speed
  int deepDishSP = textLoader -> getConstant(string("IDS_DD_SP"));
  //armor penetration
  int deepDishAP = textLoader -> getConstant(string("IDS_DD_AP"));
  //area of effect
  int deepDishAR = textLoader -> getConstant(string("IDS_DD_AR"));

  this-> currentProjectile = make_shared<DeepDishProjectile>(DeepDishProjectile(
    deepDishHP, deepDishDM, deepDishAM, deepDishSP, deepDishAP, deepDishAR));
}
