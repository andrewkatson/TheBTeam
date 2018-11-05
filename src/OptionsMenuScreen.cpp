#include "OptionsMenuScreen.hpp"


OptionsMenuScreen::OptionsMenuScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY, int numItems, sf::Font font) {
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> font = font;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> selectedItem = 0;
  //this -> registerDelegates();
  /*

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
  screen.resize();
  //Options Menu
    if(numItems == 7){
    screen.at(0).setString(string("School"));
    screen.at(0).setFillColor(sf::Color::Red);
    screen.at(0).setCharacterSize(20);
    screen.at(0).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 1));

    screen.at(1).setString(string("Population"));
    screen.at(1).setFillColor(sf::Color::White);
    screen.at(1).setCharacterSize(20);
    screen.at(1).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 2));

    screen.at(2).setString(string("Obstacles"));
    screen.at(2).setFillColor(sf::Color::White);
    screen.at(2).setCharacterSize(20);
    screen.at(2).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 3));

    screen.at(3).setString(string("Waves"));
    screen.at(3).setFillColor(sf::Color::White);
    screen.at(3).setCharacterSize(20);
    screen.at(3).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 4));

    screen.at(4).setString(string("Start Money"));
    screen.at(4).setFillColor(sf::Color::White);
    screen.at(4).setCharacterSize(20);
    screen.at(4).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 5));

    screen.at(5).setString(string("Cafeteria Size"));
    screen.at(5).setFillColor(sf::Color::White);
    screen.at(5).setCharacterSize(20);
    screen.at(5).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 6));

    screen.at(6).setString(string("Path Length"));
    screen.at(6).setFillColor(sf::Color::White);
    screen.at(6).setCharacterSize(20);
    screen.at(6).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 7));

    */
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

void OptionsMenuScreen:moveRight()
{
  /* psuedocode:
  switcher[selectedItem].increment
  */
}

void OptionsMenuScreen::draw(sf::RenderWindow &window){
  window.clear();

  //setting font locally
  for(int i = 0; i < numItems; i++){
    screen.at(i).setFont(font);
    window.draw(screen.at(i));
  }

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
 * Handle any key press from the user
 * @param event: event of the key press
 */
void OptionsMenuScreen::handleKeyPress(const EventInterface& event){
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

  }
  else if(key == "Down"){

  }
  else if(key == "Left"){

  }
  else if(key == "Right"){

  }
  else if(key == "Enter"){

  }
  else if(key == "B"){

  }
}
