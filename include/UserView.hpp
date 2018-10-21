#ifndef USERVIEW_H
#define USERVIEW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameLogic.hpp"

using std::shared_ptr;
class UserView{
private:

public:
  UserView(shared_ptr<GameLogic> gameLogic);

  void updateUserView(float deltaS, sf::RenderWindow &game);

  void processEvents(sf::RenderWindow &game);
};

#endif
