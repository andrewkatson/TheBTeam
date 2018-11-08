#include "Events/StateChangeEvent.hpp"
/*
 *  Event generated when the mouse is pressed by the user
 * @author Andrew Katson
 */

 //the event type for ALL objects of this event will be set to the value
 //of the address of this event type variable
 const EventType StateChangeEvent::eventType = EventType(&StateChangeEvent::eventType,string("StateChangeEvent"));

/*
 * constructor used just for registering
 */
StateChangeEvent::StateChangeEvent(){

}

/*
 * constructor a key press event
 * @param state: the enum for the state
 * @param timeStamp: the timestamp of the creation of this event
 */
StateChangeEvent::StateChangeEvent(State state, float timeStamp){
  this -> data = unique_ptr<StateChangeEventData>(new StateChangeEventData(state, timeStamp));
}
/*
 * return the event type
 */
const EventType& StateChangeEvent::getEventType() const{
  return this -> eventType;
}

/*
 * return the time stamp of this event
 */
float StateChangeEvent::GetTimeStamp() const {
  return static_cast<StateChangeEventData*>((this -> data).get()) -> timeStamp;
}
