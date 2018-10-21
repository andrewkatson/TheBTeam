#include "UserView.hpp"
#include "Player.cpp"

UserView::UserView(shared_ptr<GameLogic> gameLogic){
  
}

void UserView::updateUserView(float deltaS, sf::RenderWindow &game){
  this -> processEvents(game);
}


//TODO - REMOVE WHEN EVENT SYSTEM IS SETUP
//TEMPORARY EVENT PROCESSOR
void UserView::processEvents(sf::RenderWindow  &game){
  // process events
  sf::Event Event;
  while(game.pollEvent(Event))
  {

    // Main Screen
    //if(sf::Event::Keypressed){
    //game.close();
    // Options Screen
    // if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::O))
    //game.close();
    // Game Screen
    //if(Event.type == sf::Event::Closed){
	// If Player selects valid unit tile with no units currently placed 
	//draw a button that will direct them to the purchase screen
	//if player selects a tile that currently has a tower direct them to an upgrade screen
    // Restart Screen
    //if(((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)) OR (Player.hitpoints == 0)){
    // One Button with the option of returning to the main menu;
	
    // Buy Tower Screen
	// Import tower textures and display alongside name, price. If tower is selected check
	// player.balance is >= than tower cost then place tower in previosuly selected spot 

    if(Event.type == sf::Event::Closed){
      game.close();
    }
 }
}