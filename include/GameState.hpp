/*
  GameState.hpp

  Purpose: Store the current state of the game and provide methods to alter or
           get the current state of the game. Also stores game states. 
  
  @author Jeremy Elkayam
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

using namespace std;

class GameState{
private:
  int currentState;
  vector<int> gameStates;
  
public:
  GameState();
  
  void setState(int new_state);
  int getState(){return currentState;}  
};

#endif
