#include "LoadingScreen.hpp"


LoadingScreen::LoadingScreen(int windowX, int windowY, shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager){
  currentHint = 0;
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  srand (time(NULL));
  this -> loadHints();
  timeStarted = 0;
}

LoadingScreen::~LoadingScreen(){

}

void LoadingScreen::loadHints(){
  hints = textLoader -> getAllHints();
}

void LoadingScreen::registerDelegates(){
  //bind our delegate function for map generation events
  EventManager::EventDelegate mapGeneratedEventDelegate = std::bind(&LoadingScreen::handleMapGenerated, this, _1);

  //make an event and get its type
  MapGeneratedEvent mapGeneratedEvent = MapGeneratedEvent();
  EventType mapGeneratedEventType = mapGeneratedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mapGeneratedEventDelegate,
  textLoader -> getString(string("IDS_Loading_Screen_Map_Generated_Delegate")),mapGeneratedEventType);

  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<seconds>(now.time_since_epoch()).count();

  timeStarted=nowInNano;

  //everytime we register a delegate we should pick a different hint
  getNewHint();
}

void LoadingScreen::deregisterDelegates(){
  //make an event and get its type
  MapGeneratedEvent mapGeneratedEvent = MapGeneratedEvent();
  EventType mapGeneratedEventType = mapGeneratedEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(
  textLoader -> getString(string("IDS_Loading_Screen_Map_Generated_Delegate")),mapGeneratedEventType);
}


void LoadingScreen::handleMapGenerated(const EventInterface& event){

  auto mapGeneratedEvent= static_cast<const MapGeneratedEvent*>(&event);

  auto mapGeneratedEventData = static_cast<MapGeneratedEventData*>((mapGeneratedEvent->data).get());



}

void LoadingScreen::getNewHint(){
  //rand value to pick a hint
  int randVal = rand();

  currentHint+=(randVal%hints.size());

  //set the text to the next hint
  hint.setString(hints.at((currentHint)%hints.size()));

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_SFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  //cout << "loaded font!" << endl;
  }

  hint.setFont(mainFont);
  //and size the rectangle to be the center of the screen
  sf::FloatRect rect = hint.getGlobalBounds();

  //hint.setOrigin(rect.left, rect.top);

  //hint.setPosition(windowX/2.0, windowY/2.0);

  hint.setCharacterSize(textLoader->getInteger(string("IDS_Hint_Text")));

  hint.setFillColor(sf::Color::Red);
}

void LoadingScreen::draw(sf::RenderWindow& window){

  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<seconds>(now.time_since_epoch()).count();

  if(nowInNano - timeStarted> textLoader->getInteger(string("IDS_Loading_Screen_Time"))){
    changeToPlaying();
  }

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_SFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  //cout << "loaded font!" << endl;
  }
  hint.setFont(mainFont);

  window.draw(hint);


  sf::Text message;
  message.setFont(mainFont);
  message.setString(hints.at(currentHint%hints.size()));
  message.setCharacterSize(textLoader->getInteger(string("IDS_Hint_Text")));
  //and size the rectangle to be the center of the screen
  sf::FloatRect rect = message.getGlobalBounds();

  message.setOrigin(rect.width/2, rect.height/2);

  message.setPosition(windowX/2, windowY/2);

  message.setFillColor(sf::Color::White);

  window.draw(message);
}

void LoadingScreen::changeToPlaying(){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
  shared_ptr<EventInterface> playingState = make_shared<StateChangeEvent>(State::Playing, nowInNano);

  this -> eventManager -> queueEvent(playingState);
}
