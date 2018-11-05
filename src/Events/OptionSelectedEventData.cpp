#include "../include/Events/OptionSelectedEventData.hpp"

OptionSelectedEventData::OptionSelectedEventData(string optionID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> optionID = optionID;

}
