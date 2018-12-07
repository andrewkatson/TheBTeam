#include "LeaderBoardScreen.hpp"


LeaderBoardScreen::LeaderBoardScreen(int windowX, int windowY, shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> connection = false;
  this -> initBackButton();
}


LeaderBoardScreen::~LeaderBoardScreen(){

}

void LeaderBoardScreen::initBackButton(){
  string fontpath = textLoader -> getString(string("IDS_TFP"));

  //set up the back button
  backButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
    textLoader -> getString(string("IDS_Buy_Tower_Back_Button")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> backButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> backButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> backButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")));

  //set the outline color for the text
  this -> backButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->backButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Thickness")));

  //set the text character size
  this->backButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Back_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->backButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> backButton) -> setButtonPosition( BOTTOMLEFT);
}

void LeaderBoardScreen::registerDelegates(){

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&LeaderBoardScreen::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_Leader_Board_Mouse_Press_Delegate")),mousePressEventType);

  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&LeaderBoardScreen::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_Leader_Board_Key_Press_Delegate")),keyPressEventType);

  tryToConnect();
}

void LeaderBoardScreen::deregisterDelegates(){
  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Leader_Board_Mouse_Press_Delegate")),mousePressEventType);


  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Leader_Board_Key_Press_Delegate")),keyPressEventType);

  endConnect();
}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void LeaderBoardScreen::handleKeyPress(const EventInterface& event){
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
    shared_ptr<EventInterface> restartState = make_shared<StateChangeEvent>(State::Restart, nowInNano);

    this -> eventManager -> queueEvent(restartState);
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void LeaderBoardScreen::handleMousePress(const EventInterface& event){
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

  if(backButton->isSelected(xPos,yPos)){
    //the time object of the class
    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

    shared_ptr<EventInterface> restartState = make_shared<StateChangeEvent>(State::Restart, nowInNano);

    this -> eventManager -> queueEvent(restartState);
  }
}

void LeaderBoardScreen::tryToConnect(){


  //const char *cmd = &(execute[0]);
  //system(cmd);
  //cout << cmd << endl;
  //string result = exec(cmd);
  string result = "FAIL";
  if(result == "FAIL"){
    connection = false;
    getLocalLeaderBoard();
  }
  else{
    connection = true;
    getLeaderBoard();
  }
  /*
  my_ssh_session = ssh_new();
  int verbosity = SSH_LOG_PROTOCOL;
  int port = 22;
  int rc;
  if (my_ssh_session == NULL){
    connection = false;
    return;
  }

  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "localhost");
  ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
  ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);

  rc = ssh_connect(my_ssh_session);
  if (rc != SSH_OK)
  {
  fprintf(stderr, "Error connecting to localhost: %s\n",
          ssh_get_error(my_ssh_session));
  exit(-1);
  }
  */

}

std::string LeaderBoardScreen::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        result = "FAIL";
        //throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    if(result != "FAIL" && result.length() == 0){
      result = "OK";
    }
    return result;
}

void LeaderBoardScreen::getLeaderBoard(){

}

void LeaderBoardScreen::getLocalLeaderBoard(){
  //ensure there is a leaderboard
  string execute = "touch leaderboard.txt";
  const char *cmd = &(execute[0]);
  exec(cmd);
}

void LeaderBoardScreen::endConnect(){
  if(connection){
    //ssh_free(my_ssh_session);
  }
}

void LeaderBoardScreen::draw(sf::RenderWindow& window){


  sf::Text message;
  message.setFont(mainFont);
  if(connection){
    message.setString(textLoader->getString(string("IDS_Leader_Board_Normal_Title")));
  }
  else{
    message.setString(textLoader->getString(string("IDS_Leader_Board_No_Connection")));
  }

  message.setCharacterSize(textLoader->getInteger(string("IDS_Leader_Board_Message_Text_Size")));
  //and size the rectangle to be the center of the screen
  sf::FloatRect rect = message.getGlobalBounds();

  message.setOrigin(rect.width/2, rect.height/2);

  message.setPosition(windowX/2, windowY/6);

  message.setFillColor(sf::Color::White);

  window.draw(message);

  backButton -> draw(window);

  //below is a workaround because the draw was not showing the text because sfml is stupid
  sf::Text text = backButton -> getButtonText();
  sf::Font mainFont;
  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
  //  //cout << "loaded font!" << endl;
  }

  text.setFont(mainFont);
  window.draw(text);
}
