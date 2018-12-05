//
// Created by jeremyelkayam on 12/4/18.
//

#ifndef CSCI437_SPEEDCHANGEEVENTDATA_HPP
#define CSCI437_SPEEDCHANGEEVENTDATA_HPP

#include "EventDataInterface.hpp"


class SpeedChangeEventData : public EventDataInterface {
public:
  float newSpeedScale,timeStamp;

  SpeedChangeEventData(float newSpeedScale, float timeStamp);

};


#endif //CSCI437_SPEEDCHANGEEVENTDATA_HPP
