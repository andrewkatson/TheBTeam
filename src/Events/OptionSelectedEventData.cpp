#include "../include/Events/OptionSelectedEventData.hpp"

OptionSelectedEventData::OptionSelectedEventData(int optionID, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> optionID = optionID;

}
