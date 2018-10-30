/*
  GameState.hpp

  Purpose: Store the current state of the game and provide methods to alter or
           get the current state of the game. Also stores game states.

  @author Jeremy Elkayam
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <memory>
#include <vector>
#include "EventManager.hpp"

using namespace std;


/*
  The states that the game can have.
  Playing: Gameplayis currently taking place.
  Title: The game is displaying the title screen.

  TODO - add states as needed.
*/
enum class State{ MainMenu, OptionsMenu, Playing, BuyTower, Restart};

class GameState{
private:

  //The game's current state.
  State currentState;

  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
public:

  /*
    Constructor for the GameState class. Instantiate the current state to the
    game's starting state.
   */
  GameState(shared_ptr<EventManager> eventManager);

  /*
    Set the current state to the state specified.

    @param newState The state to set the game's current state to.
   */
  void setState(State newState);


  /*
    Returns the state of the game.

    @return A State enum containing the game's current state.
   */
  State getState(){return currentState;}
};

#endif
