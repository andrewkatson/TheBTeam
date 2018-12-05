//
// Created by jeremyelkayam on 12/4/18.
//

#include "Events/SpeedChangeEventData.hpp"

SpeedChangeEventData::SpeedChangeEventData(float newSpeedScale, float timeStamp) {
  this->newSpeedScale=newSpeedScale;
  this->timeStamp=timeStamp;
}