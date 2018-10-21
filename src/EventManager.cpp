
/*
  EventManager.cpp

  Purpose: Handles loading and execution of all events within the game.

  @author Mei-Ting Song
*/

#include "EventManager.hpp"


EventManager::EventManager(){
  event_queue a;
  event_queue b;
  queues.push_back(a);
  queues.push_back(b);

  process_queue = &queues.at(0);
  register_queue = &queues.at(1);
}

EventManager::~EventManager(){
  process_queue = nullptr;
  register_queue = nullptr;
}

//add an event to the queue of registered events
void EventManager::queueEvent(shared_ptr<EventInterface> event){
  register_queue->push(event);
}

//register a delegate to an event type. Think of this like a person (class) is subscribing
// to a particular magazine (EvenetType) and is sending their address (EventDelegate)
void EventManager::registerDelegate(const EventDelegate& d,const EventType &type){
  event_delegates eventList = EventDelegateMap.at(type);
  if(!find(eventList, d)){
    eventList.push_back(make_shared<EventDelegate>(d));
  }
}
//deregister a delegate to an event type
void EventManager::deregisterDelegate(const EventDelegate& d, const EventType& type){
  event_delegates eventList = EventDelegateMap.at(type);
  int isFound = find(eventList, d);
  if(isFound){
    eventList.erase(eventList.begin() + isFound);
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
  auto actualDelegateList = EventDelegateMap.at(event.getEventType());
  for(auto itr = actualDelegateList.begin(); itr != actualDelegateList.end(); itr++){
    //we dereference twice because the first gets us out of the iterator
    //and the second grabs the std::function from the shared pointer
    (*(*itr))(event);
  }

}

//iterate through all registered events and trigger them
void EventManager::processEvent(){
  std::swap(process_queue, register_queue);
  clear(*register_queue);

  while(!process_queue->empty()){
    shared_ptr<EventInterface> event = process_queue->front();
    process_queue->pop();

    triggerEvent(*event);
  }
}

/*
 * search the passed list of event delegates for one and if it is not found
 * then return 0 (false), else return the index it is at (true)
 */
int EventManager::find(event_delegates &eventDelegateList,  const EventDelegate& toFind){

  int index = 0;
  for(auto delegate: eventDelegateList){
    if(getAddress(*delegate) == getAddress(toFind)){
      return index;
    }
    index++;
  }
  return 0;
}

// get the address of the function pointed to by the passed std::function object
template<typename T, typename... U>
size_t EventManager::getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}

//used to clear the queue efficiently
void EventManager::clear( event_queue &q )
{
   event_queue empty;
   std::swap( q, empty );
}
