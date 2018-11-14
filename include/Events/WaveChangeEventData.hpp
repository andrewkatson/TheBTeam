#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class WaveChangeEventData : public EventDataInterface{
public:
  int waveNum;
  float timeStamp;

  WaveChangeEventData (int waveNum, float timeStamp);
};
