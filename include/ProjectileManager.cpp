//
// Created by jeremy on 10/20/18.
//


#include "ProjectileManager.hpp"

vector<shared_ptr<ActorInterface>> ProjectileManager::getProjectiles(){
  return projectiles;
}

void ProjectileManager::addProjectile(shared_ptr<ActorInterface> projectile){
  projectiles.push_back(projectile);
}

void ProjectileManager::removeProjectile(int projectile_index){
  projectiles.erase(projectiles.erase(projectiles.begin() + 1));
}

void ProjectileManager::update(float deltaS){

}

ProjectileManager::ProjectileManager() {
  //initialize the projectile vector
}