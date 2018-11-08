#pragma once
#include "RangeTower.hpp"
#include "../Projectiles/EnergyDrinkProjectile.hpp"
class EnergyDrink : public RangeTower{
public:
  EnergyDrink(shared_ptr<TextLoader> textLoader, string towerTypeID, shared_ptr<EventManager> eventManager);

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
  bool canAttack(){return RangeTower::canAttack();}
  void attack(shared_ptr<ActorInterface> enemyInRange){RangeTower::attack(enemyInRange);}
  void update(float delta){RangeTower::update(delta);}
};
