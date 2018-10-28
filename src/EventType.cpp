#include "EventType.hpp"

EventType::EventType(){
  cout << "what" << endl;
}

EventType::EventType(const EventType* eventType){
  this -> type = (long) addressof(*eventType);
}
