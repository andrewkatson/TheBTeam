#include "OptionsMenuScreen.hpp"

OptionsMenuScreen::OptionsMenuScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY, int numItems) {
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> selectedItem = 0;



  //get the path for the main font
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

  //load the main font
  if(!font.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
    //cout << "loaded font" <<endl;
  }

  this -> initText();
}

void OptionsMenuScreen::initText(){
  screen.resize(6);
  //Options Menu
    if(numItems == 6){
    screen.at(0).setString(string("School"));
    screen.at(0).setFillColor(sf::Color::Red);
    screen.at(0).setCharacterSize(20);
    screen.at(0).setPosition(sf::Vector2f(windowX / 4, windowY / (numItems + 1) * 1));

    screen.at(1).setString(string("Population"));
    screen.at(1).setFillColor(sf::Color::White);
    screen.at(1).setCharacterSize(20);
    screen.at(1).setPosition(sf::Vector2f(windowX / 4, windowY / (numItems + 1) * 2));

    screen.at(2).setString(string("Obstacles"));
    screen.at(2).setFillColor(sf::Color::White);
    screen.at(2).setCharacterSize(20);
    screen.at(2).setPosition(sf::Vector2f(windowX / 4, windowY / (numItems + 1) * 3));

    screen.at(3).setString(string("Waves"));
    screen.at(3).setFillColor(sf::Color::White);
    screen.at(3).setCharacterSize(20);
    screen.at(3).setPosition(sf::Vector2f(windowX / 4, windowY / (numItems + 1) * 4));

    screen.at(4).setString(string("Start Money"));
    screen.at(4).setFillColor(sf::Color::White);
    screen.at(4).setCharacterSize(20);
    screen.at(4).setPosition(sf::Vector2f(windowX / 4, windowY / (numItems + 1) * 5));

    screen.at(5).setString(string("Cafeteria Size"));
    screen.at(5).setFillColor(sf::Color::White);
    screen.at(5).setCharacterSize(20);
    screen.at(5).setPosition(sf::Vector2f(windowX / 4, windowY / (numItems + 1) * 6));

  }
}

  void OptionsMenuScreen::moveUp()
{
	if (selectedItem - 1 >= 0)
	{
		screen[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		screen[selectedItem].setFillColor(sf::Color::Red);
	}
}

void OptionsMenuScreen::moveDown()
{
	if (selectedItem + 1 < numItems)
	{
		screen[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		screen[selectedItem].setFillColor(sf::Color::Red);
}

}

void OptionsMenuScreen::moveRight()
{
    cout << std::to_string(selectedItem) + " was incremented one to the right" << endl;
  /* psuedocode:
  switcher.changeSelected(1)
  */
}

void OptionsMenuScreen::moveLeft()
{
    cout << std::to_string(selectedItem) + " was incremented one to the left" << endl;
    /* psuedocode:
    switcher.changeSelected(0)
    */
}

void OptionsMenuScreen::draw(sf::RenderWindow &window){
  window.clear();

  //setting font locally
  for(int i = 0; i < numItems; i++){
    screen.at(i).setFont(font);
    window.draw(screen.at(i));
  }
  //window.draw(switcher)

  window.display();
}


/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void OptionsMenuScreen::registerDelegates(){

  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&OptionsMenuScreen::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_OMSD_KP")),keyPressEventType);
}
/*
 * Deregisetr the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void OptionsMenuScreen::deregisterDelegates(){
    //make an event and get its type
    KeyPressEvent keyPressEvent = KeyPressEvent();
    EventType keyPressEventType = keyPressEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_OMSD_KP")),keyPressEventType);
}
/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void OptionsMenuScreen::handleKeyPress(const EventInterface& event){
    //the time object of the class
    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
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

  if(key == "Up"){
      moveUp();
  }
  else if(key == "Down"){
      moveDown();
  }
  else if(key == "Left"){
      moveLeft();
  }
  else if(key == "Right"){
      moveRight();
  }
  else if(key == "Enter"){
      cout << selectedItem << endl;
  }
  else if(key == "B"){
    //back/return to main menu can be implemented into a future restart screen
    shared_ptr<EventInterface> mainMenu = make_shared<StateChangeEvent>(State::MainMenu, nowInNano);

    this -> eventManager -> queueEvent(mainMenu);
  }
}
