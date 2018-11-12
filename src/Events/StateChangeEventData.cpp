#include "Events/StateChangeEventData.hpp"

/*
 * container for the data held by a mouse press event
 * @author Andrew Katson
 */

 StateChangeEventData::StateChangeEventData(State state,float timeStamp){
   this ->state = state;
   this -> timeStamp = timeStamp;
 }

 StateChangeEventData::StateChangeEventData(State state, int row, int col, float timeStamp){
   this ->state = state;
   this ->row = row;
   this ->col = col;
   this -> timeStamp = timeStamp;
 }
