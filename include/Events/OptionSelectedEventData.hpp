#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class OptionSelectedEventData : public EventDataInterface{
public:
  int optionID;
  int newValue;
  float timeStamp;

  OptionSelectedEventData(int optionID, int newValue, float timeStamp);
};
