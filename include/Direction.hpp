#ifndef DIRECTION_H
#define DIRECTION_H
#include <vector>

using std::vector;
class Direction{

public:
  enum Directions  {Left, Right, Up, Down};
  Direction();
  Direction(int d);

  Direction::Directions intToDirection(int d);
  int directionToInt(Direction::Directions);

  Direction::Directions oppositeDirection(Direction::Directions d);

  vector<Direction::Directions> allOtherDirections(Direction::Directions d);

private:
  Directions facing;
};
#endif
