
#include "Events/LoseHitpointsEvent.hpp"

const EventType LoseHitpointsEvent::eventType = EventType(&LoseHitpointsEvent::eventType, string("LoseHitpointsEvent"));

LoseHitpointsEvent::LoseHitpointsEvent(){

}
LoseHitpointsEvent::LoseHitpointsEvent(int lostHitpoints, float timeStamp){
  this -> data = unique_ptr<LoseHitpointsEventData>(new LoseHitpointsEventData(lostHitpoints, timeStamp));
}

const EventType& LoseHitpointsEvent::getEventType() const{
  return this -> eventType;
}

float LoseHitpointsEvent::GetTimeStamp() const {
  return static_cast<LoseHitpointsEventData*>((this -> data).get()) -> timeStamp;
}
