#include "UserView.hpp"
#include <memory>

using namespace std;

#define textNormal = 255, 255, 255
#define textHighlight = 255, 200, 10
#define windowX 800
#define windowY 600

UserView::UserView(shared_ptr<GameLogic> gameLogic){

  font.loadFromFile("fonts/PWYummyDonuts.ttf");

  //Main Menu

  title.setFont(font);
  title.setFillColor(sf::Color(255,255,255,255));
  title.setString("Food Fight");
  title.setCharacterSize(60);
  title.setPosition(350.f, 100.f);

  playButton = unique_ptr<Button>(new Button(windowX, windowY, 1, "Play"));

  optionButton = unique_ptr<Button>(new Button(windowX, windowY, 2, "Options"));

  exitButton = unique_ptr<Button>(new Button(windowX, windowY, 3, "Exit"));

  //Options menu


  backButton = unique_ptr<Button>(new Button(windowX, windowY, 3, "Back"));

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
