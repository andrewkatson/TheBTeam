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
  schoolLevel=textLoader->getInteger(string("IDS_Default_School"));
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this-> registerEvents();
  this -> registerDelegates();
}

void Player::registerDelegates(){
  EventManager::EventDelegate optionSelectedDelegate = std::bind(&Player::handleOptionSelectedEvent, this, _1);
  OptionSelectedEvent optionSelectedEvent = OptionSelectedEvent();
  const EventType optionSelectedEventType = optionSelectedEvent.getEventType();
  this -> eventManager -> registerDelegate(optionSelectedDelegate, textLoader -> getString(string("IDS_OMSD_P")), optionSelectedEventType);
  EventManager::EventDelegate difficultyChangeDelegate = std::bind(&Player::handleDiffChanged, this, _1);
  DifficultyChangeEvent difficultyChangeEvent = DifficultyChangeEvent();
  const EventType difficultyChangeEventType = difficultyChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(difficultyChangeDelegate, textLoader -> getString(string("IDS_Player_DifficultyChange")),difficultyChangeEventType);
}

void Player::handleDiffChanged(const EventInterface& event){
  auto difficultyChangedEvent = static_cast<const DifficultyChangeEvent*>(&event);
  auto difficultyChangedEventData = static_cast<DifficultyChangeEventData*>((difficultyChangedEvent->data).get());

  schoolLevel=difficultyChangedEventData->difficulty;
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

  //make a generic option selected events event, get its type, and register it
  OptionSelectedEvent optionSelectedEvent = OptionSelectedEvent();
  EventType optionSelectedEventType = optionSelectedEvent.getEventType();
  this -> eventManager -> registerEvent(optionSelectedEventType);
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

void Player::handleOptionSelectedEvent(const EventInterface& event){
    // different ID's need to be checked 0 = school, 1 = population, 4 = start money
    // Get the optionselectedevent and get the data from it
    auto optionSelectedEvent = static_cast<const OptionSelectedEvent*>(&event);
    auto optionSelectedEventData = static_cast<OptionSelectedEventData*>((optionSelectedEvent->data).get());
    //the time object of the class
    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

    if(optionSelectedEventData -> optionID == 0){
        shared_ptr<EventInterface> newDiff = make_shared<DifficultyChangeEvent>(optionSelectedEventData -> newValue + 1, nowInNano);

        this -> eventManager -> queueEvent(newDiff);
    }
    else if(optionSelectedEventData -> optionID == 1){
        this -> population = optionSelectedEventData -> newValue + 1;
    }
    else if(optionSelectedEventData -> optionID == 4){
        if(optionSelectedEventData -> newValue == 0){
            updateBalance(20);
        }
        else if(optionSelectedEventData -> newValue == 1){
            updateBalance(100);
        }
        else if(optionSelectedEventData -> newValue == 2){
            updateBalance(1000);
        }
    }

}
