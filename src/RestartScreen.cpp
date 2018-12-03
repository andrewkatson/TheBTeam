#include "RestartScreen.hpp"

RestartScreen::RestartScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> numItems = 3;
  this -> selectedItem = 0;


  //get the path for the main font
  string mainFontPath = textLoader -> getString(string("IDS_Title_Font_Path"));

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
  text.setPosition(sf::Vector2f((windowX / 25), ((windowY / 10) * 6)));

   //load the main menu picture
   string titlePicTexturePath = textLoader -> getString(string("IDS_Restart_Pic"));
   if (!restartPicture.loadFromFile(titlePicTexturePath))
   {
       cout << "picture not loaded!" << endl;
   }

  //Screen items to handle selecting between restarting the game = Return to main menu or checking a future leaderboard or quitting
  screen.resize(3);
  screen.at(0).setString(string("Restart"));
  screen.at(0).setFillColor(sf::Color::Red);
  screen.at(0).setCharacterSize(20);
  screen.at(0).setPosition(sf::Vector2f((windowX / 2), ((windowY / 10 ) * 7)));
  screen.at(1).setString(string("Check Leaderboard"));
  screen.at(1).setCharacterSize(20);
  screen.at(1).setPosition(sf::Vector2f((windowX / 2), ((windowY / 10) * 8)));
  screen.at(1).setFillColor(sf::Color::White);
  screen.at(2).setString(string("Quit"));
  screen.at(2).setCharacterSize(20);
  screen.at(2).setPosition(sf::Vector2f((windowX / 2), ((windowY / 10) * 9)));
  screen.at(2).setFillColor(sf::Color::White);
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
    window.clear();

    //Draws the main picture
    sf::RectangleShape pictureRect(sf::Vector2f((this->windowX/2), (this->windowY/2)));
    pictureRect.setPosition((this->windowX)/4, (this->windowY)/25);
    pictureRect.setTexture(&restartPicture);
    window.draw(pictureRect);


    //Write the title text
    text.setFont(font);
    window.draw(text);

    //setting font locally
    for(int i = 0; i < numItems; i++){
        screen.at(i).setFont(font);
        window.draw(screen.at(i));
    }

    window.display();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void RestartScreen::registerDelegates(){
    //bind our delegate function for key presses
    EventManager::EventDelegate keyPressDelegate = std::bind(&RestartScreen::handleKeyPress, this, _1);

    //make an event and get its type
    KeyPressEvent keyPressEvent = KeyPressEvent();
    EventType keyPressEventType = keyPressEvent.getEventType();
    //register the delegate and its type
    this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_RSD_KP")),keyPressEventType);

}
/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void RestartScreen::deregisterDelegates(){
    //make an event and get its type
    KeyPressEvent keyPressEvent = KeyPressEvent();
    EventType keyPressEventType = keyPressEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_RSD_KP")),keyPressEventType);

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
    else if(selectedItem == (int) Choices::Leaderboard){
        shared_ptr<EventInterface> quit = make_shared<KeyPressEvent>(string("Q"), nowInNano);

        this -> eventManager -> queueEvent(quit);
    }

    else if(selectedItem == (int) Choices::Quit){
      shared_ptr<EventInterface> quit = make_shared<KeyPressEvent>(string("Q"), nowInNano);

      this -> eventManager -> queueEvent(quit);
    }
  }

}
