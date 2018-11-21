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

class RangeTower : public TowerInterface{
protected:

//int pair (used to assocaite a row and col)
typedef pair<int,int> intPair;
//the specfic type of projectile shot by this tower
shared_ptr<Projectile> currentProjectile;
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//the rate that this tower can fire projectiles at
int rateOfFire;
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

  string getType(){return towerTypeID;}
  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}
  int getXCoordinate(){return xCoordinate;}
  int getYCoordinate(){return yCoordinate;}
  void setXCoordinate(int xCor){xCoordinate = xCor;}
  void setYCoordinate(int yCor){yCoordinate = yCor;}

  void setUpUnits(){}

  bool canAttack();
  void attack(shared_ptr<ActorInterface> enemyInRange);
  void calcAttackVector(shared_ptr<ActorInterface> projectileToFire, shared_ptr<ActorInterface> enemyInRange);

  shared_ptr<vector<int>>  getStatistics();
};

 #endif
