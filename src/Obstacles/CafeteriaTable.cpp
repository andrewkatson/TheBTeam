#include "Obstacles/CafeteriaTable.hpp"

CafeteriaTable::CafeteriaTable(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Obstacle(eventManager, textLoader){
  this -> towerTypeID = textLoader -> getTypeID(string("IDS_CTO"));
  this -> price = textLoader -> getInteger(string("IDS_CT_PR"));
  this -> textures = textureLoader -> getTexture(towerTypeID);
}
