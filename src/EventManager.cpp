
/*
  EventManager.cpp

  Purpose: Handles loading and execution of all events within the game.

  @author Mei-Ting Song
*/

#include "EventManager.hpp"


EventManager::EventManager(){
  queues.push_back(make_shared<event_queue>());
  queues.push_back(make_shared<event_queue>());
  process_queue = queues.at(0);
  register_queue = queues.at(1);
}

EventManager::~EventManager(){

}

//add an event to the queue of registered events
void EventManager::queueEvent(shared_ptr<EventInterface> event){
  //in case we do not find the event type we add it
  //to the map
  event_map::const_iterator it = EventDelegateMap.find(event -> getEventType());
  if(it == EventDelegateMap.end()){
    registerEvent(event -> getEventType());
  }

  register_queue->push(event);

}

//add an event to the map of events and their delegates
void EventManager::registerEvent(const EventType &type){

  event_delegates newdelegateList;
  event_map::const_iterator it = EventDelegateMap.find(type);

  if(it == EventDelegateMap.end()){
    EventDelegateMap.insert({type, newdelegateList});
  }

}

//register a delegate to an event type. Think of this like a person (class) is subscribing
// to a particular magazine (EvenetType) and is sending their address (EventDelegate)
void EventManager::registerDelegate(const EventDelegate& d, const string &eventDelegateIdentifier,
                  const EventType &type){
  //in case we do not find the event type we add it
  //to the map
  event_map::const_iterator it = EventDelegateMap.find(type);
  if(it == EventDelegateMap.end()){
    registerEvent(type);
  }
  //look for the delegate to see if it is already in the list
  event_delegates eventDelegatesEventMap = EventDelegateMap.at(type);
  //if it is not we add it to the list of event delegates
  if(eventDelegatesEventMap.find(eventDelegateIdentifier) == eventDelegatesEventMap.end()){
    //TODO the line below uses the copy constructor if there are issues with delegate
    //calls this could be it
    shared_ptr<EventDelegate> ed = make_shared<EventDelegate>(d);
    EventDelegateMap.at(type).insert({eventDelegateIdentifier,ed});
  }

}
//deregister a delegate to an event type
void EventManager::deregisterDelegate(const string &eventDelegateIdentifier, const EventType& type){
  //look for the delegate to see if it is already in the list
  event_delegates eventDelegatesEventMap = EventDelegateMap.at(type);
  if(!(eventDelegatesEventMap.find(eventDelegateIdentifier) == eventDelegatesEventMap.end())){
    EventDelegateMap.at(type).erase(eventDelegateIdentifier);
  }
}

void EventManager::triggerEvent(const EventInterface& event)
{
  //search to see if this event is registered
  auto delegateList = EventDelegateMap.find(event.getEventType());
  if(delegateList == EventDelegateMap.end()){
    return;
  }
  //the delegate list above is an iterator used to identify if an event even exists
  //the one below is the vector of event delegates
  auto actualDelegateMap = EventDelegateMap.at(event.getEventType());

  for(auto itr = actualDelegateMap.begin(); itr != actualDelegateMap.end(); itr++){
    //we dereference twice because the first gets us out of the iterator
    //and the second grabs the std::function from the shared pointer
    (*(*itr).second)(event);
  }

}

//iterate through all registered events and trigger them
void EventManager::processEvent(){
  std::swap(*process_queue, *register_queue);
  clear(register_queue);
  while(!process_queue->empty()){
    shared_ptr<EventInterface> event = process_queue->front();
    process_queue->pop();
    triggerEvent(*event);
  }
}

//used to clear the queue efficiently
void EventManager::clear( shared_ptr<event_queue> q )
{
   if(q -> size() != 0){
     q -> pop();
     //event_queue empty;
     //std::swap( *q, empty );

   }
}


void EventManager::dumpErrors(){
  ////cout << s.str();
}
