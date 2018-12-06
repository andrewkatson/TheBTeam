//
// Created by jeremyelkayam on 12/5/18.
//

#include "Events/VolumeChangeEvent.hpp"


const EventType VolumeChangeEvent::eventType = EventType(&VolumeChangeEvent::eventType, string("VolumeChangeEvent"));

VolumeChangeEvent::VolumeChangeEvent(){

}
VolumeChangeEvent::VolumeChangeEvent(float newVolume, SoundType type,float timeStamp){
  this -> data = unique_ptr<VolumeChangeEventData>(new VolumeChangeEventData(newVolume, type,timeStamp));
}

const EventType& VolumeChangeEvent::getEventType() const{
  return this -> eventType;
}

float VolumeChangeEvent::GetTimeStamp() const {
  return static_cast<VolumeChangeEventData*>((this -> data).get()) -> timeStamp;
}