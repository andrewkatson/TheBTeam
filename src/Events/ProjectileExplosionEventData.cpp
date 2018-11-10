#include "Events/ProjectileExplosionEventData.hpp"

ProjectileExplosionEventData::ProjectileExplosionEventData(long long  projectileID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> projectileID = projectileID;
}
