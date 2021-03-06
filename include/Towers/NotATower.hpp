#pragma once

/*
 * A stand in for a tile without a tower
 * @author Andrew Katson
 */

#include "RangeTower.hpp"
#include "../Projectiles/CheesePizzaProjectile.hpp"
class NotATower : public RangeTower{
public:
  NotATower(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);

  void upgrade();

  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  void setProjectile();
  void setUpUnits(){}
  void setPos(intPair pos){this->row=pos.first;this->col=pos.second;}
  void setPos(int row, int col){this->row=row; this->col=col;}
  float getXCoordinate(){return xCoordinate;}
  float getYCoordinate(){return yCoordinate;}
  void setXCoordinate(float xCor){xCoordinate = xCor;}
  void setYCoordinate(float yCor){yCoordinate = yCor;}
  bool canAttack(){return false;}
  void attack(shared_ptr<ActorInterface> enemyInRange, float delta){}
  void update(float delta){}
  shared_ptr<vector<int>> getStatistics(){return RangeTower::getStatistics();}
};
