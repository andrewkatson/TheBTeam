#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "OptionSelectedEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class OptionSelectedEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  OptionSelectedEvent();
  OptionSelectedEvent(int optionID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
