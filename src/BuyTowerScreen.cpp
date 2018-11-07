#include "BuyTowerScreen.hpp"

BuyTowerScreen::BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;

  //unused because it was causing issues
  //this -> initText();
}

/*
 * Initialize any parts of the text that will not change
 */
void BuyTowerScreen::initText(){

}

void BuyTowerScreen::draw(sf::RenderWindow &window){
  //used to make the font local
  string secondaryFontPath = textLoader -> getString(string("IDS_SFP"));

  //locally load the font
  if(!font.loadFromFile(secondaryFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }
  sf::Text title;

  // select the font
  title.setFont(font); // font is a sf::Font

  string titleTextString = this->textLoader->getString(string("IDS_Buy_Tower_Title_Text"));
  title.setString(titleTextString);

  int titleTextSize = this->textLoader->getInteger(string("IDS_Buy_Tower_Title_Text_Size"));
  title.setCharacterSize(titleTextSize);
  title.setPosition(this->windowX /3 + title.getCharacterSize(),
                      this->windowY/8 - title.getCharacterSize());
  sf::Color color (this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Alpha")));
  title.setFillColor(color);
  window.draw(title);

}
/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void BuyTowerScreen::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&BuyTowerScreen::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_BTS_KP")),keyPressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&BuyTowerScreen::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_BTS_MP")),mousePressEventType);

}
/*
 * Deregisetr the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void BuyTowerScreen::deregisterDelegates(){
  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_BTS_KP")),keyPressEventType);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_BTS_MP")),mousePressEventType);
}


/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void BuyTowerScreen::handleKeyPress(const EventInterface& event){
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

  if(key == "B"){
    shared_ptr<EventInterface> playingState = make_shared<StateChangeEvent>(State::Playing, nowInNano);

    this -> eventManager -> queueEvent(playingState);
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void BuyTowerScreen::handleMousePress(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * MousePressEvent type which allows us to access variables and methods
   * specific to MousePressEvent
   */
  const MousePressEvent* mpEvent = static_cast<const MousePressEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a KeyPressEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  MousePressEventData* mpEventData = static_cast<MousePressEventData*>((mpEvent -> data).get());
  //get the xposition
  float xPos = mpEventData -> x;
  //get the y position
  float yPos = mpEventData -> y;

}
