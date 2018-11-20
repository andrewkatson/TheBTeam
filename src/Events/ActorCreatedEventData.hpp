#include "Events/ActorCreatedEventData.hpp"

ActorCreatedEventData::ActorCreatedEventData(shared_ptr<ActorInterface> actorCreated, bool isProjectile, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> actorCreated = actorCreated;
  this -> isProjectile = isProjectile;
}
