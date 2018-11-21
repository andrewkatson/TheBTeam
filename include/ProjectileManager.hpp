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
#include "ActorInterface.hpp"
#include "EventManager.hpp"
#include "Events/ActorCreatedEvent.hpp"
#include "TextLoader.hpp"

class ProjectileManager {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Array storing the actors representing all projectiles.
  vector<shared_ptr<ActorInterface>> projectiles;
public:

  /*
   * Constructor. Initialize the projectile vector
   */
  ProjectileManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  /*
   * Register delegate methods
   */
  void registerDelegates();

  /*
   * Register events that the projectile manager needs to listen for
   */
  void registerEvents();

  /*
   * Return the vector of projectiles stored by the class.
   *
   * @return a vector containing all of the manager's projectiles
   */
  vector<shared_ptr<ActorInterface>> getProjectiles();

  /*
   * Handle an actor created event
   */
  void handleActorCreated(const EventInterface& event);

  /*
   * Appends the given projectile to the manager's vector.
   */
  void addProjectile(shared_ptr<ActorInterface> projectile);

  /*
   * Removes the projectile at the given index.
   */
  void removeProjectile(int projectile_index);

  /*
   * Updates all projectiles under the manager.
   */
  void update(float deltaS);
};


#endif //CSCI437_PROJECTILEMANAGER_HPP
