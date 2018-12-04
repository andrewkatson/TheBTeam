/*
  RangeTower.hpp

  Purpose: A defensive tower that fires missiles at enemy npc actors

  @author Andrew Katson
 */

 #ifndef RANGETOWER_H
 #define RANGETOWER_H
#include "TowerInterface.hpp"
#include "Projectile.hpp"
#include "TextLoader.hpp"
#include "Events/ActorCreatedEvent.hpp"
#include <assert.h>
#include <memory>
#include <chrono>

using std::shared_ptr;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::microseconds;
class RangeTower : public TowerInterface{
protected:

//int pair (used to assocaite a row and col)
typedef pair<int,int> intPair;
//the specfic type of projectile shot by this tower
shared_ptr<Projectile> currentProjectile;
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//the rate that this tower can fire projectiles at
long long rateOfFire;
//the time that the last shot was fired
long long lastTimeFired;
protected:
  virtual shared_ptr<ActorInterface> createProjectile();
public:
  RangeTower(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  void initSprite();
  void update(float delta);
  virtual void upgrade();

  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  virtual void setProjectile();

  /*
   * @return the price of the tower
   */
  int getPrice();

  string getType(){return typeID;}
  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}
  float getXCoordinate(){return xCoordinate;}
  float getYCoordinate(){return yCoordinate;}
  void setXCoordinate(float xCor){xCoordinate = xCor;}
  void setYCoordinate(float yCor){yCoordinate = yCor;}

  void setUpUnits(){}

  bool canAttack();
  void attack(shared_ptr<ActorInterface> enemyInRange, float delta);
  void modifyToIncludeUpgrades(shared_ptr<ActorInterface> firedProjectile);
  void calcAttackVector(shared_ptr<ActorInterface> projectileToFire, shared_ptr<ActorInterface> enemyInRange);

  shared_ptr<vector<int>>  getStatistics();

  //gettters used for the upgrading system
  int getRadius(){return radius;}
  int getRateOfFire(){return rateOfFire;}
  int getProjectileDamage(){return currentProjectile->getDamage();}
  int getProjectileArmorPenetration(){return currentProjectile->getArmorPenetration();}
  int getProjectileAreaOfEffect(){return currentProjectile->getRadius();}

  //setters for the upgrade system
  void updateRadius(int newRadius){radius = newRadius;}
  void updateRateOfFire(int newRateOfFire){rateOfFire = newRateOfFire;}
  void updateProjectileDamage(int newProjectileDamage){currentProjectile->updateDamage(newProjectileDamage);}
  void updateProjectileArmorPenetration(int newProjectileArmorPenetration){currentProjectile->updateArmorPenetration(newProjectileArmorPenetration);}
  void updateProjectileAreaOfEffect(int newProjectileAreaOfEffect){currentProjectile->updateRadius(newProjectileAreaOfEffect);}


};

 #endif
