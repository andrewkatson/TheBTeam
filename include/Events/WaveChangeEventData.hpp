#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class WaveChangeEventData : public EventDataInterface{
public:
  int waveID;
  float timeStamp;

  WaveChangeEventData (int waveID, float timeStamp);
};
