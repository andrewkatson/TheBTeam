#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;
class TowerCreationEventData : public EventDataInterface{
public:
  //a value corresponding to row*maxCol + col of the location of the tower (or tile if none exists yet)
  int towerPosID;
  //the index corresponding to a type in TowersToChoose.
  //used to find the initial type which we then use to find the upgraded version
  string towerTypeID;
  float timeStamp;

  TowerCreationEventData(int towerPosID, string towerTypeID, float timeStamp);
};
