//
// Created by jeremyelkayam on 12/2/18.
//

#include "Events/PlaySoundEvent.hpp"

const EventType PlaySoundEvent::eventType = EventType(&PlaySoundEvent::eventType, string("PlaySoundEvent"));

PlaySoundEvent::PlaySoundEvent() {}
PlaySoundEvent::PlaySoundEvent(string typeID, string soundID, float timeStamp) {
  this -> data = unique_ptr<PlaySoundEventData>(new PlaySoundEventData(typeID, soundID, timeStamp));
}

const EventType& PlaySoundEvent::getEventType() const{
  return this -> eventType;
}

float PlaySoundEvent::GetTimeStamp() const {
  return static_cast<PlaySoundEventData*>((this -> data).get()) -> timeStamp;
}