#include "../include/Obstacles/TrashCan.hpp"
TrashCan::TrashCan(shared_ptr<TextLoader> textLoader, string towerTypeID) : Obstacle(){
  this -> towerTypeID = towerTypeID;
  this -> textLoader = textLoader;
  this -> price = textLoader -> getConstant(string("IDS_TC_PR"));
}
