
#include "Events/WaveChangeEvent.hpp"

const EventType WaveChangeEvent::eventType = EventType(&WaveChangeEvent::eventType, string("WaveChangeEvent"));

WaveChangeEvent::WaveChangeEvent(){

}
WaveChangeEvent::WaveChangeEvent(int waveNum, float timeStamp){
  this -> data = unique_ptr<WaveChangeEventData>(new WaveChangeEventData(waveNum, timeStamp));
}

const EventType& WaveChangeEvent::getEventType() const{
  return this -> eventType;
}

float WaveChangeEvent::GetTimeStamp() const {
  return static_cast<WaveChangeEventData*>((this -> data).get()) -> timeStamp;
}
