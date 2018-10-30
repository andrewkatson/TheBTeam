#include "EventType.hpp"

EventType::EventType(){
}

EventType::EventType(const EventType* eventType, string eventWithin){
  this -> type = (long) addressof(*eventType);
  this -> eventWithin = eventWithin;
}
