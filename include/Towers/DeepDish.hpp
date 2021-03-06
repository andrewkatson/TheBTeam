#pragma once
#include "RangeTower.hpp"
#include "../Projectiles/DeepDishProjectile.hpp"
class DeepDish : public RangeTower{
private:
  shared_ptr<ActorInterface> createProjectile();
  static int priceMult;
public:
  DeepDish(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);

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
  bool canAttack(){return RangeTower::canAttack();}
  void attack(shared_ptr<ActorInterface> enemyInRange, float delta){RangeTower::attack(enemyInRange, delta);}
  void update(float delta){RangeTower::update(delta);}
  int getPrice(){return this->price*DeepDish::priceMult;}
  void setPriceMult(int priceMult){DeepDish::priceMult=priceMult;}

  shared_ptr<vector<int>>  getStatistics(){return RangeTower::getStatistics();}
};
