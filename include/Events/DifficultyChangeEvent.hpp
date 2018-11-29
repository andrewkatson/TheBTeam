//
// Created by jeremyelkayam on 11/28/18.
// Raised whenever you change the high school level bitchez
//

#ifndef CSCI437_DIFFICULTYCHANGEEVENT_HPP
#define CSCI437_DIFFICULTYCHANGEEVENT_HPP

#include <memory>
#include "EventInterface.hpp"
#include "EventDataInterface.hpp"
#include "DifficultyChangeEventData.hpp"

using std::unique_ptr;

class DifficultyChangeEvent : public EventInterface {
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  DifficultyChangeEvent();
  DifficultyChangeEvent(int difficulty, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;

};


#endif //CSCI437_DIFFICULTYCHANGEEVENT_HPP
