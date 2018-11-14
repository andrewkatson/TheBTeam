#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class LoseHitpointsEventData : public EventDataInterface{
public:
  int lostHitpoints;
  float timeStamp;

  LoseHitpointsEventData(int lostHitpoints, float timeStamp);
};
