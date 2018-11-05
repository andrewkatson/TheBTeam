#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "ActorAttackEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class ActorAttackEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  ActorAttackEvent();
  ActorAttackEvent(string actorAttackingID, string actorDefendingID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
