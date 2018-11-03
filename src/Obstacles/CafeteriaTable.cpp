#include "../include/Obstacles/CafeteriaTable.hpp"

CafeteriaTable::CafeteriaTable(shared_ptr<TextLoader> textLoader, string towerTypeID) : Obstacle(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> price = textLoader -> getInteger(string("IDS_CT_PR"));
}
