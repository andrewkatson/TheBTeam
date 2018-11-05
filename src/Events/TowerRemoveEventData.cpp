#include "../include/Events/TowerRemoveEventData.hpp"

/*
 * container for the data held by a tower remove event
 * @author Andrew Katson
 */

 TowerRemoveEventData::TowerRemoveEventData(int towerPosID, float timeStamp){
   this -> timeStamp = timeStamp;
   this -> towerPosID = towerPosID;
 }
