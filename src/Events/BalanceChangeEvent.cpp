#include "Events/BalanceChangeEvent.hpp"

const EventType BalanceChangeEvent::eventType = EventType(&BalanceChangeEvent::eventType, string("BalanceChangeEvent"));

BalanceChangeEvent::BalanceChangeEvent(){

}
BalanceChangeEvent::BalanceChangeEvent(int balanceChange, float timeStamp){
  this -> data = unique_ptr<BalanceChangeEventData>(new BalanceChangeEventData(balanceChange, timeStamp));
}

const EventType& BalanceChangeEvent::getEventType() const{
  return this -> eventType;
}

float BalanceChangeEvent::GetTimeStamp() const {
  return static_cast<BalanceChangeEventData*>((this -> data).get()) -> timeStamp;
}
