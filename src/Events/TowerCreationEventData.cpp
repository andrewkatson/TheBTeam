#include "Events/TowerCreationEventData.hpp"
/*
 * container for the data held by a tower creation event
 * @author Andrew Katson
 */

 TowerCreationEventData::TowerCreationEventData(int towerPosID, string towerTypeID, float timeStamp){
   this -> timeStamp = timeStamp;
   this -> towerPosID = towerPosID;
   this -> towerTypeID = towerTypeID;
 }
