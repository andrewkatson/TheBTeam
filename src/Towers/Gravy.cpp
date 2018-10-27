#include "../include/Towers/Gravy.hpp"

Gravy::Gravy(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void Gravy::upgrade(){}
