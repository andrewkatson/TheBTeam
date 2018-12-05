//
// Created by jeremyelkayam on 12/5/18.
//

#ifndef CSCI437_VOLUMECHANGEEVENT_HPP
#define CSCI437_VOLUMECHANGEEVENT_HPP

#include "EventInterface.hpp"
#include "VolumeChangeEventData.hpp"
#include <memory>

using std::unique_ptr;

class VolumeChangeEvent : public EventInterface {
public:
unique_ptr<EventDataInterface> data;
static const EventType eventType;

VolumeChangeEvent();
VolumeChangeEvent(int newVolume, SoundType type,float timeStamp);

const EventType& getEventType() const;
float GetTimeStamp() const;

};


#endif //CSCI437_VOLUMECHANGEEVENT_HPP
