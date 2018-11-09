#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class MapGeneratedEventData : public EventDataInterface{
public:
  float timeStamp;

  MapGeneratedEventData(float timeStamp);
};
