#ifndef EVENTINTERFACE_H
#define EVENTINTERFACE_H

#include "EventType.hpp"

class EventInterface
{
public:
  virtual const EventType& getEventType(void) const = 0;
  virtual float GetTimeStamp(void) const = 0;
};

#endif
