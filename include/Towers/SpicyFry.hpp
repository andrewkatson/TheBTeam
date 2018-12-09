#pragma once
#include "MeleeTower.hpp"
#include "TextLoader.hpp"
#include "../Units/SpicyFryUnit.hpp"
class SpicyFry : public MeleeTower{
private:
  static int priceMult;
public:
  SpicyFry(shared_ptr<TextLoader> textLoader, int maxMeleeUnits, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader, bool setUpUnits=true);

  virtual void upgrade();
  virtual void setUpUnits();
  void setProjectile(){}
  void setPos(intPair pos){this->row=pos.first;this->col=pos.second;}
  void setPos(int row, int col){this->row=row; this->col=col;}
  float getXCoordinate(){return xCoordinate;}
  float getYCoordinate(){return yCoordinate;}
  void setXCoordinate(float xCor){xCoordinate = xCor;}
  void setYCoordinate(float yCor){yCoordinate = yCor;}
  bool canAttack(){return MeleeTower::canAttack();}
  void attack(shared_ptr<ActorInterface> enemyInRange, float delta){MeleeTower::attack(enemyInRange, delta);}
  void update(float delta){MeleeTower::update(delta);}
  shared_ptr<vector<int>> getStatistics(){return MeleeTower::getStatistics();}

  int getPrice(){return this->price*SpicyFry::priceMult;}
  void setPriceMult(int priceMult){SpicyFry::priceMult=priceMult;}
};
