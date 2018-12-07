#include "Events/ActorDestroyedEventData.hpp"

ActorDestroyedEventData::ActorDestroyedEventData(long long actorID, shared_ptr<ActorInterface> actorDestroyed, float timeStamp, bool fed){
  this -> timeStamp = timeStamp;
  this -> actorID = actorID;
  this -> actorDestroyed = actorDestroyed;
  this -> fed = fed;

}
