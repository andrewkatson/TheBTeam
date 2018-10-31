#pragma once

#include <string>
#include "EventDataInterface.hpp"
#include "GameState.hpp"

using std::string;
class StateChangeEventData : public EventDataInterface{
public:
  State state;
  float timeStamp;

  StateChangeEventData(State state, float timeStamp);
};
