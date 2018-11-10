#pragma once
#include "RangeTower.hpp"
#include "../Projectiles/SodaProjectile.hpp"
class Soda : public RangeTower{
public:
  Soda(shared_ptr<TextLoader> textLoader,  shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);

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
