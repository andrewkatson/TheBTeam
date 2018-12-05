#ifndef GAME_H
#define GAME_H
#include "GameLogic.hpp"
#include "UserView.hpp"
#include "CompView.hpp"
#include "AllyCompView.hpp"
#include "TextLoader.hpp"
#include "TextureLoader.hpp"
#include "CollisionCallback.hpp"
#include "Events/SpeedChangeEvent.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <iostream>

using std::cout;
using std::shared_ptr;
using std::unique_ptr;
using std::shared_ptr;
class Game {
private:
shared_ptr<GameLogic> gameLogic;
shared_ptr<EventManager> eventManager;

unique_ptr<UserView> userView;
unique_ptr<CompView> compView;
unique_ptr<AllyCompView> allyCompView;

float speedScale;
public:
  shared_ptr<TextLoader> textLoader;
  shared_ptr<TextureLoader> textureLoader;
  //Box2d World and Body
  shared_ptr<b2World> world;
  shared_ptr<b2Body> body;
  CollisionCallback collisionCallbackInstance;
  Game();

  void setUpTextLoader();

  void initGame(sf::RenderWindow &game);

  void updateGame(float deltaS, sf::RenderWindow &game);

  void registerDelegates();
  void deregisterDelegates();

  void handleSpeedChange(const EventInterface& event);
};

#endif
