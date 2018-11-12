#include "Events/OptionSelectedEventData.hpp"

OptionSelectedEventData::OptionSelectedEventData(int optionID, int newValue, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> optionID = optionID;
  this -> newValue = newValue;
}
