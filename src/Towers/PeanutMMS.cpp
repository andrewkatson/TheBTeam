#include "../include/Towers/PeanutMMS.hpp"

PeanutMMS::PeanutMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void PeanutMMS::upgrade(){}
