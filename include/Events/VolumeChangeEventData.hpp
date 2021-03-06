//
// Created by jeremyelkayam on 12/5/18.
//

#ifndef CSCI437_VOLUMECHANGEEVENTDATA_HPP
#define CSCI437_VOLUMECHANGEEVENTDATA_HPP

#include "EventDataInterface.hpp"

enum class SoundType {SFX, Music};

class VolumeChangeEventData : public EventDataInterface {
public:
  float newVolume;
  SoundType type;
  float timeStamp;

  VolumeChangeEventData(float newVolume, SoundType type,float timeStamp);

};


#endif //CSCI437_VOLUMECHANGEEVENTDATA_HPP
