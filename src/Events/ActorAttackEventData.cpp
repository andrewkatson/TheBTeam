#include "../include/Events/ActorAttackEventData.hpp"

ActorAttackEventData::ActorAttackEventData(string actorAttackingID, string actorDefendingID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorAttackingID = actorAttackingID;
  this -> actorDefendingID = actorDefendingID;

}
