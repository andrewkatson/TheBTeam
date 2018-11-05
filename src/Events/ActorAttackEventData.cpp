#include "../include/Events/ActorAttackEventData.hpp"

ActorAttackEventData::ActorAttackEventData(long long actorID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;

}
