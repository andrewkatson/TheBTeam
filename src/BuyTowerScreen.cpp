#include "BuyTowerScreen.hpp"

BuyTowerScreen::BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}

void BuyTowerScreen::draw(sf::RenderWindow &window){

}
/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void BuyTowerScreen::registerDelegates(){

}
/*
 * Deregisetr the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void BuyTowerScreen::deregisterDelegates(){

}
