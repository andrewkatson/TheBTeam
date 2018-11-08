#include "Events/KeyPressEventData.hpp"

/*
 * container for the data held by a key press event
 * @author Andrew Katson
 */

 KeyPressEventData::KeyPressEventData(string keyID, float timeStamp){

   this -> timeStamp = timeStamp;
   this -> keyID = keyID;
 }
