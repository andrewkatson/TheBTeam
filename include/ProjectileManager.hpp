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

class ProjectileManager {
public:
  //Array storing the actors representing all projectiles.
  vector<shared_ptr<ActorInterface>> projectiles;
private:

  /*
   * Constructor. Initialize the projectile vector
   */
  ProjectileManager();

  /*
   * Return the vector of projectiles stored by the class.
   *
   * @return a vector containing all of the manager's projectiles
   */
  vector<shared_ptr<ActorInterface>> getProjectiles();

  /*
   * Appends the given projectile to the manager's vector.
   */
  void addProjectile(shared_ptr<ActorInterface> ikiiprojectile);

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
