#include "UserView.hpp"


UserView::UserView(shared_ptr<EventManager> eventManager, sf::RenderWindow &game){

  this -> eventManager = eventManager;
  this -> userInputManager = unique_ptr<UserInputManager>(new UserInputManager(eventManager));
  this -> registerDelegates();
  this -> game = &game;

  font.loadFromFile("../Fonts/PWYummyDonuts.ttf");

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

UserView::~UserView(){
  game = nullptr;
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void UserView::registerDelegates(){
  //bind our delegatefunction for key presses
  std::function<void(const EventInterface&)> delegate = std::bind(&UserView::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent event = KeyPressEvent();
  EventType type = event.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(delegate,  string("USERVIEWHANDLEKEYPRESS"),type);
}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void UserView::handleKeyPress(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * KeyPressEvent type which allows us to access variables and methods
   * specific to KeyPressEvent
   */
  const KeyPressEvent* kpEvent = static_cast<const KeyPressEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a KeyPressEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  KeyPressEventData* kpEventData = static_cast<KeyPressEventData*>((kpEvent -> data).get());
  //get the key string identifier from the data
  string key = kpEventData -> keyID;
  if(key == "CLOSE"){
    shutDown();
  }
  else if(key == "Q"){
    shutDown();
  }
}


void UserView::updateUserView(float deltaS, sf::RenderWindow &game){
  this -> userInputManager -> processUserInput(game);
}

void UserView::shutDown(){
  game -> close();
}
