/*
 * ProjectileManager.cpp
 *
 * Purpose: Handle the life-cycles of all on-screen projectiles.
 *
 * @author Jeremy Elkayam
 */


#include "ProjectileManager.hpp"


ProjectileManager::ProjectileManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader,shared_ptr<b2World> world) {
  //initialize the projectile vector
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> registerEvents();
  this -> registerDelegates();
  this -> world = world;
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

  //bind our delegate function for actor destructions (specifically projectiles)
  EventManager::EventDelegate actorDestroyedDelegate = std::bind(&ProjectileManager::handleActorDestroyed, this, _1);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorDestroyedDelegate, textLoader -> getString(string("IDS_Projectile_Manager_Actor_Destroyed")),actorDestroyedEventType);
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

    //make an event and get its type
    ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
    EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Projectile_Manager_Actor_Destroyed")),actorDestroyedEventType);
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

unordered_map<long long, shared_ptr<ActorInterface>>& ProjectileManager::getAllProjectiles(){
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
    cout << "yay projectile !" << endl;
    cout << "id " << firedProjectile->getID() << endl;
    addProjectile(firedProjectile);
  }
}

void ProjectileManager::handleActorDestroyed(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * ActorDestroyedEvent type which allows us to access variables and methods
   * specific to ActorDestroyedEvent
   */
  const ActorDestroyedEvent* adEvent = static_cast<const ActorDestroyedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a ActorDestroyedEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  ActorDestroyedEventData* adEventData = static_cast<ActorDestroyedEventData*>((adEvent -> data).get());
  //get the id of the actor to check if it was a projectile
  long long actorDestroyedID = adEventData -> actorID;

  cout << "remove ! " << actorDestroyedID << endl;
  if(projectiles.find(actorDestroyedID) != projectiles.end()){
    removeProjectile(actorDestroyedID);
  }
}

void ProjectileManager::addProjectile(shared_ptr<ActorInterface> projectile){
  projectiles.insert({projectile->getID(), projectile});
}

void ProjectileManager::removeProjectile(long long ID){
  cout << "get hit" << endl;
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  shared_ptr<EventInterface> playSound = make_shared<PlaySoundEvent>("",textLoader->getString("IDS_Unit_Hit_By_Projectile_Noise"),nowInNano);

  eventManager->queueEvent(playSound);

  projectiles.erase(ID);
}

void ProjectileManager::update(float deltaS){

}

//Used ID to grab projectile
shared_ptr<ActorInterface> ProjectileManager::getProjectile(long long ID){
  if(projectiles.find(ID) == projectiles.end()){
    cout << " oh no " << ID << endl;
    assert(true==false);
  }
  return projectiles.at(ID);
}
