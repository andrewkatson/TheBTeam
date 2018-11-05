#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ActorAttackEventData : public EventDataInterface{
public:
  long long actorID;
  float timeStamp;

  ActorAttackEventData(long long actorID, float timeStamp);
};
