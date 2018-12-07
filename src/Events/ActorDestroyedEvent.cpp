
#include "Events/ActorDestroyedEvent.hpp"

const EventType ActorDestroyedEvent::eventType = EventType(&ActorDestroyedEvent::eventType, string("ActorDestroyedEvent"));

ActorDestroyedEvent::ActorDestroyedEvent(){

}
ActorDestroyedEvent::ActorDestroyedEvent(long long actorID, shared_ptr<ActorInterface> actorDestroyed, float timeStamp, bool fed){
  this -> data = unique_ptr<ActorDestroyedEventData>(new ActorDestroyedEventData(actorID, actorDestroyed, timeStamp, fed));
}

const EventType& ActorDestroyedEvent::getEventType() const{
  return this -> eventType;
}

float ActorDestroyedEvent::GetTimeStamp() const {
  return static_cast<ActorDestroyedEventData*>((this -> data).get()) -> timeStamp;
}
