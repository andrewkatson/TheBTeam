#include "OptionsMenuScreen.hpp"

OptionsMenuScreen::OptionsMenuScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY, int numItems) {
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> selectedItem = 0;
  //initialize switchers
  this -> school = make_shared<Switcher>(eventManager,textLoader, windowX, windowY, 0, 3);
  this -> population = make_shared<Switcher>(eventManager,textLoader, windowX, windowY, 1, 6);
  this -> obstacles = make_shared<Switcher>(eventManager,textLoader, windowX, windowY, 2, 3);
  this -> meal = make_shared<Switcher>(eventManager,textLoader, windowX, windowY, 3, 3);
  this -> startMoney = make_shared<Switcher>(eventManager,textLoader, windowX, windowY, 4, 3);
  this -> cafeteriaSize = make_shared<Switcher>(eventManager,textLoader, windowX, windowY, 5, 3);
  //initialize the button and the vector of screens
  this -> initDrawingMaterials();



  //get the path for the main font
  string mainFontPath = textLoader -> getString(string("IDS_Title_Font_Path"));

  //load the main font
  if(!font.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
    ////cout << "loaded font" <<endl;
  }

}

void OptionsMenuScreen::initDrawingMaterials(){
    initText();
    initBackButton();
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

    screen.at(3).setString(string("Meal"));
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
void OptionsMenuScreen::initBackButton(){
    string fontpath = textLoader -> getString(string("IDS_TFP"));

    //set up the back button
    backButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
                                               textLoader -> getString(string("IDS_Options_Menu_Confirm_Button")), textLoader, fontpath));

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
   switch(selectedItem) {
        case 0:  school -> changeSelected(1);
                break;
        case 1:  population -> changeSelected(1);
                break;
        case 2:  obstacles -> changeSelected(1);
                break;
        case 3:  meal -> changeSelected(1);
                break;
        case 4:  startMoney -> changeSelected(1);
                break;
        case 5:  cafeteriaSize -> changeSelected(1);
                break;
   }

}

void OptionsMenuScreen::moveLeft()
{
    switch(selectedItem) {
          case 0:  school -> changeSelected(0);
                    break;
          case 1:  population -> changeSelected(0);
                    break;
          case 2:  obstacles -> changeSelected(0);
                    break;
          case 3:  meal -> changeSelected(0);
                    break;
          case 4:  startMoney -> changeSelected(0);
                    break;
          case 5:  cafeteriaSize -> changeSelected(0);
                    break;
    }

}

void OptionsMenuScreen::draw(sf::RenderWindow &window){
  window.clear();

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

  //setting font locally
  for(int i = 0; i < numItems; i++){
    screen.at(i).setFont(font);
    window.draw(screen.at(i));
  }
  //draw the switchers
  school -> draw(window);
  population -> draw(window);
  obstacles -> draw(window);
  meal -> draw(window);
  startMoney -> draw(window);
  cafeteriaSize -> draw(window);

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

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&OptionsMenuScreen::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_OMSD_MP")),mousePressEventType);

}
/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void OptionsMenuScreen::deregisterDelegates(){
    //make an event and get its type
    KeyPressEvent keyPressEvent = KeyPressEvent();
    EventType keyPressEventType = keyPressEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_OMSD_KP")),keyPressEventType);

    //make an event and get its type
    MousePressEvent mousePressEvent = MousePressEvent();
    EventType mousePressEventType = mousePressEvent.getEventType();
    //deregister the delegate and its type
    this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_OMSD_MP")),mousePressEventType);

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

      optionSelected();

      shared_ptr<EventInterface> mainMenu = make_shared<StateChangeEvent>(State::MainMenu, nowInNano);

      this -> eventManager -> queueEvent(mainMenu);
  }
  else if(key == "B"){
    //back/return to main menu can be implemented into a future restart screen
    shared_ptr<EventInterface> mainMenu = make_shared<StateChangeEvent>(State::MainMenu, nowInNano);

    this -> eventManager -> queueEvent(mainMenu);
  }
  else if(key == "R"){
      //back/return to main menu can be implemented into a future restart screen
      shared_ptr<EventInterface> restartScreen = make_shared<StateChangeEvent>(State::Restart, nowInNano);

      this -> eventManager -> queueEvent(restartScreen);
  }
}

void OptionsMenuScreen::handleMousePress(const EventInterface& event) {
    /*
     * cast the EventInterface reference to a CONST pointer to the
     * MousePressEvent type which allows us to access variables and methods
     * specific to MousePressEvent
     */
    const MousePressEvent *mpEvent = static_cast<const MousePressEvent *>(&event);
    /*
     * cast the "data" (a EventDataInterface) to a KeyPressEventData type
     * the .get() is because data is a unique_ptr and we need to grab the
     * raw pointer inside of it for this
     */
    MousePressEventData *mpEventData = static_cast<MousePressEventData *>((mpEvent->data).get());
    //get the xposition
    float xPos = mpEventData->x;
    //get the y position
    float yPos = mpEventData->y;

    if(backButton->isSelected(xPos,yPos)){
        //the time object of the class
        auto now = high_resolution_clock::now();
        //the actual count in nanoseconds for the time
        auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

        shared_ptr<EventInterface> mainMenu = make_shared<StateChangeEvent>(State::MainMenu,nowInNano);

        this -> eventManager -> queueEvent(mainMenu);
    }
}

void OptionsMenuScreen::optionSelected(){

    //the time object of the class
    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

    shared_ptr<EventInterface> os0 = make_shared<OptionSelectedEvent>(school -> getID(), school -> getSelected(),nowInNano);
    shared_ptr<EventInterface> os1 = make_shared<OptionSelectedEvent>(population -> getID(), population -> getSelected(),nowInNano);
    shared_ptr<EventInterface> os2 = make_shared<OptionSelectedEvent>(obstacles -> getID(), obstacles -> getSelected(),nowInNano);
    shared_ptr<EventInterface> os3 = make_shared<OptionSelectedEvent>(meal -> getID(), meal -> getSelected(),nowInNano);
    shared_ptr<EventInterface> os4 = make_shared<OptionSelectedEvent>(startMoney -> getID(), startMoney -> getSelected(),nowInNano);
    shared_ptr<EventInterface> os5 = make_shared<OptionSelectedEvent>(cafeteriaSize -> getID(), cafeteriaSize -> getSelected(),nowInNano);
    this -> eventManager -> queueEvent(os0);
    this -> eventManager -> queueEvent(os1);
    this -> eventManager -> queueEvent(os2);
    this -> eventManager -> queueEvent(os3);
    this -> eventManager -> queueEvent(os4);
    this -> eventManager -> queueEvent(os5);



}
