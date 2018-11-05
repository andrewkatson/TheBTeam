#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class OptionSelectedEventData : public EventDataInterface{
public:
  string optionID;
  float timeStamp;

  OptionSelectedEventData(string optionID, float timeStamp);
};
