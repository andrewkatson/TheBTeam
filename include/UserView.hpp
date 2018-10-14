#ifndef USERVIEW_H
#define USERVIEW_H
#include <SFML/Graphics.hpp>

class UserView{
private:
public:
  UserView();

  void updateUserView(float deltaS, sf::RenderWindow &game);

  void processEvents(sf::RenderWindow &game);
};

#endif
