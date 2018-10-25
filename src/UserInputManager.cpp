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
   KeyPressEvent event = KeyPressEvent();
   EventType type = event.getEventType();
   this -> eventManager -> registerEvent(type);
 }

/*
 * handle a new event
 * @param event: the event passed from the Event Manager
 */
void UserInputManager::delegateMethod(const EventInterface& event){

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

      shared_ptr<EventInterface> closeKey = make_shared<KeyPressEvent>(KeyPressEvent(string("CLOSE"), nowInNano));

      this -> eventManager -> queueEvent(closeKey);
      game.close();
    }
   else if(Event.type == sf::Event::KeyPressed){
     handleKeyPress(Event);
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
     shared_ptr<EventInterface> qKey = make_shared<KeyPressEvent>(KeyPressEvent(string("Q"), nowInNano));

     this -> eventManager -> queueEvent(qKey);
   }
 }
