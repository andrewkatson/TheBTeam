//
// Created by jeremyelkayam on 12/2/18.
//

#include "Events/PlaySoundEventData.hpp"

PlaySoundEventData::PlaySoundEventData(string typeID, string soundID, float timeStamp){
  this->typeID=typeID;
  this->soundID=soundID;
  this->timeStamp=timeStamp;
}