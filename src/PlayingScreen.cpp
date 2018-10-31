#include "PlayingScreen.hpp"

PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}

void PlayingScreen::draw(sf::RenderWindow &window){

}
