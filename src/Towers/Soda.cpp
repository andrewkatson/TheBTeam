#include "../include/Towers/Soda.hpp"

Soda::Soda(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void Soda::upgrade(){}
