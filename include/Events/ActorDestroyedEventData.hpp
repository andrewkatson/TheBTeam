#pragma once

#include <string>
#include <memory>
#include "EventDataInterface.hpp"
#include "ActorInterface.hpp"

using std::string;
using std::shared_ptr;

class ActorDestroyedEventData : public EventDataInterface{
public:
  long long  actorID;
  float timeStamp;
  shared_ptr<ActorInterface> actorDestroyed;

  ActorDestroyedEventData(long long actorID, shared_ptr<ActorInterface> actorDestroyed,float timeStamp);
};
