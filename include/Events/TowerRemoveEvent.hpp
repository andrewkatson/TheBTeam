#pragma once
#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "TowerRemoveEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

class TowerRemoveEvent : public EventInterface{

public:
  //data container with any information pertaining to an instance of this event
  unique_ptr<EventDataInterface> data;
  //the event type identifier for this event (shared between all instances of this event type)
  static const EventType eventType;

  TowerRemoveEvent();
  TowerRemoveEvent(int towerPosID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
