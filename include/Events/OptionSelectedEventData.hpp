#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class OptionSelectedEventData : public EventDataInterface{
public:
  int optionID;
  float timeStamp;

  OptionSelectedEventData(int optionID, float timeStamp);
};
