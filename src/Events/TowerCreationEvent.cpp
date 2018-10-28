#include "../include/Events/TowerCreationEvent.hpp"
/*
 *  Event generated when a tower is created (bought) by the user
 * @author Andrew Katson
 */

 //the event type for ALL objects of this event will be set to the value
 //of the address of this event type variable
 const EventType TowerCreationEvent::eventType = EventType(&TowerCreationEvent::eventType);

/*
 * constructor used just for registering
 */
TowerCreationEvent::TowerCreationEvent(){

}

/*
 * constructor a key press event
 * @param keyID: the string identifier for the key pressed
 * @param timeStamp: the timestamp of the creation of this event
 */
TowerCreationEvent::TowerCreationEvent(int towerID, float timeStamp){
  this -> data = unique_ptr<TowerCreationEventData>(new TowerCreationEventData(towerID, timeStamp));
}
/*
 * return the event type
 */
const EventType& TowerCreationEvent::getEventType() const{
  return this -> eventType;
}

/*
 * return the time stamp of this event
 */
float TowerCreationEvent::GetTimeStamp() const {
  return static_cast<TowerCreationEventData*>((this -> data).get()) -> timeStamp;
}