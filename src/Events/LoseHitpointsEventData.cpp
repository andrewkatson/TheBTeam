#include "../include/Events/LoseHitpointsEventData.hpp"

LoseHitpointsEventData::LoseHitpointsEventData(string actorID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;

}
