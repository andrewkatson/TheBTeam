#include "Events/TowerRemoveEvent.hpp"
/*
 *  Event generated when a tower is removed (includes obstacles) by the user
 * @author Andrew Katson
 */

 //the event type for ALL objects of this event will be set to the value
 //of the address of this event type variable
 const EventType TowerRemoveEvent::eventType = EventType(&TowerRemoveEvent::eventType, string("TowerCreationEvent"));

/*
 * constructor used just for registering
 */
TowerRemoveEvent::TowerRemoveEvent(){

}

/*
 * constructor a key press event
 * @param towerPosID: the string identifier for the key pressed
 * @param timeStamp: the timestamp of the creation of this event
 */
TowerRemoveEvent::TowerRemoveEvent(int towerPosID,  float timeStamp){
  this -> data = unique_ptr<TowerRemoveEventData>(new TowerRemoveEventData(towerPosID, timeStamp));
}
/*
 * return the event type
 */
const EventType& TowerRemoveEvent::getEventType() const{
  return this -> eventType;
}

/*
 * return the time stamp of this event
 */
float TowerRemoveEvent::GetTimeStamp() const {
  return static_cast<TowerRemoveEventData*>((this -> data).get()) -> timeStamp;
}
