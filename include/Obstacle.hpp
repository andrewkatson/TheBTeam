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
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
public:
  Obstacle();

  void upgrade();

  string getType(){return towerTypeID;}
  int getPrice(){return price;}
  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}
};
 #endif
