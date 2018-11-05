#include "../include/Events/ActorAttackEventData.hpp"

ActorAttackEventData::ActorAttackEventData(long long actorAttackingID, long long actorDefendingID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorAttackingID = actorAttackingID;
  this -> actorDefendingID = actorDefendingID;

}
