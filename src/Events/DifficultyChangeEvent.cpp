//
// Created by jeremyelkayam on 11/28/18.
//

#include "Events/DifficultyChangeEvent.hpp"

const EventType DifficultyChangeEvent::eventType = EventType(&DifficultyChangeEvent::eventType, string("DifficultyChangeEvent"));

DifficultyChangeEvent::DifficultyChangeEvent() {}
DifficultyChangeEvent::DifficultyChangeEvent(int difficulty, float timeStamp) {
  this -> data = unique_ptr<DifficultyChangeEventData>(new DifficultyChangeEventData(difficulty, timeStamp));
}

const EventType& DifficultyChangeEvent::getEventType() const{
  return this -> eventType;
}

float DifficultyChangeEvent::GetTimeStamp() const {
  return static_cast<DifficultyChangeEventData*>((this -> data).get()) -> timeStamp;
}
