
#include "Events/OptionSelectedEvent.hpp"

const EventType OptionSelectedEvent::eventType = EventType(&OptionSelectedEvent::eventType, string("OptionSelectedEvent"));

OptionSelectedEvent::OptionSelectedEvent(){

}
OptionSelectedEvent::OptionSelectedEvent(int optionID, int newValue, float timeStamp){
  this -> data = unique_ptr<OptionSelectedEventData>(new OptionSelectedEventData(optionID, newValue, timeStamp));
}

const EventType& OptionSelectedEvent::getEventType() const{
  return this -> eventType;
}

float OptionSelectedEvent::GetTimeStamp() const {
  return static_cast<OptionSelectedEventData*>((this -> data).get()) -> timeStamp;
}
