#include "Events/LoseHitpointsEventData.hpp"

LoseHitpointsEventData::LoseHitpointsEventData(int lostHitpoints, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> lostHitpoints = lostHitpoints;

}
