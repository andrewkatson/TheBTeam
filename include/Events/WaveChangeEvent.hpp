#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "WaveChangeEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class WaveChangeEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  WaveChangeEvent();
  WaveChangeEvent(int waveNum, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
