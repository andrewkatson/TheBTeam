#include "../include/Events/MousePressEvent.hpp"
/*
 *  Event generated when the mouse is pressed by the user
 * @author Andrew Katson
 */

 //the event type for ALL objects of this event will be set to the value
 //of the address of this event type variable
 const EventType MousePressEvent::eventType = EventType(&MousePressEvent::eventType,string("MousePressEvent"));

/*
 * constructor used just for registering
 */
MousePressEvent::MousePressEvent(){

}

/*
 * constructor a key press event
 * @param partOfMouse: the left, or right
 * @param x: the x position of the mousee
 * @param y: the y position of the mouse
 * @param timeStamp: the timestamp of the creation of this event
 */
MousePressEvent::MousePressEvent(string partOfMouse, float x, float y, float timeStamp){
  this -> data = unique_ptr<MousePressEventData>(new MousePressEventData(partOfMouse,x,y, timeStamp));
}
/*
 * return the event type
 */
const EventType& MousePressEvent::getEventType() const{
  return this -> eventType;
}

/*
 * return the time stamp of this event
 */
float MousePressEvent::GetTimeStamp() const {
  return static_cast<MousePressEventData*>((this -> data).get()) -> timeStamp;
}
