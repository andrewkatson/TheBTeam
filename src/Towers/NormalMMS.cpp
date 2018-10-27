#include "../include/Towers/NormalMMS.hpp"

NormalMMS::NormalMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void NormalMMS::upgrade(){}
