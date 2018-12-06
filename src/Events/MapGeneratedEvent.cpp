
#include "Events/MapGeneratedEvent.hpp"

const EventType MapGeneratedEvent::eventType = EventType(&MapGeneratedEvent::eventType, string("MapGeneratedEvent"));

MapGeneratedEvent::MapGeneratedEvent(){

}
MapGeneratedEvent::MapGeneratedEvent(float timeStamp,const vector<vector<int>>& distances,const vector<int>& entrances, vector<vector<std::unordered_set<int>>>combinedPaths){
  this -> data = unique_ptr<MapGeneratedEventData>(new MapGeneratedEventData( timeStamp,distances,entrances, combinedPaths));

}

const EventType& MapGeneratedEvent::getEventType() const{
  return this -> eventType;
}

float MapGeneratedEvent::GetTimeStamp() const {
  return static_cast<MapGeneratedEventData*>((this -> data).get()) -> timeStamp;
}
