#ifndef GAME_H
#define GAME_H
#include "GameLogic.hpp"
#include "UserView.hpp"
#include "CompView.hpp"
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
unique_ptr<UserView> userView;
unique_ptr<CompView> compView;
public:

  Game();

  void initGame(sf::RenderWindow &game);

  void updateGame(float deltaS, sf::RenderWindow &game);
};

#endif
