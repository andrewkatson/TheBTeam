#include "../include/Obstacles/CafeteriaTable.hpp"

CafeteriaTable::CafeteriaTable(shared_ptr<TextLoader> textLoader, string towerTypeID) : Obstacle(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> price = textLoader -> getConstant(string("IDS_CT_PR"));
}
