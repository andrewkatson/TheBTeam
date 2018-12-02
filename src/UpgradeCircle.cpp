#include "UpgradeCircle.hpp"

UpgradeCircle::UpgradeCircle(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,
  shared_ptr<GameLogic> gameLogic, int windowX, int windowY){
    this -> eventManager = eventManager;
    this -> textLoader = textLoader;
    this -> gameLogic = gameLogic;
    this -> isDisplayed = false;
    this -> rowSelected = 0;
    this -> colSelected = 0;
    this -> windowX = windowX;
    this -> windowY = windowY;
    this -> upgradePriceAdditionString = "";
    this -> initButtonIDs();
    this -> initButtonIcons();
    this -> initDrawingMaterials();
}


UpgradeCircle::~UpgradeCircle(){

}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void UpgradeCircle::registerDelegates(){
  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&UpgradeCircle::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_Upgrade_Circle_Mouse_Press")),mousePressEventType);

}

/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void UpgradeCircle::deregisterDelegates(){
  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Upgrade_Circle_Mouse_Press")),mousePressEventType);

}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void UpgradeCircle::handleMousePress(const EventInterface& event){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
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

  //get whether this is a left or right mouse click
  string mouseButtonPressed = mpEventData -> partOfMouse;

  //get the xposition
  float xPos = mpEventData -> x;
  //get the y position
  float yPos = mpEventData -> y;

  //get the size of a tile in the x
  float xTileSize = gameLogic -> getTileXSize();
  //get the size of a tile in the y
  float yTileSize = gameLogic -> getTileYSize();

  //what row is being clicked
  int row = (int) yPos / yTileSize;
  //what col is being clicked
  int col = (int) xPos / xTileSize;

  //if there is a tower then we care otherwise we leave
  if(gameLogic -> isTower(row, col)){
    //get the tower we have clicked on
    shared_ptr<TowerInterface> towerSelected = gameLogic -> getTowerPlaced(row, col);
    if(mouseButtonPressed == "Right"){
      rowSelected = row;
      colSelected = col;
      isDisplayed = true;
    }
    else{
      //if this was the left button we should switch things to false if none of our buttons were selected
      //which is only possible if we have already right clicked on the tower
      if(row == rowSelected && col == colSelected){
        //check only if the buttons are visible
        if(isDisplayed){
          //a tower upgrade has to be purchaseable
          if(gameLogic->canUpgradeTowerStats(row,col)){
            string upgradeButtonID = "";

            //determine which button is being selected
            if(towerSelected -> isMelee){
              upgradeButtonID = checkMeleeTowerUpgradeButtons(xPos, yPos);
            }
            else{
              upgradeButtonID = checkRangeTowerUpgradeButtons(xPos, yPos);
            }

            if(upgradeButtonID != ""){
              //upgrade the tower
              gameLogic->upgradeTower(upgradeButtonID, row, col);
            }
          }
        }
      }
      else{
        rowSelected = row;
        colSelected = col;
        isDisplayed = false;
      }
    }
  }
  else{
    rowSelected = row;
    colSelected = col;
    isDisplayed = false;
  }

}

/*
 * Iterate through the melee tower upgrade buttons and determine which has been clicked
 * @param mouseX: the x position of the mouse click
 * @param mouseY: the y position of the mouse click
 */
 string UpgradeCircle::checkMeleeTowerUpgradeButtons(float mouseX, float mouseY){
   string retString = "";

   for(shared_ptr<Button> meleeTowerUpgradeButton : meleeTowerUpgradeButtons){
     if(meleeTowerUpgradeButton -> isSelected(mouseX, mouseY)){
       return meleeTowerUpgradeButton -> getButtonID();
     }
   }
   return retString;
 }

 /*
  * Iterate through the range tower upgrade buttons and determine which has been clicked
  * @param mouseX: the x position of the mouse click
  * @param mouseY: the y position of the mouse click
  */
  string UpgradeCircle::checkRangeTowerUpgradeButtons(float mouseX, float mouseY){
    string retString = "";

    for(shared_ptr<Button> rangeTowerUpgradeButton : rangeTowerUpgradeButtons){
      if(rangeTowerUpgradeButton -> isSelected(mouseX, mouseY)){
        return rangeTowerUpgradeButton -> getButtonID();
      }
    }
    return retString;
  }


//set up the vector full of strings for each button id
void UpgradeCircle::initButtonIDs(){
  //add the button ids for melee tower
  initButtonIDsMeleeTower();
  //add the button ids for range tower
  initButtonIDsRangeTower();
}

void UpgradeCircle::initButtonIDsMeleeTower(){
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Tower_Radius_Upgrade_ID")));
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Tower_Respawn_Rate_Upgrade_ID")));
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Max_Hitpoints_Upgrade_ID")));
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Max_Damage_Upgrade_ID")));
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Armor_Penetration_Upgrade_ID")));
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Armor_Upgrade_ID")));
  meleeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Attack_Rate_Upgrade_ID")));
}

void UpgradeCircle::initButtonIDsRangeTower(){
  rangeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Tower_Radius_Upgrade_ID")));
  rangeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Tower_Rate_Of_Fire_Upgrade_ID")));
  rangeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Max_Damage_Upgrade_ID")));
  rangeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Armor_Penetration_Upgrade_ID")));
  rangeTowerButtonIDS.push_back(textLoader->getString(string("IDS_Actor_Area_Of_Effect_Upgrade_ID")));
}

//set up the vector full of strings for each button icon path
void UpgradeCircle::initButtonIcons(){
  //add the button icon paths for the melee tower
  initButtonIconPathsMeleeTower();
  //add the button icon paths for the range tower
  initButtonIconPathsRangeTower();
}

void UpgradeCircle::initButtonIconPathsMeleeTower(){
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Radius_Upgrade_ID")));
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Respawn_Speed_Upgrade_ID")));
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Hitpoints_Upgrade_ID")));
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Damage_Upgrade_ID")));
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Armor_Penetration_Upgrade_ID")));
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Armor_Upgrade_ID")));
  meleeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Attack_Rate_Upgrade_ID")));
}

void UpgradeCircle::initButtonIconPathsRangeTower(){
  rangeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Radius_Upgrade_ID")));
  rangeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Rate_Of_Fire_Upgrade_ID")));
  rangeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Damage_Upgrade_ID")));
  rangeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Armor_Penetration_Upgrade_ID")));
  rangeTowerButtonIconPaths.push_back(textLoader->getString(string("IDS_Area_Of_Effect_Upgrade_ID")));
}

void UpgradeCircle::initDrawingMaterials(){
  initTowerUpgradeButtons();
  initUpgradePriceButton();
  initCircleToDraw();
}

/*
 * Put the tower upgrade buttons with icons, their id, and their other initlaizations (except position which is set later)
 */
void UpgradeCircle::initTowerUpgradeButtons(){
  initMeleeTowerUpgradeButtons();
  initRangeTowerUpgradeButtons();
}

void UpgradeCircle::initMeleeTowerUpgradeButtons(){
  //iterate through all the melee tower upgrade buttons
  for(int index = 0; index < meleeTowerButtonIDS.size(); index++){
    bool makeItCircle = true;
    //the path to load in the texture for this button's icon
    string iconPath = textLoader->getString(meleeTowerButtonIconPaths.at(index));

    //the id for the button
    string buttonid = textLoader->getString(meleeTowerButtonIDS.at(index));

    //make a circular button for this range tower upgrade button
    shared_ptr<Button> meleeTower = make_shared<Button>(windowX, windowY, 0.0, 0.0, textLoader,
       iconPath, makeItCircle, textLoader->getString(meleeTowerButtonIDS.at(index)));
    //set the radius of the circle to be its initial size
    meleeTower -> setCircleRadius(textLoader->getInteger("IDS_Button_Radius"));
    //set the origin of the circle shape to be its center
    meleeTower -> setOrigin(textLoader->getInteger("IDS_Button_Radius"), textLoader->getInteger("IDS_Button_Radius"));

    // set the fill color for the button
    meleeTower -> setFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Alpha")));

    //load in the color components of the button's color
    float redComponent = textLoader -> getInteger(string("IDS_Melee_Tower_Upgrade_Outline_Color_Red"));
    float greenComponent = textLoader -> getInteger(string("IDS_Melee_Tower_Upgrade_Outline_Color_Green"));
    float blueComponent = textLoader -> getInteger(string("IDS_Melee_Tower_Upgrade_Outline_Color_Blue"));
    float alphaComponent = textLoader -> getInteger(string("IDS_Melee_Tower_Upgrade_Outline_Color_Alpha"));
    //set the outline colorfor this range tower upgrade button
    meleeTower -> setOutlineColor(redComponent, greenComponent, blueComponent, alphaComponent);

    //set the outline color thickness
    meleeTower -> setOutlineThickness(textLoader->getInteger(string("IDS_Melee_Tower_Upgrade_Outline_Thickness")));

    meleeTowerUpgradeButtons.push_back(meleeTower);
  }

}

void UpgradeCircle::initRangeTowerUpgradeButtons(){
  //iterate through all the range tower upgrade buttons
  for(int index = 0; index < rangeTowerButtonIDS.size(); index++){
    bool makeItCircle = true;
    //make a circular button for this range tower upgrade button
    shared_ptr<Button> rangeTower = make_shared<Button>(windowX, windowY, 0.0, 0.0, textLoader,
       textLoader->getString(rangeTowerButtonIconPaths.at(index)), makeItCircle, textLoader->getString(rangeTowerButtonIDS.at(index)));
    //set the radius of the circle to be its initial size
    rangeTower -> setCircleRadius(textLoader->getInteger("IDS_Button_Radius"));
    //set the origin of the circle shape to be its center
    rangeTower -> setOrigin(textLoader->getInteger("IDS_Button_Radius"), textLoader->getInteger("IDS_Button_Radius"));

    // set the fill color for the button
    rangeTower -> setFillColor(this->textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Tile_Button_Fill_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Tile_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Tile_Button_Fill_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Tile_Button_Fill_Color_Alpha")));

    //load in the color components of the button's color
    float redComponent = textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Outline_Color_Red"));
    float greenComponent = textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Outline_Color_Green"));
    float blueComponent = textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Outline_Color_Blue"));
    float alphaComponent = textLoader -> getInteger(string("IDS_Range_Tower_Upgrade_Outline_Color_Alpha"));
    //set the outline color for this range tower upgrade button
    rangeTower -> setOutlineColor(redComponent, greenComponent, blueComponent, alphaComponent);

    //set the outline color thickness
    rangeTower -> setOutlineThickness(textLoader->getInteger(string("IDS_Range_Tower_Upgrade_Outline_Thickness")));

    rangeTowerUpgradeButtons.push_back(rangeTower);
  }
}

/*
 * Initalize the upgrade price button that displays how much an upgrade will cost
 */
void UpgradeCircle::initUpgradePriceButton(){
  string fontpath = textLoader -> getString(string("IDS_TFP"));

  //the base string used for the upgrade price along with 0 to be the amount paid
  upgradePriceBaseString = textLoader -> getString(string("IDS_Upgrade_Circle_Price_Button"));
  string fullUpgradePriceString = upgradePriceBaseString + string(" 0");

  //set up the upgrade price button
  upgradePriceButton = unique_ptr<Button>(new Button(windowX, windowY, 0.0,0.0,
    fullUpgradePriceString, textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> upgradePriceButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> upgradePriceButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> upgradePriceButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Fill_Color_Alpha")));

  //set the outline color for the text
  this -> upgradePriceButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->upgradePriceButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Text_Outline_Thickness")));

  //set the text character size
  this->upgradePriceButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Upgrade_Price_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->upgradePriceButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> upgradePriceButton) -> setButtonPosition(0.0,0.0);

}

/*
 * Initalize the circle to draw on
 */
void UpgradeCircle::initCircleToDraw(){

  int redComponent = this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Background_Circle_Fill_Color_Red"));
  int blueComponent = this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Background_Circle_Fill_Color_Blue"));
  int greenComponent = this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Background_Circle_Fill_Color_Green"));
  int alphaComponent = this->textLoader -> getInteger(string("IDS_Upgrade_Price_Button_Background_Circle_Fill_Color_Alpha"));
  sf::Color fillColor (redComponent, greenComponent, blueComponent, alphaComponent);
  // set the fill color for the background circle
  circleToDraw.setFillColor(fillColor);
}

void UpgradeCircle::draw(sf::RenderWindow& window){

  if(isDisplayed){
    shared_ptr<TowerInterface> tower = gameLogic->getTowerPlaced(rowSelected, colSelected);

    //check the mouse position every second in case it is hovering over one of
    //the buttons so that the price button reflects what it upgrades
    checkMousePosAndDisplayUpgrade(tower, window);

    //if this is a melee tower selected
    if(tower -> isMelee){
      drawMeleeTowerButtons(tower, window);
    }
    //if this is a range tower selected
    else{
      drawRangeTowerButtons(tower, window);
    }

    drawUpgradePriceButton(window);
  }
}

/*
 * Checks the mouse position and displays the corresponding string inside of the
 * upgrade price button
 */
void UpgradeCircle::checkMousePosAndDisplayUpgrade(shared_ptr<TowerInterface> tower,sf::RenderWindow& window){
  if(tower->isMelee){
    checkMousePosAndDisplayMeleeUpgrade(tower, window);
  }
  else{
    checkMousePosAndDisplayRangeUpgrade(tower, window);
  }
}

/*
 * Check the mouse position considering a melee tower has been clicked on
 * and display the appropriate screen in the upgrade price button
 */
void UpgradeCircle::checkMousePosAndDisplayMeleeUpgrade(shared_ptr<TowerInterface> tower,sf::RenderWindow& window){
  float mouseX = mouse.getPosition(window).x;
  float mouseY = mouse.getPosition(window).y;

  for(shared_ptr<Button> meleeTowerUpgradeButton : meleeTowerUpgradeButtons){
    //if the current mouse coordinates are over the button then we set the addtion string
    //for the upgrade price button to reflect that
    if(meleeTowerUpgradeButton->isSelected(mouseX, mouseY)){
      upgradePriceAdditionString = textLoader->getString(string("IDS_Melee_")+meleeTowerUpgradeButton->getButtonID());
      return;
    }
  }

  //if no tower was being hovered over then we set it to nothing
  upgradePriceAdditionString = " ";

}

/*
 * Check the mouse position considering a range tower has been clicked on
 * and display the appropriate screen in the upgrade price button
 */
void UpgradeCircle::checkMousePosAndDisplayRangeUpgrade(shared_ptr<TowerInterface> tower,sf::RenderWindow& window){
  float mouseX = mouse.getPosition(window).x;
  float mouseY = mouse.getPosition(window).y;


  for(shared_ptr<Button> rangeTowerUpgradeButton : rangeTowerUpgradeButtons){
    //if the current mouse coordinates are over the button then we set the addtion string
    //for the upgrade price button to reflect that
    if(rangeTowerUpgradeButton->isSelected(mouseX, mouseY)){
      upgradePriceAdditionString = textLoader->getString(string("IDS_Range_")+rangeTowerUpgradeButton->getButtonID());
      return;
    }
  }

  //if no tower was being hovered over then we set it to nothing
  upgradePriceAdditionString = " ";
}


/*
 * Draw the upgrade buttons for a melee tower
 * @param window: the window we draw on
 */
 void UpgradeCircle::drawMeleeTowerButtons(shared_ptr<TowerInterface> tower, sf::RenderWindow& window){
   int numMeleeTowerUpgradeButtons = meleeTowerUpgradeButtons.size();
   //the angle between each upgrade price button
   float angle = 360.0/numMeleeTowerUpgradeButtons;

   int buttonIndex = 0;
   //iterate through the melee tower upgrade buttons
   for(shared_ptr<Button> meleeTowerUpgradeButton : meleeTowerUpgradeButtons){
     //if the button is not visible we make it so
     if(!(meleeTowerUpgradeButton -> isCurrentlyVisible())){
       meleeTowerUpgradeButton -> flipVisibility();
     }

     //the radius without scaling of the circle to place the button on
     float radiusOfUpgradeCircle = (textLoader -> getInteger(string("IDS_Button_Radius"))
                     + textLoader -> getInteger(string("IDS_Upgrade_Circle_Button_Offset")));

     //the x and y for the button that is its position around the center of the tower
     float newX = (radiusOfUpgradeCircle) * (tower->getXScale()) * cos(angle*buttonIndex * (M_PI/180.0)) + (tower->getXCoordinate());
     float newY = (radiusOfUpgradeCircle) * (tower->getYScale()) * sin(angle*buttonIndex * (M_PI/180.0)) + (tower->getYCoordinate());

     //set the button's new position
     meleeTowerUpgradeButton -> setButtonPosition(newX, newY);

     //set the button's scale
     meleeTowerUpgradeButton -> setButtonScale(tower->getXScale(), tower->getYScale());

     int size = textLoader -> getInteger(string("IDS_Button_Radius"));

     //use the circle shape to draw a background for the button
     circleToDraw.setRadius(textLoader -> getInteger(string("IDS_Button_Radius")));
     circleToDraw.setOrigin(textLoader -> getInteger(string("IDS_Button_Radius")), textLoader -> getInteger(string("IDS_Button_Radius")));
     circleToDraw.setPosition(newX,newY);
     circleToDraw.setScale(tower->getXScale(), tower->getYScale());
     window.draw(circleToDraw);

     meleeTowerUpgradeButton -> draw(window);

     buttonIndex++;
   }
 }

/*
* Draw the upgrade buttons for a range tower
* @param window: the window we draw on
*/
void UpgradeCircle::drawRangeTowerButtons(shared_ptr<TowerInterface> tower, sf::RenderWindow& window){
  int numRangeTowerUpgradeButtons = rangeTowerUpgradeButtons.size();
  //the angle between each upgrade price button
  float angle = 360.0/numRangeTowerUpgradeButtons;

  int buttonIndex = 0;
  //iterate through the range tower upgrade buttons
  for(shared_ptr<Button> rangeTowerUpgradeButton : rangeTowerUpgradeButtons){
    //if the button is not visible we make it so
    if(!(rangeTowerUpgradeButton -> isCurrentlyVisible())){
      rangeTowerUpgradeButton -> flipVisibility();
    }

    //the radius without scaling of the circle to place the button on
    float radiusOfUpgradeCircle = (textLoader -> getInteger(string("IDS_Button_Radius"))
                    + textLoader -> getInteger(string("IDS_Upgrade_Circle_Button_Offset")));

    //the x and y for the button that is its position around the center of the tower
    float newX = (radiusOfUpgradeCircle) * (tower->getXScale()) * cos(angle*buttonIndex * (M_PI/180.0)) + (tower->getXCoordinate());
    float newY = (radiusOfUpgradeCircle) * (tower->getYScale()) * sin(angle*buttonIndex * (M_PI/180.0)) + (tower->getYCoordinate());

    //set the button's new position
    rangeTowerUpgradeButton -> setButtonPosition(newX, newY);

    //set the button's scale
    rangeTowerUpgradeButton -> setButtonScale(tower->getXScale(), tower->getYScale());

    int size = textLoader -> getInteger(string("IDS_Button_Radius"));

    //use the circle shape to draw a background for the button
    circleToDraw.setRadius(textLoader -> getInteger(string("IDS_Button_Radius")));
    circleToDraw.setOrigin(textLoader -> getInteger(string("IDS_Button_Radius")), textLoader -> getInteger(string("IDS_Button_Radius")));
    circleToDraw.setPosition(newX,newY);
    circleToDraw.setScale(tower->getXScale(), tower->getYScale());
    window.draw(circleToDraw);

    rangeTowerUpgradeButton -> draw(window);

    buttonIndex++;
  }
}

/*
 * Draw the button that displays the price of an upgrade
 * @window: the window we draw on
 */
void UpgradeCircle::drawUpgradePriceButton(sf::RenderWindow& window){
  assert(gameLogic->isTower(rowSelected, colSelected));

  //finally display the button to show upgrade prices
  upgradePriceButton -> draw(window);

  //below is a workaround because the draw was not showing the text because sfml is stupid
  sf::Text text = upgradePriceButton -> getButtonText();
  sf::Font mainFont;
  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }

  text.setFont(mainFont);

  //have to modify the text to reflect the current price of an upgrade
  int priceOfUpgrade = gameLogic -> getUpgradePrice(rowSelected, colSelected);
  upgradePriceButton -> setString(upgradePriceBaseString + upgradePriceAdditionString + to_string(priceOfUpgrade));

  for(int i = 0; i < 2; i++){
    //get the x dimension of the tower
    float towerXDimension = gameLogic -> getTileXSize();

    //get the x position of the tower
    float towerXPos = gameLogic -> getTileXSize() * colSelected;

    //scale the button in case the words changed its size
    //was not setting itself properly around the current button
    sf::RectangleShape ownRect = (upgradePriceButton) -> getButtonRect();

    //position
    sf::Vector2f ownRectPos = ownRect.getPosition();
    //dimensions
    sf::Vector2f ownRecDimensions = ownRect.getSize();

    //their xmidpoint
    float towerMidpointX = towerXDimension/2 + towerXPos;
    //our x midpoint
    float ownRecMidpointX = ownRecDimensions.x/2 + ownRectPos.x;

    //the difference between ours and their
    float difference = towerMidpointX - ownRecMidpointX;

    float newxPos = ownRectPos.x + difference;

    //the yPosition is the same as the tower's
    float newyPos = gameLogic->getTileYSize() * rowSelected - ownRecDimensions.y*1.5;

    //rescale the button and reset it
    upgradePriceButton -> scaleButton(newxPos, newyPos);

    //we must set the position of the button to sit above the tower
    upgradePriceButton -> setButtonPosition(newxPos, newyPos);
  }

  window.draw(text);
}
