#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "ActorDestroyedEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class ActorDestroyedEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  ActorDestroyedEvent();
  ActorDestroyedEvent(long long actorID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
