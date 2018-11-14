#pragma once

#include "EventType.hpp"
#include "EventDataInterface.hpp"
#include "BalanceChangeEventData.hpp"
#include "EventInterface.hpp"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;


class BalanceChangeEvent : public EventInterface{
public:
  unique_ptr<EventDataInterface> data;
  static const EventType eventType;

  BalanceChangeEvent();
  BalanceChangeEvent(int balanceChange, float timeStamp);

  const EventType& getEventType() const;
  float GetTimeStamp() const;
};
