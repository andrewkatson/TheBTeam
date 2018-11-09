
#include "Events/MapGeneratedEvent.hpp"

const EventType MapGeneratedEvent::eventType = EventType(&MapGeneratedEvent::eventType, string("MapGeneratedEvent"));

MapGeneratedEvent::MapGeneratedEvent(){

}
MapGeneratedEvent::MapGeneratedEvent(float timeStamp){
  this -> data = unique_ptr<MapGeneratedEventData>(new MapGeneratedEventData( timeStamp));
}

const EventType& MapGeneratedEvent::getEventType() const{
  return this -> eventType;
}

float MapGeneratedEvent::GetTimeStamp() const {
  return static_cast<MapGeneratedEventData*>((this -> data).get()) -> timeStamp;
}
