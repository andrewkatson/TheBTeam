
#include "Events/ActorCreatedEvent.hpp"

const EventType ActorCreatedEvent::eventType = EventType(&ActorCreatedEvent::eventType, string("ActorCreatedEvent"));

ActorCreatedEvent::ActorCreatedEvent(){

}
ActorCreatedEvent::ActorCreatedEvent(shared_ptr<ActorInterface> actorCreated, bool isProjectile, float timeStamp){
  this -> data = unique_ptr<ActorCreatedEventData>(new ActorCreatedEventData(actorCreated, isProjectile, timeStamp));
}

const EventType& ActorCreatedEvent::getEventType() const{
  return this -> eventType;
}

float ActorCreatedEvent::GetTimeStamp() const {
  return static_cast<ActorCreatedEventData*>((this -> data).get()) -> timeStamp;
}
