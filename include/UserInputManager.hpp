#ifndef USERINPUTMANAGER_H
#define USERINPUTMANAGER_H
#include "EventManager.hpp"
#include "KeyPressEvent.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <chrono>

using std::shared_ptr;
using std::make_shared;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

class UserInputManager{
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
public:

  UserInputManager(shared_ptr<EventManager> eventManager);

  void registerEvents();

  void delegateMethod(const EventInterface& event);

  void processUserInput(sf::RenderWindow &game);

  void handleKeyPress(sf::Event &event);

};
#endif
