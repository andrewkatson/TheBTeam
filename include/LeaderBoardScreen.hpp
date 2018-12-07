#pragma once
#include "Screen.hpp"
#include "Button.hpp"
//#define LIBSSH_STATIC 1
//#include <../libssh/include/libssh/libssh.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <array>
#include <cstdio>
/*
 * Handles an ssh to a basic server to check your stats against those
 * @author Andrew Katson
 */

class LeaderBoardScreen : public Screen{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Store the Event Manger for the game that receives and distributes irregular
  //game events
  shared_ptr<EventManager> eventManager;
  unique_ptr<Button> backButton;
  //size of window
  int windowX;
  int windowY;
  //our ssh session
  //ssh_session my_ssh_session;
  //whether we made a sucessful connection or not
  bool connection;

  sf::Font mainFont;
public:

  LeaderBoardScreen(int windowX, int windowY, shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager);

  ~LeaderBoardScreen();

  void initBackButton();

  void registerDelegates();
  void deregisterDelegates();

  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);

  void tryToConnect();
  std::string exec(const char* cmd);
  void getLeaderBoard();
  void getLocalLeaderBoard();
  void endConnect();

  void draw(sf::RenderWindow& window);
 };
