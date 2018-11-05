#pragma once

#include <string>
#include "EventDataInterface.hpp"

using std::string;

class ProjectileExplosionEventData : public EventDataInterface{
public:
  string projectileID;
  float timeStamp;

  ActorAttackEventData(string projectileID, float timeStamp);
};
