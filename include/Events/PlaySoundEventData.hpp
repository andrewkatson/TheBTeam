//
// Created by jeremyelkayam on 12/2/18.
//

#ifndef CSCI437_PLAYSOUNDEVENTDATA_HPP
#define CSCI437_PLAYSOUNDEVENTDATA_HPP

#include "EventDataInterface.hpp"
#include <string>

using std::string;

class PlaySoundEventData : public EventDataInterface {
public:
  string typeID,soundID;
  float timeStamp;

  PlaySoundEventData(string typeID, string soundID, float timeStamp);

};


#endif //CSCI437_PLAYSOUNDEVENTDATA_HPP
