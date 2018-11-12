#include "Events/LoseHitpointsEventData.hpp"

LoseHitpointsEventData::LoseHitpointsEventData(long long  actorID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;

}
