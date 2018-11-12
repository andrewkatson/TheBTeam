#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class LoseHitpointsEventData : public EventDataInterface{
public:
  string actorID;
  float timeStamp;

  LoseHitpointsEventData(long long  actorID, float timeStamp);
};
