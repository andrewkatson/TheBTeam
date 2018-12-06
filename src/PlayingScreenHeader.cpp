#include "PlayingScreenHeader.hpp"


PlayingScreenHeader::PlayingScreenHeader(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic){
  this->eventManager=eventManager;
  this->textLoader=textLoader;
  this->gameLogic=gameLogic;
  this -> windowX = gameLogic -> getWindowX();
  this-> windowY = gameLogic -> getWindowY();
  string fontpath = textLoader -> getString(string("IDS_TFP"));
  this -> buyTower = unique_ptr<Button>(new Button(windowX, windowY, TOPRIGHT,
    textLoader -> getString(string("IDS_Buy_Tower_Empty_Space")), textLoader, fontpath));

  visible = true;
  initDrawingMaterials();
  recaculateHeader = false;
  ySize = getMaximumY();
  rowSelected = 0;
  colSelected = 0;
  timesHeaderRecalculated = 0;
  blockClicks = false;
  registerPersistentDelegates();
}

PlayingScreenHeader::~PlayingScreenHeader(){
  this -> deregisterPersistentDelegates();
}

/*
 * Set up any objects that can be drawn
 */
void PlayingScreenHeader::initDrawingMaterials(){
  headerVariables.clear();
  headerVariableValues.clear();
  initBuyTowerButton();
  initSellTowerButton();
  initHitpointsButton();
  initBalanceButton();
  initLevelButton();
  initWaveButton();
}

/*
 * Set up the buy tower button
 */
void PlayingScreenHeader::initBuyTowerButton(){
  // set the fill color for the button rectangle
  this -> buyTower -> setFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> buyTower -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->buyTower -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Thickness")));

  //set the fill color for the button text
  this -> buyTower -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  this -> buyTower -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->buyTower -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Thickness")));

  //set the text character size
  this->buyTower -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Buy_Tower_Text_Size")));

  string fontpath = textLoader -> getString(string("IDS_TFP"));
  //set the font inside the button so it can be used to calculate a bounds
  (this->buyTower) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> buyTower) -> setButtonPosition( TOPRIGHT);

  //make the button invisible to begin with
  (this->buyTower) -> flipVisibility();
}

/*
 * Set up the sell tower button
 */
void PlayingScreenHeader::initSellTowerButton(){
  //padding between each button in header
  int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
  int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

  //the bounding rectangle for the rectangle around the balance button
  sf::RectangleShape offSetRect = (this->buyTower) -> getButtonRect();

  //position
  sf::Vector2f pos = offSetRect.getPosition();
  //dimensions
  sf::Vector2f dimensions = offSetRect.getSize();

  //the xPosition is the length of the balance button plus some padding
  float xPos = pos.x;
  //the yPosition is the
  float yPos =  pos.y + dimensions.y + headerButtonPaddingY;

  string fontpath = textLoader -> getString(string("IDS_TFP"));
  this -> sellTower = unique_ptr<Button>(new Button(windowX, windowY, xPos, yPos,
    textLoader -> getString(string("IDS_Sell_Tower")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> sellTower -> setFillColor(this->textLoader -> getInteger(string("IDS_Sell_Tower_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Sell_Tower_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> sellTower -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Sell_Tower_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Sell_Tower_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->sellTower -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Sell_Tower_Outline_Thickness")));

  //set the fill color for the button text
  this -> sellTower -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  this -> sellTower -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->sellTower -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Sell_Tower_Text_Outline_Thickness")));

  //set the text character size
  this->sellTower -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Sell_Tower_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->sellTower) -> setFont(fontpath);


  //was not setting itself properly
  //the bounding rectangle for the rectangle around the balance button
  sf::RectangleShape ownRect = (this->sellTower) -> getButtonRect();

  //position
  sf::Vector2f ownRectPos = ownRect.getPosition();
  //dimensions
  sf::Vector2f ownRecDimensions = ownRect.getSize();

  //the xPosition is the length of the balance button plus some padding
  float newxPos = pos.x;
  //the yPosition is the
  float newyPos =  dimensions.y + ownRecDimensions.y;

  //rescale the button and reset it
  (this -> sellTower) -> scaleButton( newxPos, newyPos);

  //make the button invisible to begin with
  (this->sellTower) -> flipVisibility();

}

/*
 * Initalize the hitpoints button to be displayed in the header
 */
void PlayingScreenHeader::initHitpointsButton(){

  //get the starting hitpoints
  shared_ptr<Player> player = gameLogic -> getPlayer();
  int startingHitpoints = player -> getHitpoints();

  //padding between each button in header
  int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
  int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

  //x position is from the left plus padding
  float xPos = headerButtonPaddingX;
  //y position is from the top plus padding
  float yPos = headerButtonPaddingY;

  string fontpath = textLoader -> getString(string("IDS_TFP"));
  shared_ptr<Button> hitpoints = make_shared<Button>(windowX, windowY, xPos, yPos,
    textLoader -> getString(string("IDS_Hitpoints_Button_Text"))  + to_string(startingHitpoints),
      textLoader, fontpath);

  // set the fill color for the button rectangle
  hitpoints->setFillColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Alpha")));

  // set the outline color for the button
  hitpoints->setOutlineColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Alpha")));

  //set the button outline thickness
  hitpoints -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Thickness")));

  //set the fill color for the button text
  hitpoints->setTextFillColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  hitpoints->setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  hitpoints->setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Thickness")));

  //set the text character size
  hitpoints->setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Hitpoints_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  hitpoints->setFont(fontpath);

  //rescale the button and reset it
  hitpoints->scaleButton(xPos, yPos);

  //push this button into the vector of buttons to be drawn
  headerVariables.push_back(hitpoints);

  //push the initial value of the button
  headerVariableValues.push_back(startingHitpoints);
}

/*
 * Initalize the balance button to be displayed in the header
 */
void PlayingScreenHeader::initBalanceButton(){

  //get the starting balance
  shared_ptr<Player> player = gameLogic -> getPlayer();
  int startingBalance = player -> getBalance();

  //padding between each button in header
  int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
  int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

  //the bounding rectangle for the rectangle around the balance button
  sf::RectangleShape offSetRect = headerVariables.at(0) -> getButtonRect();

  //position
  sf::Vector2f pos = offSetRect.getPosition();
  //dimensions
  sf::Vector2f dimensions = offSetRect.getSize();

  //the xPosition is the length of the balance button plus some padding
  float xPos = pos.x + dimensions.x + headerButtonPaddingX;
  //the yPosition is the
  float yPos =  headerButtonPaddingY;


  string fontpath = textLoader -> getString(string("IDS_TFP"));
  shared_ptr<Button> balance = make_shared<Button>(windowX, windowY, xPos, yPos,
    textLoader -> getString(string("IDS_Balance_Button_Text")) + to_string(startingBalance), textLoader, fontpath);

  // set the fill color for the button rectangle
  balance->setFillColor(this->textLoader -> getInteger(string("IDS_Balance_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Balance_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Balance_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Balance_Fill_Color_Alpha")));

  // set the outline color for the button
  balance->setOutlineColor(this->textLoader -> getInteger(string("IDS_Balance_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Balance_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Balance_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Balance_Outline_Color_Alpha")));

  //set the button outline thickness
  balance -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Balance_Outline_Thickness")));

  //set the fill color for the button text
  balance->setTextFillColor(this->textLoader -> getInteger(string("IDS_Balance_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Balance_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Balance_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Balance_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  balance->setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Balance_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Balance_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Balance_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Balance_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  balance->setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Balance_Text_Outline_Thickness")));

  //set the text character size
  balance->setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Balance_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  balance->setFont(fontpath);

  //rescale the button and reset it
  balance->scaleButton(xPos, yPos);

  //push this button into the vector of buttons to be drawn
  headerVariables.push_back(balance);

  //push the initial value of the button
  headerVariableValues.push_back(startingBalance);
}

/*
 * Initalize the level button to be displayed in the header
 */
void PlayingScreenHeader::initLevelButton(){
  //get the starting level
  shared_ptr<Player> player = gameLogic -> getPlayer();
  int startingLevel = player -> getLevel();

  //padding between each button in header
  int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
  int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

  //the bounding rectangle for the rectangle around the level button
  sf::RectangleShape offSetRect = headerVariables.at(1) -> getButtonRect();

  //position
  sf::Vector2f pos = offSetRect.getPosition();
  //dimensions
  sf::Vector2f dimensions = offSetRect.getSize();

  //the xPosition is the length of the level button plus some padding
  float xPos = pos.x + dimensions.x + headerButtonPaddingX;
  //the yPosition is the
  float yPos =  headerButtonPaddingY;


  string fontpath = textLoader -> getString(string("IDS_TFP"));
  shared_ptr<Button> level = make_shared<Button>(windowX, windowY, xPos, yPos,
    textLoader -> getString(string("IDS_Level_Button_Text")) + to_string(startingLevel), textLoader, fontpath);

  // set the fill color for the button rectangle
  level->setFillColor(this->textLoader -> getInteger(string("IDS_Level_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Level_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Level_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Level_Fill_Color_Alpha")));

  // set the outline color for the button
  level->setOutlineColor(this->textLoader -> getInteger(string("IDS_Level_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Level_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Level_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Level_Outline_Color_Alpha")));

  //set the button outline thickness
  level -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Level_Outline_Thickness")));

  //set the fill color for the button text
  level->setTextFillColor(this->textLoader -> getInteger(string("IDS_Level_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Level_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Level_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Level_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  level->setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Level_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Level_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Level_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Level_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  level->setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Level_Text_Outline_Thickness")));

  //set the text character size
  level->setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Level_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  level->setFont(fontpath);

  //rescale the button and reset it
  level->scaleButton(xPos, yPos);

  //push this button into the vector of buttons to be drawn
  headerVariables.push_back(level);

  //push the inital value
  headerVariableValues.push_back(startingLevel);
}

/*
 * Initalize the wave button to be displayed in the header
 */
void PlayingScreenHeader::initWaveButton(){
  //get the starting wave
  shared_ptr<Player> player = gameLogic -> getPlayer();
  int startingWave = player -> getWave();

  cout << "wave is " << startingWave << endl;
  //padding between each button in header
  int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
  int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

  //the bounding rectangle for the rectangle around the wave button
  sf::RectangleShape offSetRect = headerVariables.at(2) -> getButtonRect();

  //position
  sf::Vector2f pos = offSetRect.getPosition();
  //dimensions
  sf::Vector2f dimensions = offSetRect.getSize();

  //the xPosition is the length of the wave button plus some padding
  float xPos = pos.x + dimensions.x + headerButtonPaddingX;
  //the yPosition is the
  float yPos =  headerButtonPaddingY;

  string fontpath = textLoader -> getString(string("IDS_TFP"));
  shared_ptr<Button> wave = make_shared<Button>(windowX, windowY, xPos, yPos,
    textLoader -> getString(string("IDS_Wave_Button_Text")) + to_string(startingWave), textLoader, fontpath);

  // set the fill color for the button rectangle
  wave->setFillColor(this->textLoader -> getInteger(string("IDS_Wave_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Wave_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Wave_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Wave_Fill_Color_Alpha")));

  // set the outline color for the button
  wave->setOutlineColor(this->textLoader -> getInteger(string("IDS_Wave_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Wave_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Wave_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Wave_Outline_Color_Alpha")));

  //set the button outline thickness
  wave -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Wave_Outline_Thickness")));

  //set the fill color for the button text
  wave->setTextFillColor(this->textLoader -> getInteger(string("IDS_Wave_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Wave_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Wave_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Wave_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  wave->setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Wave_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Wave_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Wave_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Wave_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  wave->setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Wave_Text_Outline_Thickness")));

  //set the text character size
  wave->setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Wave_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  wave->setFont(fontpath);

  //rescale the button and reset it
  wave->scaleButton(xPos, yPos);


  //push this button into the vector of buttons to be drawn
  headerVariables.push_back(wave);

  //push the inital value
  headerVariableValues.push_back(startingWave);
}

/*
 * Recompute the size and strings for the buttons when
 * one of their values has been updated
 */
void PlayingScreenHeader::resetButtons(){
  resetHitpointButton();
  resetBalanceButton();
  resetLevelButton();
  resetWaveButton();

}

/*
 * Recompute the size and string of the hitpoints button
 */
void PlayingScreenHeader::resetHitpointButton(){

    //padding between each button in header
    int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
    int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

    //x position is from the left plus padding
    float xPos = headerButtonPaddingX;
    //y position is from the top plus padding
    float yPos = headerButtonPaddingY;

    //set the string
    headerVariables.at(0) -> setString(textLoader -> getString("IDS_Hitpoints_Button_Text") + to_string(headerVariableValues.at(0)));

    //rescale the button and reset it
    headerVariables.at(0) -> scaleButton(xPos, yPos);

}

/*
 * Recompute the size and string of the balance button
 */
void PlayingScreenHeader::resetBalanceButton(){
    //the bounding rectangle for the rectangle around the balance button
    sf::RectangleShape offSetRect = headerVariables.at(0) -> getButtonRect();

    //position
    sf::Vector2f pos = offSetRect.getPosition();
    //dimensions
    sf::Vector2f dimensions = offSetRect.getSize();

    //padding between each button in header
    int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
    int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

    //the xPosition is the length of the balance button plus some padding
    float xPos = pos.x + dimensions.x + headerButtonPaddingX;
    //the yPosition is the
    float yPos =  headerButtonPaddingY;

    //set the string
    headerVariables.at(1) -> setString(textLoader -> getString("IDS_Balance_Button_Text") + to_string(headerVariableValues.at(1)));

    //rescale the button and reset it
    headerVariables.at(1) -> scaleButton(xPos, yPos);

}

/*
 * Recompute the size and string of the level button
 */
void PlayingScreenHeader::resetLevelButton(){
    //the bounding rectangle for the rectangle around the wave button
    sf::RectangleShape offSetRect = headerVariables.at(1) -> getButtonRect();

    //position
    sf::Vector2f pos = offSetRect.getPosition();
    //dimensions
    sf::Vector2f dimensions = offSetRect.getSize();

    //padding between each button in header
    int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
    int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

    //the xPosition is the length of the wave button plus some padding
    float xPos = pos.x + dimensions.x + headerButtonPaddingX;
    //the yPosition is the
    float yPos =  headerButtonPaddingY;

    //set the string
    headerVariables.at(2) -> setString(textLoader -> getString("IDS_Level_Button_Text") + to_string(headerVariableValues.at(2)));

    //rescale the button and reset it
    headerVariables.at(2) -> scaleButton(xPos, yPos);

}

/*
 * Recompute the size and string of the wave button
 */
void PlayingScreenHeader::resetWaveButton(){

    //padding between each button in header
    int headerButtonPaddingX = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_X"));
    int headerButtonPaddingY = textLoader -> getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));

    //the bounding rectangle for the rectangle around the level button
    sf::RectangleShape offSetRect = headerVariables.at(2) -> getButtonRect();

    //position
    sf::Vector2f pos = offSetRect.getPosition();
    //dimensions
    sf::Vector2f dimensions = offSetRect.getSize();

    //the xPosition is the length of the level button plus some padding
    float xPos = pos.x + dimensions.x + headerButtonPaddingX;
    //the yPosition is the
    float yPos =  headerButtonPaddingY;


    //set the string
    headerVariables.at(3) -> setString(textLoader -> getString("IDS_Wave_Button_Text") + to_string(headerVariableValues.at(3)));

    //rescale the button and reset it
    headerVariables.at(3) -> scaleButton(xPos, yPos);

}

/*
 * Reset the header so that no buttons are visisble
 * and the row and col selected are reset
 */
void PlayingScreenHeader::softReset(){
  if(buyTower -> isCurrentlyVisible()){
    buyTower -> flipVisibility();
  }
  if(sellTower -> isCurrentlyVisible()){
    sellTower -> flipVisibility();
  }
  rowSelected = 0;
  colSelected = 0;
}

/*
 * @return the maximum y dimension of any object in the header
 */
float PlayingScreenHeader::getMaximumY(){

  /*
  //if the sell tower is visible it will be the lowest
  if((this->sellTower)->isCurrentlyVisible()){
    sf::RectangleShape rect = sellTower -> getButtonRect();
    sf::Vector2f size = rect.getSize();
    //position
    sf::Vector2f pos = rect.getPosition();

    int playingScreenHeaderPaddingY = textLoader->getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));
    return pos.y + size.y + playingScreenHeaderPaddingY;
  }
  //if the buy tower is visible it will be the lowest
  else if((this->buyTower)->isCurrentlyVisible()){
    sf::RectangleShape rect = buyTower -> getButtonRect();
    sf::Vector2f size = rect.getSize();
    //position
    sf::Vector2f pos = rect.getPosition();

    int playingScreenHeaderPaddingY = textLoader->getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));
    return pos.y + size.y + playingScreenHeaderPaddingY;
  }
  //otherwise it is one of the normal headers
  else{
    sf::RectangleShape rect = headerVariables.at(0).getButtonRect();
    sf::Vector2f size = rect.getSize();

    int playingScreenHeaderPaddingY = textLoader->getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));
    return size.y + playingScreenHeaderPaddingY;
  }
  */
  //using a normal header for now since the resizing is looking weird
  sf::RectangleShape rect = headerVariables.at(0) -> getButtonRect();
  sf::Vector2f size = rect.getSize();

  int playingScreenHeaderPaddingY = textLoader->getInteger(string("IDS_Playing_Screen_Header_Padding_Y"));
  return size.y + playingScreenHeaderPaddingY;
}


/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void PlayingScreenHeader::registerDelegates(){

  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&PlayingScreenHeader::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_PSH_KP")),keyPressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&PlayingScreenHeader::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_PSH_MP")),mousePressEventType);

  //bind our delegate function for lose hitpoints
  EventManager::EventDelegate lostHitpointsDelegate = std::bind(&PlayingScreenHeader::handleLoseHitpoints, this, _1);

  //make an event and get its type
  LoseHitpointsEvent loseHitpointsEvent = LoseHitpointsEvent();
  EventType loseHitpointsEventType = loseHitpointsEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(lostHitpointsDelegate, textLoader -> getString(string("IDS_PSH_LHP")),loseHitpointsEventType);

  //bind our delegate function for level change
  EventManager::EventDelegate levelChangeDelegate = std::bind(&PlayingScreenHeader::handleLevelChange, this, _1);

  //bind our delegate function for wave change
  EventManager::EventDelegate waveChangeDelegate = std::bind(&PlayingScreenHeader::handleWaveChange, this, _1);

  //make an event and get its type
  WaveChangeEvent waveChangeEvent = WaveChangeEvent();
  EventType waveChangeEventType = waveChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(waveChangeDelegate, textLoader -> getString(string("IDS_PSH_WC")),waveChangeEventType);

}

/*
 * Register events that need to be always registered
 */
void PlayingScreenHeader::registerPersistentDelegates(){
  //bind our delegate function for balance change
  EventManager::EventDelegate balanceChangeDelegate = std::bind(&PlayingScreenHeader::handleBalanceChange, this, _1);

  //make an event and get its type
  BalanceChangeEvent balanceChangeEvent = BalanceChangeEvent();
  EventType balanceChangeEventType = balanceChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(balanceChangeDelegate, textLoader -> getString(string("IDS_PSH_BC")),balanceChangeEventType);

}

/*
 * Deregister the persistent event delegates
 */
void PlayingScreenHeader::deregisterPersistentDelegates(){
  //make an event and get its type
  BalanceChangeEvent balanceChangeEvent = BalanceChangeEvent();
  EventType balanceChangeEventType = balanceChangeEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PSH_BC")),balanceChangeEventType);
}

/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void PlayingScreenHeader::deregisterDelegates(){
  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PSH_KP")),keyPressEventType);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PSH_MP")),mousePressEventType);

  //make an event and get its type
  LoseHitpointsEvent loseHitpointsEvent = LoseHitpointsEvent();
  EventType loseHitpointsEventType = loseHitpointsEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate( textLoader -> getString(string("IDS_PSH_LHP")),loseHitpointsEventType);
  //make an event and get its type
  WaveChangeEvent waveChangeEvent = WaveChangeEvent();
  EventType waveChangeEventType = waveChangeEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate( textLoader -> getString(string("IDS_PSH_WC")),waveChangeEventType);
}

void PlayingScreenHeader::setSelectedTile(int row, int col){
  this->rowSelected = row;
  this->colSelected = col;
}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void PlayingScreenHeader::handleKeyPress(const EventInterface& event){
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

  //if H then we flip the visibility
  if(key == "H"){
    flipVisibility();
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void PlayingScreenHeader::handleMousePress(const EventInterface& event){
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

  //get whether this is a left or right click
  string mouseButtonPressed = mpEventData -> partOfMouse;

  //get the xposition
  float xPos = mpEventData -> x;
  //get the y position
  float yPos = mpEventData -> y;

  //get the size of a tile in the x
  float xTileSize = getTrueXTileSize();
  //get the size of a tile in the y
  float yTileSize = getTrueYTileSize();

  //what row is being clicked
  int row = (int) yPos / yTileSize;
  //what col is being clicked
  int col = (int) xPos / xTileSize;

  //if the playing screen is blocking clicks for some reason
  if(blockClicks){
    return;
  }

  //check if BuyTower button is being clicked
  //modify the xposition to reflect if there is an offset
  //otherwise it will not register the click
  bool buyTowerClicked = (this->buyTower) -> isSelected(xPos,yPos);
  if(buyTowerClicked){

    if(mouseButtonPressed == "Right"){
      buyTower -> mirrorOverY(windowY);
    }
    else{
      shared_ptr<EventInterface> buyTowerState = make_shared<StateChangeEvent>(State::BuyTower, rowSelected, colSelected, true, nowInNano);

      this -> eventManager -> queueEvent(buyTowerState);
    }
    return;
  }

  //check if SellTower button is being clicked
  //modify the xposition to reflect if there is an offset
  //otherwise it will not register the click
  bool sellTowerClicked = (this->sellTower) -> isSelected(xPos,yPos);
  if(sellTowerClicked){
    if(mouseButtonPressed == "Right"){
      sellTower -> mirrorOverY(windowY);
    }
    else{
      shared_ptr<EventInterface> buyTowerState = make_shared<StateChangeEvent>(State::BuyTower, rowSelected, colSelected, false, nowInNano);

      this -> eventManager -> queueEvent(buyTowerState);
    }
    return;
  }

  //if the selected row and column is not the same as the old ones
  //and/or the selected row col is not an existing tower
  //then we hide the sell tower button
  if(row==rowSelected && colSelected == col &&  gameLogic ->isTower(row,col)){
    (this->sellTower)->flipVisibility();
    recaculateHeader = true;
  }
  else if(!(gameLogic->isTower(row,col))){
    if((this->sellTower)->isCurrentlyVisible()){
      (this->sellTower)->flipVisibility();
      recaculateHeader = true;
    }
  }

  //if we have selected the same row and col as the last click then we
  //flip the visibility of the button
  if(row == rowSelected && colSelected == col){
    (this->buyTower)->flipVisibility();
    recaculateHeader = true;
  }
  else{
    if((this->buyTower)->isCurrentlyVisible()){
      (this->buyTower)->flipVisibility();
      recaculateHeader = true;
    }
    rowSelected = row;
    colSelected = col;
  }


  //only check if we are clickinga tile when the cursor is within the game
  //area, subtracting the offset will render some clicks outside
  if(xPos >= 0 && yPos >= 0){
    //change what the buyTower button says depending on the what is at the tile
    if(gameLogic->isTower(rowSelected,colSelected)){
      (this->buyTower) -> setString(textLoader->getString("IDS_Buy_Tower_Existing_Tower"));
      (this->buyTower) -> setButtonPosition(TOPRIGHT);
    }
    else if(gameLogic->isObstacle(rowSelected,colSelected)){
      (this->buyTower) -> setString(textLoader->getString("IDS_Buy_Tower_Existing_Obstacle"));
      (this->buyTower) -> setButtonPosition(TOPRIGHT);
    }
    else if(gameLogic->isEmptySpace(rowSelected,colSelected)){
      (this->buyTower) -> setString(textLoader->getString("IDS_Buy_Tower_Empty_Space"));
      (this->buyTower) -> setButtonPosition(TOPRIGHT);
    }
    //if the tile is a path or exit tile and the button is visible turn it off
    else if(gameLogic->isExit(rowSelected,colSelected) || gameLogic -> isPath(rowSelected,colSelected)) {
      if((this->buyTower)->isCurrentlyVisible()){
          (this->buyTower)->flipVisibility();
          recaculateHeader = true;
      }
      rowSelected = row;
      colSelected = col;
      return;
    }
  }
}

/*
 * Handle any lost hitpoints from enemy units reaching exit
 * @param event: event of the hitpoint loss
 */
void PlayingScreenHeader::handleLoseHitpoints(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * LoseHitpointsEvent type which allows us to access variables and methods
   * specific to LoseHitpointsEvent
   */
  const LoseHitpointsEvent* lhpEvent = static_cast<const LoseHitpointsEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a LoseHitpointsEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  LoseHitpointsEventData* lhpEventData = static_cast<LoseHitpointsEventData*>((lhpEvent -> data).get());
  //get the hitpoints lost from the data
  int lostHitpoints = lhpEventData -> lostHitpoints;

  headerVariableValues.at(0) -= lostHitpoints;

  recaculateHeader=true;
}

/*
 * Handle any change in the balance
 * @param event: event of the balance change
 */
void PlayingScreenHeader::handleBalanceChange(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * BalanceChangeEvent type which allows us to access variables and methods
   * specific to BalanceChangeEvent
   */
  const BalanceChangeEvent* bcEvent = static_cast<const BalanceChangeEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a BalanceChangeEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  BalanceChangeEventData* bcEventData = static_cast<BalanceChangeEventData*>((bcEvent -> data).get());
  //get the balance change
  int balanceChange = bcEventData -> balanceChange;

  assert(headerVariableValues.size() > 1);

  headerVariableValues.at(1) += balanceChange;

  recaculateHeader=true;
}


/*
 * Handle any level change
 * @param event: event of the level change
 */
void PlayingScreenHeader::handleLevelChange(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * LevelChangeEvent type which allows us to access variables and methods
   * specific to LevelChangeEvent
   */
  const LevelChangeEvent* lcEvent = static_cast<const LevelChangeEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a LevelChangeEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  LevelChangeEventData* lcEventData = static_cast<LevelChangeEventData*>((lcEvent -> data).get());
  //get the new level value
  int newLevel = lcEventData -> level;

  headerVariableValues.at(2) = newLevel;

  recaculateHeader=true;
}

/*
 * Handle wave change
 * @param event: event of next wave
 */
void PlayingScreenHeader::handleWaveChange(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * WaveChangeEvent type which allows us to access variables and methods
   * specific to WaveChangeEvent
   */
  const WaveChangeEvent* wcEvent = static_cast<const WaveChangeEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a WaveChangeEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  WaveChangeEventData* wcEventData = static_cast<WaveChangeEventData*>((wcEvent -> data).get());
  //get the new wave
  int newWave = wcEventData -> waveNum;

  headerVariableValues.at(3) = newWave;

  recaculateHeader=true;
}

/*
 * Handle restart game
 * @param event:
 */
void PlayingScreenHeader::handleRestartGame(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * RestartGameEvent type which allows us to access variables and methods
   * specific to RestartGameEvent
   */
  const RestartGameEvent* rgEvent = static_cast<const RestartGameEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a RestartGameEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  RestartGameEventData* rgEventData = static_cast<RestartGameEventData*>((rgEvent -> data).get());

  //reinitlaize all the header buttons so that they use the new values for the
  //player
  initDrawingMaterials();
}

/*
 * Flip the visibility for the screen
 */
void PlayingScreenHeader::flipVisibility(){
  visible = visible == true ? false : true;
}

/*
 * @return the size of an x tile which is determined by the dimensions and whether or
 * not the header is visible
 */
float PlayingScreenHeader::getTrueXTileSize(){
  return gameLogic -> getTileXSize();
}

/*
 * @return the size of an y tile which is determined by the dimensions and whether or
 * not the header is visible
 */
float PlayingScreenHeader::getTrueYTileSize(){
  return gameLogic -> getTileYSize();
}

/*
 * @return the offset in the x direction for the header
 */
float PlayingScreenHeader::getXOffSet(){
  return 0.0;
}

/*
 * @return the offset in the y direction for the header
 */
float PlayingScreenHeader::getYOffSet(){
  return 0.0;
}

/*
 * @return true if the header needs to be recalculated
 */
bool PlayingScreenHeader::headerRecalculated(){
  return recaculateHeader;
}

void PlayingScreenHeader::draw(sf::RenderWindow &window){
  //if something has changed we need to resize the header
  if(recaculateHeader){
    ySize = getMaximumY();
    resetButtons();
    recaculateHeader = false;
    timesHeaderRecalculated++;
  }

  //handle the buy tower and sell tower buttons separately
  if(clicksCheckedFor()){
    drawBuyTowerButton(window);
    drawSellTowerButton(window);
  }
  //draw the rest of the header if it is visible
  if(visible){
    drawHeaderButtons(window);
  }
}


/*
 * Draw the buy tower button
 * @param window: the game window to draw on
 */
void PlayingScreenHeader::drawBuyTowerButton(sf::RenderWindow& window){

  //if the button is invisible do not draw it
  if(!buyTower -> isCurrentlyVisible()){
    return;
  }

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
  //  //cout << "loaded font!" << endl;
  }

  text = buyTower -> getButtonText();
  text.setFont(mainFont);

  window.draw(buyTower -> getButtonRect());
  window.draw(text);
}

/*
 * Draw the sell tower button
 * @param window: the game window to draw on
 */
void PlayingScreenHeader::drawSellTowerButton(sf::RenderWindow& window){

  //if the button is invisible do not draw it
  if(!sellTower -> isCurrentlyVisible()){
    return;
  }

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
  //  //cout << "loaded font!" << endl;
  }

  text = sellTower -> getButtonText();
  text.setFont(mainFont);

  window.draw(sellTower -> getButtonRect());
  window.draw(text);
}

/*
 * Draw all the buttons in the header (hitpoints, balance, level, wave)
 * @param window: the game window to draw on
 */
void PlayingScreenHeader::drawHeaderButtons(sf::RenderWindow& window){
  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
  //  //cout << "loaded font!" << endl;
  }
  for(shared_ptr<Button> toDraw : headerVariables){
    text = toDraw -> getButtonText();
    text.setFont(mainFont);
    window.draw(toDraw -> getButtonRect());
    window.draw(text);
  }
}
