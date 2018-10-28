#pragma once


#include <string>
#include "EventDataInterface.hpp"

using std::string;
class MousePressEventData : public EventDataInterface{
public:
  string partOfMouse;
  float x;
  float y;
  float timeStamp;

  MousePressEventData(string partOfMouse, float x, float y, float timeStamp);
};
