#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;
class TowerCreationEventData : public EventDataInterface{
public:
  int towerID;
  float timeStamp;

  TowerCreationEventData(int towerID, float timeStamp);
};
