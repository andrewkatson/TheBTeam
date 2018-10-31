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

  //Options Menu
  if(numItems == 7){
    Screen[0].setFont(font);
    Screen[0].setFillColor(sf::Color::Red);
    Screen[0].setString("School");
    Screen[0].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 1));

    Screen[1].setFont(font);
    Screen[1].setFillColor(sf::Color::White);
    Screen[1].setString("Population");
    Screen[1].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 2));

    Screen[2].setFont(font);
    Screen[2].setFillColor(sf::Color::White);
    Screen[2].setString("Obstacles");
    Screen[2].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 3));

    Screen[3].setFont(font);
    Screen[3].setFillColor(sf::Color::White);
    Screen[3].setString("Waves");
    Screen[3].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 4));

    Screen[4].setFont(font);
    Screen[4].setFillColor(sf::Color::White);
    Screen[4].setString("Start Money");
    Screen[4].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 5));

    Screen[5].setFont(font);
    Screen[5].setFillColor(sf::Color::White);
    Screen[5].setString("Cafetria Size");
    Screen[5].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 6));

    Screen[6].setFont(font);
    Screen[6].setFillColor(sf::Color::White);
    Screen[6].setString("Path Length");
    Screen[6].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 7));

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

void OptionsMenuScreen::draw(sf::RenderWindow &window){

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
