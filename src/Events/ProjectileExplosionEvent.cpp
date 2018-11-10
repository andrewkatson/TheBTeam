
#include "Events/ProjectileExplosionEvent.hpp"

const EventType ProjectileExplosionEvent::eventType = EventType(&ProjectileExplosionEvent::eventType, string("ProjectileExplosionEvent"));

ProjectileExplosionEvent::ProjectileExplosionEvent(){

}
ProjectileExplosionEvent::ProjectileExplosionEvent(long long  projectileID, float timeStamp){
  this -> data = unique_ptr<ProjectileExplosionEventData>(new ProjectileExplosionEventData(projectileID, timeStamp));
}

const EventType& ProjectileExplosionEvent::getEventType() const{
  return this -> eventType;
}

float ProjectileExplosionEvent::GetTimeStamp() const {
  return static_cast<ProjectileExplosionEventData*>((this -> data).get()) -> timeStamp;
}
