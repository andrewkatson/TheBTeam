#pragma once

#include "Obstacle.hpp"

class CafeteriaTable : public Obstacle{
private:

public:
  CafeteriaTable(shared_ptr<TextLoader> textLoader,shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);

  void setProjectile(){}
  void setUpUnits(){}

  void setPos(intPair pos){this->row=pos.first;this->col=pos.second;}
  void setPos(int row, int col){this->row=row; this->col=col;}
  int getXCoordinate(){return xCoordinate;}
  int getYCoordinate(){return yCoordinate;}
  void setXCoordinate(int xCor){xCoordinate = xCor;}
  void setYCoordinate(int yCor){yCoordinate = yCor;}
  bool canAttack(){return false;}
  void attack(shared_ptr<ActorInterface> enemyInRange){}
  void update(float delta){Obstacle::update(delta);}
  shared_ptr<vector<int>>  getStatistics(){return Obstacle::getStatistics();}
};
