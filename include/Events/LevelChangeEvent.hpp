#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "LevelChangeEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class LevelChangeEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  LevelChangeEvent();
  LevelChangeEvent(int level, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
