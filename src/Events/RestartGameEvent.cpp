#include "Events/RestartGameEvent.hpp"

const EventType RestartGameEvent::eventType = EventType(&RestartGameEvent::eventType, string("RestartGameEvent"));

RestartGameEvent::RestartGameEvent(){

}
RestartGameEvent::RestartGameEvent(float timeStamp){
  this -> data = unique_ptr<RestartGameEventData>(new RestartGameEventData(timeStamp));
}

const EventType& RestartGameEvent::getEventType() const{
  return this -> eventType;
}

float RestartGameEvent::GetTimeStamp() const {
  return static_cast<RestartGameEventData*>((this -> data).get()) -> timeStamp;
}
