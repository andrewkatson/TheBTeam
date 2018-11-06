#include "../include/Events/ActorDestroyedEventData.hpp"

ActorDestroyedEventData::ActorDestroyedEventData(long long actorID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;

}
