#include "../include/Towers/MeatLovers.hpp"
MeatLovers::MeatLovers(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void MeatLovers::upgrade(){}
