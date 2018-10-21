

#include "UserView.hpp"

UserView::UserView(shared_ptr<GameLogic> gameLogic){
  
}

void UserView::updateUserView(float deltaS, sf::RenderWindow &game){
  this -> processEvents(game);
}


//TODO REMOVE WHEN EVENT SYSTEM IS SETUP
//TEMPORARY EVENT PROCESSOR
void UserView::processEvents(sf::RenderWindow  &game){
  // process events
  sf::Event Event;
  while(game.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed){
      game.close();
    }
 }
}
