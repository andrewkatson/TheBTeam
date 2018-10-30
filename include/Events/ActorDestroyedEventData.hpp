#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ActorDestroyedEventData : public EventDataInterface{
public:
  string actorID;
  float timeStamp;

  ActorDestroyedEventData(string actorID, float timeStamp);
};
