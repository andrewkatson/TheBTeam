/*
  Obstacle.hpp

  Purpose: Essentially a tower that when upgraded is actually removed

  @author Andrew Katson
 */

 #ifndef OBSTACLE_H
 #define OBSTACLE_H
 #include "TowerInterface.hpp"
class Obstacle : public TowerInterface{
public:
  Obstacle();

  void upgrade();
};
 #endif
