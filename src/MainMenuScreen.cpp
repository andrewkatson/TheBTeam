#include "MainMenuScreen.hpp"

MainMenuScreen::MainMenuScreen(shared_ptr<EventManager> eventManager,int windowX, int windowY, int numItems,shared_ptr<TextLoader> textLoader){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> selectedItem = 0;
  this -> registerEvents();



  this -> initText();
}

void MainMenuScreen::initText(){
  //get the path for the main font
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

  //load the main font
  if(!font.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
    ////cout << "loaded font!" << endl;
  }

  //get the path for the title font
  string titleFontPath = textLoader -> getString(string("IDS_Title_Font_Path"));

  //load a font for the title
  if(!titleFont.loadFromFile(titleFontPath)){
    //cout << "no title font!" << endl;
  }
  else{

  }

  //load the main menu picture
  string titlePicTexturePath = textLoader -> getString(string("IDS_Main_Title_Pic"));
  if (!mainPicture.loadFromFile(titlePicTexturePath))
  {
    //cout << "main title not loaded!" << endl;
  }
  screen.resize(3);

  //Main Menu
  if(numItems == 3){
    screen.at(0).setString(string("Play"));
    screen.at(0).setFillColor(sf::Color::Red);
    screen.at(0).setCharacterSize(24);
    screen.at(0).setPosition(sf::Vector2f((windowX / 10)*7, windowY / (numItems + 1) * 1));
    screen.at(1).setString(string("Options"));
    screen.at(1).setCharacterSize(24);
    screen.at(1).setPosition(sf::Vector2f((windowX / 10)*7, windowY / (numItems + 1) * 2));
    screen.at(1).setFillColor(sf::Color::White);
    screen.at(2).setString(string("Exit"));
    screen.at(2).setCharacterSize(24);
    screen.at(2).setPosition(sf::Vector2f((windowX / 10)*7, windowY / (numItems + 1)*3));
    screen.at(2).setFillColor(sf::Color::White);
  }

  string mainMenuTitleTextString = textLoader -> getString(string("IDS_Main_Menu_Title_Text_String"));
  int mainMenuTitleTextSize = textLoader -> getInteger(string("IDS_Main_Menu_Title_Text_Size"));

  //Main Menu Title
  title.setString(mainMenuTitleTextString);
  title.setCharacterSize(mainMenuTitleTextSize);
  title.setPosition(sf::Vector2f((windowX / 20.0)*13.5, windowY / (numItems + 8)));
  title.setFillColor(sf::Color::White);
}

void MainMenuScreen::draw(sf::RenderWindow &window){
  window.clear();

  //Draws the main picture
  sf::RectangleShape mainPictureRect(sf::Vector2f((this->windowX/10)*6, (this->windowY/10)*9));
  mainPictureRect.setPosition((this->windowX)/35, (this->windowY)/25);
  mainPictureRect.setTexture(&mainPicture);
  window.draw(mainPictureRect);


  //Write the title text
  title.setFont(titleFont);
  window.draw(title);

  //need to set the fonts locally
  for(int i = 0; i < numItems; i++){
    screen.at(i).setFont(font);
    window.draw(screen.at(i));
  }


  window.display();
}
void MainMenuScreen::moveUp()
{

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

void MainMenuScreen::moveDown()
{

  selectedItem = selectedItem % numItems;
  screen.at(selectedItem).setFillColor(sf::Color::White);
  selectedItem++;
  selectedItem = selectedItem % numItems;
  screen.at(selectedItem).setFillColor(sf::Color::Red);

}

/*
 * any events created by this class must be registered with the
 * Event Manager
 */
void MainMenuScreen::registerEvents(){
  //make a generic tower creation event, get its type, and register it
  StateChangeEvent event = StateChangeEvent();
  EventType type = event.getEventType();
  this -> eventManager -> registerEvent(type);
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
 * Deregisetr the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void MainMenuScreen::deregisterDelegates(){
  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_MMSD_KP")),keyPressEventType);
}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void MainMenuScreen::handleKeyPress(const EventInterface& event){
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
    if(selectedItem == (int) Choices::Play){
      shared_ptr<EventInterface> playState = make_shared<StateChangeEvent>(State::Playing, nowInNano);

      this -> eventManager -> queueEvent(playState);
    }
    else if(selectedItem == (int) Choices::Options){
      shared_ptr<EventInterface> optionsState = make_shared<StateChangeEvent>(State::OptionsMenu, nowInNano);

      this -> eventManager -> queueEvent(optionsState);
    }
    else if(selectedItem == (int) Choices::Quit){
      shared_ptr<EventInterface> quit = make_shared<KeyPressEvent>(string("Q"), nowInNano);

      this -> eventManager -> queueEvent(quit);
    }
  }
  else if(key == "S"){
    shared_ptr<EventInterface> playState = make_shared<StateChangeEvent>(State::Playing, nowInNano);

    this -> eventManager -> queueEvent(playState);
  }
}
