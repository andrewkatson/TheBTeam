//
// Created by jeremyelkayam on 12/4/18.
//

#ifndef CSCI437_SPEEDCHANGEEVENT_HPP
#define CSCI437_SPEEDCHANGEEVENT_HPP

#include "EventInterface.hpp"
#include "EventDataInterface.hpp"
#include "SpeedChangeEventData.hpp"

using std::string;
using std::unique_ptr;


class SpeedChangeEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  SpeedChangeEvent();
  SpeedChangeEvent(float newSpeedScale, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};



#endif //CSCI437_SPEEDCHANGEEVENT_HPP
