#include "../include/Events/ProjectileExplosionEventData.hpp"

ProjectileExplosionEventData::ProjectileExplosionEventData(string projectileID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> projectileID = projectileID;
}
