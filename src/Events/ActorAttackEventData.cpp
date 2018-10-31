#include "../include/Events/ActorAttackEventData.hpp"

ActorAttackEventData::ActorAttackEventData(string actorID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;

}
