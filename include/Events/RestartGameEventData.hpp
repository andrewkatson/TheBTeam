#pragma once
#include <string>
#include "EventDataInterface.hpp"

using std::string;

class RestartGameEventData : public EventDataInterface{
public:
  float timeStamp;

  RestartGameEventData (float timeStamp);
};
