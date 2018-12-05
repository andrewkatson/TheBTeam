//
// Created by jeremyelkayam on 12/5/18.
//

#include "Events/VolumeChangeEventData.hpp"

VolumeChangeEventData::VolumeChangeEventData(float newVolume, SoundType type,float timeStamp){
  this->newVolume=newVolume;
  this->type=type;
  this->timeStamp=timeStamp;
}