#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ProjectileExplosionEventData : public EventDataInterface{
public:
  string projectileID;
  float timeStamp;

  ProjectileExplosionEventData(string projectileID, float timeStamp);
};
