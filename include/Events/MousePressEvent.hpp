#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "MousePressEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

class MousePressEvent : public EventInterface{

public:
  //data container with any information pertaining to an instance of this event
  unique_ptr<EventDataInterface> data;
  //the event type identifier for this event (shared between all instances of this event type)
  static const EventType eventType;

  MousePressEvent();
  MousePressEvent(string partOfMouse, float x,float y, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
