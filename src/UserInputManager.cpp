#include "UserInputManager.hpp"
/*
 * Receive user input and make events for them
 * @author Andrew Katson
 */
UserInputManager::UserInputManager(shared_ptr<EventManager> eventManager){
  this -> eventManager = eventManager;
  this -> registerEvents();
}

/*
 * any events created by this class must be registered with the
 * Event Manager
 */
 void UserInputManager::registerEvents(){
   //make a generic key press event, get its type, and register it
   KeyPressEvent keyPressEvent = KeyPressEvent();
   EventType keyPressEventType = keyPressEvent.getEventType();

   this -> eventManager -> registerEvent(keyPressEventType);
   //make a generic mouse press event, get its type, and register it
   MousePressEvent mousePressEvent = MousePressEvent();
   EventType mousePressEventType = mousePressEvent.getEventType();
   this -> eventManager -> registerEvent(mousePressEventType);
 }

/*
 * receive user input from keys or mouse and create a relevant event
 * @param game: the game window
 */
void UserInputManager::processUserInput(sf::RenderWindow &game){

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
      //the time object of the class
      auto now = high_resolution_clock::now();
      //the actual count in nanoseconds for the time
      auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

      shared_ptr<EventInterface> closeKey = make_shared<KeyPressEvent>(string("CLOSE"), nowInNano);

      this -> eventManager -> queueEvent(closeKey);

    }
   else if(Event.type == sf::Event::KeyPressed){
     handleKeyPress(Event);
   }
   else if(Event.type == sf::Event::MouseButtonPressed){
     handleMousePress(Event);
   }
 }
}

/*
 * Handle a key pressed by the user and make a game event
 * @param event: the sfml event indicating a key was pressed
 */
 void UserInputManager::handleKeyPress(sf::Event &event){
   //the time object of the class
   auto now = high_resolution_clock::now();
   //the actual count in nanoseconds for the time
   auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
   if(event.key.code == sf::Keyboard::Q){
     shared_ptr<EventInterface> qKey = make_shared<KeyPressEvent>(string("Q"), nowInNano);

     this -> eventManager -> queueEvent(qKey);
   }
   //S used for start when you want to play the game (could have been p but distinction needs to be made between pressing on main
   // menu and the game screen because p is also pause)
   else if(event.key.code == sf::Keyboard::S){
     shared_ptr<EventInterface> sKey = make_shared<KeyPressEvent>(string("S"), nowInNano);

     this -> eventManager -> queueEvent(sKey);
   }
   else if(event.key.code == sf::Keyboard::O){
     shared_ptr<EventInterface> oKey = make_shared<KeyPressEvent>(string("O"), nowInNano);

     this -> eventManager -> queueEvent(oKey);
   }
   else if(event.key.code == sf::Keyboard::B){
     shared_ptr<EventInterface> bKey = make_shared<KeyPressEvent>(string("B"), nowInNano);

     this -> eventManager -> queueEvent(bKey);
   }
   else if(event.key.code == sf::Keyboard::H){
     shared_ptr<EventInterface> hKey = make_shared<KeyPressEvent>(string("H"), nowInNano);

     this -> eventManager -> queueEvent(hKey);
   }
   else if(event.key.code == sf::Keyboard::Left){
     shared_ptr<EventInterface> leftArrow = make_shared<KeyPressEvent>(string("Left"), nowInNano);

     this -> eventManager -> queueEvent(leftArrow);
   }
   else if(event.key.code == sf::Keyboard::Right){
     shared_ptr<EventInterface> rightArrow = make_shared<KeyPressEvent>(string("Right"), nowInNano);

     this -> eventManager -> queueEvent(rightArrow);
   }
   else if(event.key.code == sf::Keyboard::Up){
     shared_ptr<EventInterface> upArrow = make_shared<KeyPressEvent>(string("Up"), nowInNano);

     this -> eventManager -> queueEvent(upArrow);
   }
   else if(event.key.code == sf::Keyboard::Down){
     shared_ptr<EventInterface> downArrow = make_shared<KeyPressEvent>(string("Down"), nowInNano);

     this -> eventManager -> queueEvent(downArrow);
   }
   else if(event.key.code == sf::Keyboard::Return){
     shared_ptr<EventInterface> enterKey = make_shared<KeyPressEvent>(string("Enter"), nowInNano);

     this -> eventManager -> queueEvent(enterKey);
   }
 }

 /*
  * Handle a mouse press by the user and make a game event
  * @param event: the sfml event indicating the mouse was pressed
  */
 void UserInputManager::handleMousePress(sf::Event &event){
   //the time object of the class
   auto now = high_resolution_clock::now();
   //the actual count in nanoseconds for the time
   auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
   //x coordinate of the mouse
   float mouseX = event.mouseButton.x;
   //y coordinate of the mouse
   float mouseY = event.mouseButton.y;

   //Handle left mouse button
   if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
     shared_ptr<EventInterface> leftMouse = make_shared<MousePressEvent>(string("Left"), mouseX, mouseY, nowInNano);

     this -> eventManager -> queueEvent(leftMouse);
   }
   else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
     shared_ptr<EventInterface> rightMouse = make_shared<MousePressEvent>(string("Right"), mouseX, mouseY, nowInNano);

     this -> eventManager -> queueEvent(rightMouse);
   }
 }
