
#include "../include/Events/ActorAttackEvent.hpp"

const EventType ActorAttackEvent::eventType = EventType(&ActorAttackEvent::eventType, string("ActorAttackEvent"));

ActorAttackEvent::ActorAttackEvent(){

}
ActorAttackEvent::ActorAttackEvent(string actorAttackingID, string actorDefendingID, float timeStamp){
  this -> data = unique_ptr<ActorAttackEventData>(new ActorAttackEventData(actorAttackingID, actorDefendingID, timeStamp));
}

const EventType& ActorAttackEvent::getEventType() const{
  return this -> eventType;
}

float ActorAttackEvent::GetTimeStamp() const {
  return static_cast<ActorAttackEventData*>((this -> data).get()) -> timeStamp;
}
