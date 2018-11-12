/*
  Obstacle.hpp

  Purpose: Essentially a tower that when upgraded is actually removed

  @author Andrew Katson
 */

 #ifndef OBSTACLE_H
 #define OBSTACLE_H
 #include "TowerInterface.hpp"

class Obstacle : public TowerInterface{
protected:
  //int pair (used to assocaite a row and col)
  typedef pair<int,int> intPair;
public:
  Obstacle(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader);

  void upgrade();

  void initSprite();

  string getType(){return towerTypeID;}
  int getPrice(){return price;}
  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}
  int getXCoordinate(){return xCoordinate;}
  int getYCoordinate(){return yCoordinate;}
  void setXCoordinate(int xCor){xCoordinate = xCor;}
  void setYCoordinate(int yCor){yCoordinate = yCor;}
  bool canAttack(){return false;}
  void attack(shared_ptr<ActorInterface> enemyInRange){}
  void setProjectile(){}
  void setUpUnits(){}

  void update(float delta);
};
 #endif
