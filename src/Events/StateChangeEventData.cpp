#include "Events/StateChangeEventData.hpp"

/*
 * container for the data held by a mouse press event
 * @author Andrew Katson
 */

 StateChangeEventData::StateChangeEventData(State state,float timeStamp){
   this ->state = state;
   this -> timeStamp = timeStamp;
 }
