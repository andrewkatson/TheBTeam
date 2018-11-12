#include "Events/LevelChangeEvent.hpp"

const EventType LevelChangeEvent::eventType = EventType(&LevelChangeEvent::eventType, string("LevelChangeEvent"));

LevelChangeEvent::LevelChangeEvent(){

}
LevelChangeEvent::LevelChangeEvent(int level, float timeStamp){
  this -> data = unique_ptr<LevelChangeEventData>(new LevelChangeEventData(level, timeStamp));
}

const EventType& LevelChangeEvent::getEventType() const{
  return this -> eventType;
}

float LevelChangeEvent::GetTimeStamp() const {
  return static_cast<LevelChangeEventData*>((this -> data).get()) -> timeStamp;
}
