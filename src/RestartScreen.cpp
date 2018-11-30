#include "RestartScreen.hpp"

RestartScreen::RestartScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> numItems = 2;
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



void RestartScreen::initText(){
  string mainText = textLoader -> getString(string("IDS_RSM"));
  text.setString(mainText);
  text.setCharacterSize(30);
  text.setPosition(sf::Vector2f((windowX / 2), (windowY * 0.5)));

  //Screen items to handle selecting between restarting the game = Return to main menu or quitting
  screen.resize(2);
  screen.at(0).setString(string("Restart"));
  screen.at(0).setFillColor(sf::Color::Red);
  screen.at(0).setCharacterSize(20);
  screen.at(0).setPosition(sf::Vector2f((windowX / 2), (windowY * 0.75 )));
  screen.at(1).setString(string("Quit"));
  screen.at(1).setCharacterSize(20);
  screen.at(1).setPosition(sf::Vector2f((windowX / 2), (windowY * 0.9)));
  screen.at(1).setFillColor(sf::Color::White);
}

void RestartScreen::moveUp(){

  //make sure the selected item indicator can ever be outside of the
  //range of options
  selectedItem = selectedItem % numItems;
  screen.at(selectedItem).setFillColor(sf::Color::White);
  selectedItem--;
  //the below line just ensures that if we are below 0 then we want to
  //put selectedItem to a value above 0 with an equivalent modulus with
  //numItems
  selectedItem = selectedItem >= 0 ? selectedItem: numItems + selectedItem;
  selectedItem = selectedItem % numItems;
  screen.at(selectedItem).setFillColor(sf::Color::Red);

}

void RestartScreen::moveDown(){

  selectedItem = selectedItem % numItems;
  screen.at(selectedItem).setFillColor(sf::Color::White);
  selectedItem++;
  selectedItem = selectedItem % numItems;
  screen.at(selectedItem).setFillColor(sf::Color::Red);

}

void RestartScreen::draw(sf::RenderWindow &window){

}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void RestartScreen::registerDelegates(){

}
/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void RestartScreen::deregisterDelegates(){

}

void RestartScreen::handleKeyPress(const EventInterface& event){
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
  else if(key == "Enter"){

    if(selectedItem == (int) Choices::Restart){
      shared_ptr<EventInterface> mainMenu = make_shared<StateChangeEvent>(State::MainMenu, nowInNano);

      this -> eventManager -> queueEvent(mainMenu);
    }

    else if(selectedItem == (int) Choices::Quit){
      shared_ptr<EventInterface> quit = make_shared<KeyPressEvent>(string("Q"), nowInNano);

      this -> eventManager -> queueEvent(quit);
    }
  }

}
