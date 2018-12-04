//
// Created by jeremyelkayam on 12/2/18.
//

#ifndef CSCI437_PLAYSOUNDEVENT_HPP
#define CSCI437_PLAYSOUNDEVENT_HPP


#include <memory>
#include "EventInterface.hpp"
#include "EventDataInterface.hpp"
#include "PlaySoundEventData.hpp"

using std::unique_ptr;

class PlaySoundEvent : public EventInterface {
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  PlaySoundEvent();
  PlaySoundEvent(string typeID, string soundID, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};


#endif //CSCI437_PLAYSOUNDEVENT_HPP
