#include "MainMenuScreen.hpp"

MainMenuScreen::MainMenuScreen(shared_ptr<EventManager> eventManager,int windowX, int windowY, int numItems,shared_ptr<TextLoader> textLoader){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> selectedItem = 0;
  check= 10;
  //this -> registerDelegates();
  /*
  //get the path for the main font
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

  //load the main font
  if(!font.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
    cout << "loaded font!" << endl;
  }
  */
  this -> initText();


}

void MainMenuScreen::initText(){

  //Main Menu
  if(numItems == 3){

  //  screen.at(0).setFillColor(sf::Color::Red);
    textStrings.push_back(string("Play"));
    //screen.at(0).setCharacterSize(24);
    //screen.at(0).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 1));

    //screen.at(1).setFillColor(sf::Color::White);
    textStrings.push_back(string("Options"));
    //screen.at(1).setCharacterSize(24);
    //screen.at(1).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 2));

    //screen.at(2).setFillColor(sf::Color::White);
    textStrings.push_back(string("Exit"));
  ///  screen.at(2).setCharacterSize(24);
    //screen.at(2).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 3));

  }
  cout << selectedItem << endl;

  cout << textStrings.size() << endl;

}

void MainMenuScreen::draw(sf::RenderWindow &window){
  window.clear();
  /*
  //need to set the fonts locally
  text.setFont(font);
  text.setCharacterSize(24);
  text.setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 3));

  for(int i = 0; i < numItems; i++){
    if(selectedItem == i){
      text.setFillColor(sf::Color::Red);
    }
    else{
      text.setFillColor(sf::Color::White);
    }

    window.draw(text);
  }
  */
  window.display();
}
void MainMenuScreen::moveUp()
{
  cout << "screen " << textStrings.size() << endl;
  cout << "up " <<  selectedItem << endl;
  cout  << numItems << endl;
  //make sure the selected item indicator can ever be outside of the
  //range of options
  selectedItem = selectedItem % numItems;
  //screen.at(selectedItem).setFillColor(sf::Color::White);
  selectedItem--;
  selectedItem = selectedItem % numItems;
  //screen.at(selectedItem).setFillColor(sf::Color::Red);

}

void MainMenuScreen::moveDown()
{
  cout << "screen " << textStrings.size() << endl;
  cout << "down " <<  selectedItem << endl;
  selectedItem = selectedItem % numItems;
  //screen.at(selectedItem).setFillColor(sf::Color::White);
  selectedItem++;
  selectedItem = selectedItem % numItems;
  //screen.at(selectedItem).setFillColor(sf::Color::Red);

}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void MainMenuScreen::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&MainMenuScreen::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_MMSD_KP")),keyPressEventType);
}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void MainMenuScreen::handleKeyPress(const EventInterface& event){

  cout << "handle key press " << endl;
  cout << textStrings.size() << endl;
  cout << numItems << endl;
  cout << selectedItem << endl;
  cout << " check 2 " << check << endl;
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
    //moveUp();
  }
  else if(key == "Down"){
    cout << "down" << endl;
    //moveDown();
  }
  else if(key == "Enter"){
    eventManager -> dumpErrors();
  }
}
