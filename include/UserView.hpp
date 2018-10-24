#ifndef USERVIEW_H
#define USERVIEW_H
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "GameLogic.hpp"


class UserView{
private:
  sf::Font font;
  sf::Text title;

  unique_ptr<Button> playButton,optionButton,exitButton,backButton;
public:
  UserView(shared_ptr<GameLogic> gameLogic);

  void updateUserView(float deltaS, sf::RenderWindow &game);

  void processEvents(sf::RenderWindow &game);
};

#endif
