#pragma once

/*
 * Handles the ai for anything used by the player
 * for now that means the tower firing and the allied unit attacking
 * as well as whether the projectiles hit their targets
 */

 #include "EventManager.hpp"
 #include "TextLoader.hpp"
 #include "GameLogic.hpp"
 #include "PlayingScreenHeader.hpp"
 #include <chrono>

 using std::chrono::high_resolution_clock;
 using std::chrono::duration_cast;
 using std::chrono::nanoseconds;
 class AllyCompView{
 private:
   //Store the textLoader to make requests for strings and constants
   shared_ptr<TextLoader> textLoader;
   //event manager (used to register, deregister from events, and create them)
   shared_ptr<EventManager> eventManager;
   //logic of the game. handles mechanics
   shared_ptr<GameLogic> gameLogic;
   //Store the wave manager to get the current wave and information about the enemies being controlled.
   shared_ptr<WaveManager> waveManager;

   shared_ptr<PlayingScreenHeader> playingScreenHeader;

   bool coordsInsideTile(int row, int col,double x, double y);


 public:
   AllyCompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,shared_ptr<PlayingScreenHeader> playingScreenHeader);

   void updateAllyCompView(float deltaS);

   void updateProjectiles(float deltaS);

   void updateTowers(float deltaS);
 };
