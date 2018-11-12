#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class LevelChangeEventData : public EventDataInterface{
public:
  int level;
  float timeStamp;

  LevelChangeEventData (int level, float timeStamp);
};
