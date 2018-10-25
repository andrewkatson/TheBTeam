#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;
class KeyPressEventData : public EventDataInterface{
public:
  string keyID;
  float timeStamp;

  KeyPressEventData(string keyID, float timeStamp);
};
