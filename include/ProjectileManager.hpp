/*
 * ProjectileManager.hpp
 *
 * Purpose: Handle the life-cycles of all on-screen projectiles.
 *
 * @author Jeremy Elkayam
 */

#ifndef CSCI437_PROJECTILEMANAGER_HPP
#define CSCI437_PROJECTILEMANAGER_HPP

using namespace std;

#include <memory>
#include <vector>
#include <unordered_map>
#include "ActorInterface.hpp"
#include "EventManager.hpp"
#include "Events/ActorCreatedEvent.hpp"
#include "Events/ActorDestroyedEvent.hpp"
#include "Events/PlaySoundEvent.hpp"
#include "TextLoader.hpp"
#include <algorithm>
#include <chrono>

using std::max;
using std::chrono::high_resolution_clock ;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

class ProjectileManager {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Array storing the actors representing all projectiles.
  unordered_map<long long, shared_ptr<ActorInterface>> projectiles;

public:

  /*
   * Constructor. Initialize the projectile vector
   */
  ProjectileManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);
  ~ProjectileManager();

  /*
   * Register delegate methods
   */
  void registerDelegates();

  /*
   * Deregister delegate methods
   */
  void deregisterDelegates();

  /*
   * Register events that the projectile manager needs to listen for
   */
  void registerEvents();

  /*
   * Return the vector of projectiles stored by the class.
   *
   * @return a vector containing all of the manager's projectiles
   */
  unordered_map<long long, shared_ptr<ActorInterface>>& getAllProjectiles();

  /*
   * Handle an actor created event
   */
  void handleActorCreated(const EventInterface& event);

  /*
   * Checks if the actor destroyed is a projectile and then removes it from the map of fired projectiles
   */
  void handleActorDestroyed(const EventInterface& event);

  /*
   * Appends the given projectile to the manager's vector.
   */
  void addProjectile(shared_ptr<ActorInterface> projectile);

  /*
   * Removes the projectile at the given index.
   */
  void removeProjectile(long long ID);

  /*
   * Updates all projectiles under the manager.
   */
  void update(float deltaS);

  shared_ptr<ActorInterface> getProjectile(long long ID);

  void clearProjectiles();
};


#endif //CSCI437_PROJECTILEMANAGER_HPP
