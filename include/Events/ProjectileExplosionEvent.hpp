#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "ProjectileExplosionEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class ProjectileExplosionEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  ProjectileExplosionEvent();
  ProjectileExplosionEvent(long long  projectileID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
