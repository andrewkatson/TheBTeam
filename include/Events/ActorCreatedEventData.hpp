#pragma once

#include <string>
#include <memory>
#include "EventDataInterface.hpp"
#include "ActorInterface.hpp"

using std::string;
using std::shared_ptr;

class ActorCreatedEventData : public EventDataInterface{
public:
  shared_ptr<ActorInterface> actorCreated;
  bool isProjectile;
  float timeStamp;

  ActorCreatedEventData(shared_ptr<ActorInterface> actorCreated, bool isProjectile, float timeStamp);
};
