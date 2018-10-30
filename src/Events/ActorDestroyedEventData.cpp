#include "../include/Events/ActorDestroyedEventData.hpp"

ActorDestroyedEventData::ActorDestroyedEventData(string actorID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;

}
