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

  string getType(){return typeID;}
  int getPrice(){return price;}
  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}
  float getXCoordinate(){return xCoordinate;}
  float getYCoordinate(){return yCoordinate;}
  void setXCoordinate(float xCor){xCoordinate = xCor;}
  void setYCoordinate(float yCor){yCoordinate = yCor;}
  bool canAttack(){return false;}
  void attack(shared_ptr<ActorInterface> enemyInRange){}
  void setProjectile(){}
  void setUpUnits(){}

  void update(float delta);
  shared_ptr<vector<int>>  getStatistics(){shared_ptr<vector<int>> emptyVec = make_shared<vector<int>>(); return emptyVec;}
};
 #endif
