#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ActorAttackEventData : public EventDataInterface{
public:
  string actorID;
  float timeStamp;

  ActorAttackEventData(string actorID, float timeStamp);
};
