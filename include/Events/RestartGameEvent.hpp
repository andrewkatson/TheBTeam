#pragma once


#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "RestartGameEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class RestartGameEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  RestartGameEvent();
  RestartGameEvent(float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
