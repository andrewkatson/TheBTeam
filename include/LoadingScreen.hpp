#pragma once
#include "Screen.hpp"
#include <chrono>
#include <stdlib.h> 
#include <time.h>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::nanoseconds;
/*
 * Loading Screen to display after a map is generated
 * @author Andrew Katson
 */

class LoadingScreen : public Screen{
private:
  //hint to display
  sf::Text hint;
  //main font used
  sf::Font mainFont;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Store the Event Manger for the game that receives and distributes irregular
  //game events
  shared_ptr<EventManager> eventManager;
  //size of window
  int windowX;
  int windowY;

  //all the hints
  vector<string> hints;
  int currentHint;

  //show loading screen for
  long long timeStarted;
public:

  LoadingScreen(int windowX, int windowY, shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager);

  ~LoadingScreen();
  void loadHints();

  void registerDelegates();
  void deregisterDelegates();

  void handleMapGenerated(const EventInterface& event);

  void getNewHint();

  void draw(sf::RenderWindow& window);

  void changeToPlaying();
};
