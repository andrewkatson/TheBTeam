
#include "../include/Events/ActorDestroyedEvent.hpp"

const EventType ActorDestroyedEvent::eventType = EventType(&ActorDestroyedEvent::eventType, string("ActorDestroyedEvent"));

ActorDestroyedEvent::ActorDestroyedEvent(){

}
ActorDestroyedEvent::ActorDestroyedEvent(string actorID, float timeStamp){
  this -> data = unique_ptr<ActorDestroyedEventData>(new ActorDestroyedEventData(actorID, timeStamp));
}

const EventType& ActorDestroyedEvent::getEventType() const{
  return this -> eventType;
}

float ActorDestroyedEvent::GetTimeStamp() const {
  return static_cast<ActorDestroyedEventData*>((this -> data).get()) -> timeStamp;
}
