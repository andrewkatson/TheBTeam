#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ActorAttackEventData : public EventDataInterface{
public:
  string actorAttackingID;
  string actorDefendingID;
  float timeStamp;

  ActorAttackEventData(string actorAttackingID, string actorDefendingID, float timeStamp);
};
