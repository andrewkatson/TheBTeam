/*
  EventManager.hpp

  Purpose: Handles loading and execution of all events within the game.

  @author Mei-Ting Song, Andrew Katson
*/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <functional>
#include <memory>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include "EventInterface.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::cout;
using std::endl;
using std::unordered_map;
using std::size_t;
using std::queue;
class EventManager{
public:
  typedef std::function<void(const EventInterface&)> EventDelegate;
  typedef std::queue<shared_ptr<EventInterface>> event_queue;

  typedef std::vector<shared_ptr<EventDelegate>> event_delegates;
  typedef std::unordered_map<EventType, event_delegates> event_map;

  EventManager();
  ~EventManager();

  void queueEvent(shared_ptr<EventInterface> event);

  void registerEvent(const EventType &type);

  void registerDelegate(const EventDelegate& d, const EventType& type);

  void deregisterDelegate(const EventDelegate& d, const EventType& type);

  void processEvent();

private:
  void triggerEvent(const EventInterface& event);

  int find(event_delegates &eventDelegateList,  const EventDelegate& toFind);

  void clear(event_queue &q);

  std::vector<event_queue> queues;
  event_queue *process_queue;
  event_queue *register_queue;

  event_map EventDelegateMap;
};

#endif
