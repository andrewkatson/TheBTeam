//
// Created by jeremyelkayam on 12/4/18.
//

#include "Events/SpeedChangeEvent.hpp"

const EventType SpeedChangeEvent::eventType = EventType(&SpeedChangeEvent::eventType, string("SpeedChangeEvent"));

SpeedChangeEvent::SpeedChangeEvent(){

}
SpeedChangeEvent::SpeedChangeEvent(float newSpeedScale, float timeStamp){
  this -> data = unique_ptr<SpeedChangeEventData>(new SpeedChangeEventData(newSpeedScale, timeStamp));
}

const EventType& SpeedChangeEvent::getEventType() const{
  return this -> eventType;
}

float SpeedChangeEvent::GetTimeStamp() const {
  return static_cast<SpeedChangeEventData*>((this -> data).get()) -> timeStamp;
}
