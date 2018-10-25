#ifndef EVENTINTERFACE_H
#define EVENTINTERFACE_H

#include "EventType.hpp"
//NOTE USE CHRONO HIGHRESOLUTIONCLOCK FOR TIMESTAMPS
class EventInterface
{
public:
  virtual const EventType& getEventType() const = 0;
  virtual float GetTimeStamp() const = 0;
};

#endif
