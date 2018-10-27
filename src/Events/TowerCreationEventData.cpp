#include "../include/Events/TowerCreationEventData.hpp"
/*
 * container for the data held by a tower creation event
 * @author Andrew Katson
 */

 TowerCreationEventData::TowerCreationEventData(int towerID, float timeStamp){
   this -> timeStamp = timeStamp;
   this -> towerID = towerID;
 }
