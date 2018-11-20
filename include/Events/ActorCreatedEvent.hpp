#pragma once

/*
 * When an actor is created (in particular a projectile)
 * it is passed along with an event so that the correct manager class
 * can take it and add it to the list of objects it has access to
 * @author Andrew Katson
 */

 #include "EventType.hpp"
 #include "EventDataInterface.hpp"
 #include "ActorCreatedEventData.hpp"
 #include "EventInterface.hpp"
 #include <memory>
 #include <string>

 using std::string;
 using std::unique_ptr;


 class ActorCreatedEvent : public EventInterface{
 public:
   unique_ptr<EventDataInterface> data;
   static const EventType eventType;

   ActorCreatedEvent();
   ActorCreatedEvent(shared_ptr<ActorInterface> actorCreated, bool isProjectile, float timeStamp);

   const EventType& getEventType() const;
   float GetTimeStamp() const;
 };
