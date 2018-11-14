/*
  Player.cpp

  Purpose: Store and manage player attributes with set/get methods

  @author Jeremy Elkayam
 */

#include "Player.hpp"

Player::Player(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader)
{
  balance= textLoader->getInteger(string("IDS_P_B"));
  hitpoints= textLoader->getInteger(string("IDS_P_HP"));
  wave=textLoader->getInteger(string("IDS_Default_Wave"));
  level=textLoader->getInteger(string("IDS_Default_Level"));
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this-> registerEvents();
}

void Player::registerEvents(){
  //make a generic balance change event, get its type, and register it
  BalanceChangeEvent balanceChangeEvent = BalanceChangeEvent();
  EventType balanceChangeEventType = balanceChangeEvent.getEventType();
  this -> eventManager -> registerEvent(balanceChangeEventType);

  //make a generic hitpoint change events  event, get its type, and register it
  LoseHitpointsEvent loseHitpointsEvent = LoseHitpointsEvent();
  EventType loseHitpointsEventType = loseHitpointsEvent.getEventType();
  this -> eventManager -> registerEvent(loseHitpointsEventType);

  //make a generic wave change event, get its type, and register it
  WaveChangeEvent waveChangeEvent = WaveChangeEvent();
  EventType waveChangeEventType = waveChangeEvent.getEventType();
  this -> eventManager -> registerEvent(waveChangeEventType);

  //make a generic level change events event, get its type, and register it
  LevelChangeEvent levelChangeEvent = LevelChangeEvent();
  EventType levelChangeEventType = levelChangeEvent.getEventType();
  this -> eventManager -> registerEvent(levelChangeEventType);
}

void Player::updateBalance(int balance){

  //difference between the passed balance and the old balance
  int difference = balance - this->balance;

  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> bcEvent = make_shared<BalanceChangeEvent>(difference, nowInNano);

  this -> eventManager -> queueEvent(bcEvent);

  this->balance=balance;
}

void Player::modifyBalance(int modifyBy){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> bcEvent = make_shared<BalanceChangeEvent>(modifyBy, nowInNano);

  this -> eventManager -> queueEvent(bcEvent);

  this->balance+=modifyBy;
}

void Player::updateHitpoints(int points){
  //the difference between the old hitpoints and the new ones
  int difference = points - this->hitpoints;

  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> lhpEvent = make_shared<LoseHitpointsEvent>(difference, nowInNano);

  this -> eventManager -> queueEvent(lhpEvent);

  this->hitpoints=points;
}

void Player::modifyHitpoints(int pointsToDeduct){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> lhpEvent = make_shared<LoseHitpointsEvent>(pointsToDeduct, nowInNano);

  this -> eventManager -> queueEvent(lhpEvent);

  this->hitpoints-=pointsToDeduct;
}

void Player::updateWave(int wave){

  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> wcEvent = make_shared<WaveChangeEvent>(wave, nowInNano);

  this -> eventManager -> queueEvent(wcEvent);

  this->wave=wave;
}

void Player::updateLevel(int level){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> lcEvent = make_shared<LevelChangeEvent>(level, nowInNano);

  this -> eventManager -> queueEvent(lcEvent);

  this->level=level;
}
