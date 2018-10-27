#include "../include/Towers/PeanutButterMMS.hpp"
PeanutButterMMS::PeanutButterMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void PeanutButterMMS::upgrade(){}
