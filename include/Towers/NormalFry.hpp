#pragma once
#include "TextLoader.hpp"
#include "MeleeTower.hpp"
#include "../include/Units/NormalFryUnit.hpp"

class NormalFry : public MeleeTower{
private:
public:
  NormalFry(shared_ptr<TextLoader> textLoader, string towerTypeID,int maxMeleeUnits, shared_ptr<EventManager> eventManager);

  virtual void upgrade();
  virtual void setUpUnits();
  void setProjectile(){}
  void setPos(intPair pos){this->row=pos.first;this->col=pos.second;}
  void setPos(int row, int col){this->row=row; this->col=col;}
  int getXCoordinate(){return xCoordinate;}
  int getYCoordinate(){return yCoordinate;}
  void setXCoordinate(int xCor){xCoordinate = xCor;}
  void setYCoordinate(int yCor){yCoordinate = yCor;}
  bool canAttack(){return MeleeTower::canAttack();}
  void attack(shared_ptr<ActorInterface> enemyInRange){MeleeTower::attack(enemyInRange);}
  void update(float delta){MeleeTower::update(delta);}
};
