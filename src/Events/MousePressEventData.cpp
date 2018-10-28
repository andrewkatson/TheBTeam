#include "../include/Events/MousePressEventData.hpp"

/*
 * container for the data held by a mouse press event
 * @author Andrew Katson
 */

 MousePressEventData::MousePressEventData(string partOfMouse,float x, float y ,float timeStamp){
   this ->partOfMouse = partOfMouse;
   this -> timeStamp = timeStamp;
   this -> x = x;
   this -> y = y;
 }
