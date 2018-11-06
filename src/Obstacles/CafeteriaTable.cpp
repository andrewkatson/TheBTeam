#include "../include/Obstacles/CafeteriaTable.hpp"

CafeteriaTable::CafeteriaTable(shared_ptr<TextLoader> textLoader, string towerTypeID,shared_ptr<EventManager> eventManager) : Obstacle(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> price = textLoader -> getInteger(string("IDS_CT_PR"));
}
