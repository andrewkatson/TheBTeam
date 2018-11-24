/*
 * ProjectileManager.cpp
 *
 * Purpose: Handle the life-cycles of all on-screen projectiles.
 *
 * @author Jeremy Elkayam
 */


#include "ProjectileManager.hpp"


ProjectileManager::ProjectileManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader) {
  //initialize the projectile vector
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> registerEvents();
  this -> registerDelegates();
}

ProjectileManager::~ProjectileManager(){
  this -> deregisterDelegates();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void ProjectileManager::registerDelegates(){
  //bind our delegate function for actor creations (specifically projectiles)
  EventManager::EventDelegate actorCreatedDelegate = std::bind(&ProjectileManager::handleActorCreated, this, _1);

  //make an event and get its type
  ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
  EventType actorCreatedEventType = actorCreatedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorCreatedDelegate, textLoader -> getString(string("IDS_ProjectileManager_ActorCreated")),actorCreatedEventType);
}

/*
 * Deregister the delegate methods for this class
 */
void ProjectileManager::deregisterDelegates(){

    //make an event and get its type
    ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
    EventType actorCreatedEventType = actorCreatedEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate( textLoader -> getString(string("IDS_ProjectileManager_ActorCreated")),actorCreatedEventType);
}

/*
 * any events created by this class must be registered with the
 * Event Manager
 */
void ProjectileManager::registerEvents(){
  //make a generic actor created event, get its type, and register it
  ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
  EventType actorCreatedEventType = actorCreatedEvent.getEventType();

  this -> eventManager -> registerEvent(actorCreatedEventType);
}

vector<shared_ptr<ActorInterface>>& ProjectileManager::getAllProjectiles(){
  return projectiles;
}


void ProjectileManager::handleActorCreated(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * ActorCreatedEvent type which allows us to access variables and methods
   * specific to ActorCreatedEvent
   */
  const ActorCreatedEvent* acEvent = static_cast<const ActorCreatedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a ActorCreatedEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  ActorCreatedEventData* acEventData = static_cast<ActorCreatedEventData*>((acEvent -> data).get());
  //get the identifier for whether this is a projectile or not
  bool isProjectile = acEventData -> isProjectile;

  if(isProjectile){
    //the projectile that was created
    shared_ptr<ActorInterface> firedProjectile = acEventData -> actorCreated;
    addProjectile(firedProjectile);
  }
}

void ProjectileManager::addProjectile(shared_ptr<ActorInterface> projectile){
  projectiles.push_back(projectile);
}

void ProjectileManager::removeProjectile(int projectile_index){
  projectiles.erase(projectiles.erase(projectiles.begin() + 1));
}

void ProjectileManager::update(float deltaS){

}
