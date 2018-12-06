#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "MapGeneratedEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class MapGeneratedEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  MapGeneratedEvent();
  MapGeneratedEvent(float timeStamp,const vector<vector<int>>& distances,const vector<int>&entrances, vector<vector<std::unordered_set<int>>>combinedPaths);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
