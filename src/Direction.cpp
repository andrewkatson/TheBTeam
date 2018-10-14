#include "Direction.hpp"

Direction::Direction(){
  this -> facing = intToDirection(3);
}

Direction::Direction(int d){
  this -> facing = intToDirection(d);
}

//return the enum direction corresponding to the integer passed
Direction::Directions Direction::intToDirection(int d){
  switch(d){
    case 0:
      return Directions::Left;
    case 1:
      return Directions::Right;
    case 2:
      return Directions::Top;
    case 3:
    default:
      return Directions::Bottom;
  }
}

//return the int corresponding to the Directions enum passed
int Direction::directionToInt(Direction::Directions d){
  switch(d){
    case Directions::Left:
      return 0;
    case Directions::Right:
      return 1;
    case Directions::Top:
      return 2;
    case Directions::Bottom:
    default:
      return 3;
  }
}

//return the direction opposite the one passed
Direction::Directions Direction::oppositeDirection(Direction::Directions d) {
  switch(d){
    case Directions::Left:
      return Directions::Right;
    case Directions::Right:
      return Directions::Left;
    case Directions::Top:
      return Directions::Bottom;
    case Directions::Bottom:
    default:
      return Directions::Top;
  }
}

//return a vector with the three directions that are not the one passed
vector<Direction::Directions> Direction::allOtherDirections(Direction::Directions d) {
  vector<Direction::Directions> otherDirections;
  for(int direct = Left; direct != Bottom + 1; direct++){
    Directions direction = static_cast<Directions>(direct);
    if(direction != d){
      otherDirections.push_back(direction);
    }
  }
  return otherDirections;
}
