#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;
class TowerRemoveEventData : public EventDataInterface{
public:
  //a value corresponding to row*maxCol + col of the location of the tower (or tile if none exists yet)
  int towerPosID;
  float timeStamp;

  TowerRemoveEventData(int towerPosID, float timeStamp);
};
