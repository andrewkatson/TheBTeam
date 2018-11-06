#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ActorDestroyedEventData : public EventDataInterface{
public:
  long long  actorID;
  float timeStamp;

  ActorDestroyedEventData(long long actorID, float timeStamp);
};
