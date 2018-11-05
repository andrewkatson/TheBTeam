#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ActorAttackEventData : public EventDataInterface{
public:
  long long actorAttackingID;
  long long actorDefendingID;
  float timeStamp;

  ActorAttackEventData(long long actorAttackingID, long long actorDefendingID, float timeStamp);
};
