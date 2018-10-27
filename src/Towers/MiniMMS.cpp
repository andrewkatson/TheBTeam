#include "../include/Towers/MiniMMS.hpp"
MiniMMS::MiniMMS(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
}

void MiniMMS::upgrade(){}
