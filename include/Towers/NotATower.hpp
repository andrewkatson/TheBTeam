#pragma once

/*
 * A stand in for a tile without a tower
 * @author Andrew Katson
 */

#include "RangeTower.hpp"
#include "../include/Projectiles/CheesePizzaProjectile.hpp"
class NotATower : public RangeTower{
public:
  NotATower(shared_ptr<TextLoader> textLoader,string towerTypeID, shared_ptr<EventManager> eventManager);

  void upgrade();

  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  void setProjectile();
  void setUpUnits(){}
  void setPos(intPair pos){this->row=pos.first;this->col=pos.second;}
  void setPos(int row, int col){this->row=row; this->col=col;}
  int getXCoordinate(){return xCoordinate;}
  int getYCoordinate(){return yCoordinate;}
  void setXCoordinate(int xCor){xCoordinate = xCor;}
  void setYCoordinate(int yCor){yCoordinate = yCor;}
  bool canAttack(){return false;}
  void attack(shared_ptr<ActorInterface> enemyInRange){}
  void update(float delta){RangeTower::update(delta);;}
};
