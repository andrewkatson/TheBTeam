#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ProjectileExplosionEventData : public EventDataInterface{
public:
  long long projectileID;
  float timeStamp;

  ProjectileExplosionEventData(long long  projectileID, float timeStamp);
};
