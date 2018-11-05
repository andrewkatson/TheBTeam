#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "LoseHitpointsEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class LoseHitpointsEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  LoseHitpointsEvent();
  LoseHitpointsEvent(string actorID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
