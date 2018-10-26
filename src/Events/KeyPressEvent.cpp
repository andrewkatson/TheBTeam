#include "../include/Events/KeyPressEvent.hpp"
/*
 *  Event generated when a key is pressed by the user
 * @author Andrew Katson
 */

 //the event type for ALL objects of this event will be set to the value
 //of the address of this event type variable
 const EventType KeyPressEvent::eventType = EventType(&KeyPressEvent::eventType);

/*
 * constructor used just for registering
 */
KeyPressEvent::KeyPressEvent(){

}

/*
 * constructor a key press event
 * @param keyID: the string identifier for the key pressed
 * @param timeStamp: the timestamp of the creation of this event
 */
KeyPressEvent::KeyPressEvent(string keyID, float timeStamp){
  this -> data = unique_ptr<KeyPressEventData>(new KeyPressEventData(keyID, timeStamp));
}
/*
 * return the event type
 */
const EventType& KeyPressEvent::getEventType() const{
  return this -> eventType;
}

/*
 * return the time stamp of this event
 */
float KeyPressEvent::GetTimeStamp() const {
  return static_cast<KeyPressEventData*>((this -> data).get()) -> timeStamp;
}
