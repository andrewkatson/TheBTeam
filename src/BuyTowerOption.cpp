#include "BuyTowerOption.hpp"


BuyTowerOption::BuyTowerOption(shared_ptr<TextLoader> textLoader, float xPos, float yPos,
  float xSize, float ySize, string fontPath, shared_ptr<TowerInterface> towerToShow,
  bool showStats, int windowX, int windowY, bool areBuying, bool isClickable,shared_ptr<EventManager> eventManager){
  this -> textLoader = textLoader;
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> xSize = xSize;
  this -> ySize = ySize;
  this -> fontPath = fontPath;
  this -> towerToShow = towerToShow;
  this -> showStats = showStats;
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> areBuying = areBuying;
  this -> isClickable = isClickable;
  this -> eventManager = eventManager;
  initDrawingMaterials();
}

/*
 * Initalize all the objects used to draw this tower option
 * the rectangle holding the texture and the button holding the text
 * about purchasing/selling
 */
void BuyTowerOption::initDrawingMaterials(){
  initPictureRectangle();
  initChooseButton();
  if(showStats){
    initStatisticsButtons();
  }
  initBackgroundRectangle();
}

/*
 * Initalize the rectangle that holds the texture displaying the tower/obstacle
 */
void BuyTowerOption::initPictureRectangle(){
  towerPictureRect.setSize(sf::Vector2f(xSize, ySize));
  towerPictureRect.setPosition(xPos, yPos);
  //the texture is that of the tower
  //syntax is forced by sfml
  towerPictureRect.setTexture(towerToShow -> getSprite().getTexture());


}

/*
 * Initalize the button that the user selects to buy/sell/upgrade the tower
 */
void BuyTowerOption::initChooseButton(){
  //padding between each button in a tile
  int optionTileButtonPaddingX = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Padding_X"));
  int optionTileButtonPaddingY = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Padding_Y"));

  //position
  sf::Vector2f pos = towerPictureRect.getPosition();
  //dimensions
  sf::Vector2f dimensions = towerPictureRect.getSize();

  //the xPosition is the length of the balance button plus some padding
  float xPos = pos.x;
  //the yPosition is the
  float yPos =  pos.y + dimensions.y + optionTileButtonPaddingY;

  //normal padding for a button we must account for
  int normalButtonXPadding = textLoader->getInteger(string("IDS_Button_Position_Padding"));

  //the full string for what the button will say
  string fullPurchaseString;
  if(areBuying){
    if(showStats){
      fullPurchaseString = textLoader -> getString(string("IDS_Buy_Tower_Option_Tile_Button_Buy"));
    }
    else{
      fullPurchaseString = textLoader -> getString(string("IDS_Buy_Tower_Option_Tile_Button_Obstacle"));
    }
  }
  else{
    fullPurchaseString = textLoader -> getString(string("IDS_Buy_Tower_Option_Tile_Button_Sell"));
  }


  //if we are buying than the number is negative
  if(areBuying){
    fullPurchaseString += string(" -") + to_string(towerToShow->getPrice());
  }
  //if we are selling then the number is positive
  else{
    fullPurchaseString += string(" ") + to_string((int)(towerToShow->getPrice()*textLoader->getDouble(string("IDS_Percentage_Money_Returned_On_Sell_Tower"))));
  }

  string fontpath = textLoader -> getString(string("IDS_SFP"));
  this -> buyOrSell = unique_ptr<Button>(new Button(windowX, windowY, xPos, yPos,
    fullPurchaseString, textLoader, fontpath));

  //if the purchase option is not valid the button is greyed out
  if(isClickable){

      //set the fill color for the button text
      this -> buyOrSell -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Fill_Color_Red")),
      this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Fill_Color_Green")),
      this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Fill_Color_Alpha")));


      //set the outline color for the text
      this -> buyOrSell -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Outline_Color_Red")),
      this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Outline_Color_Green")),
      this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Clickable_Text_Outline_Color_Alpha")));

  }
  else{
    //set the fill color for the button text
    this -> buyOrSell -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Fill_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Fill_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Fill_Color_Alpha")));


    //set the outline color for the text
    this -> buyOrSell -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Outline_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Outline_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_UnClickable_Text_Outline_Color_Alpha")));

  }

  // set the fill color for the button rectangle
  this -> buyOrSell -> setFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> buyOrSell -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->buyOrSell -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Thickness")));

  //set the button text outline thickness
  this->buyOrSell -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Outline_Thickness")));

  //set the text character size
  this->buyOrSell -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Buy_Tower_Option_Tile_Purchase_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->buyOrSell) -> setFont(fontpath);


  //was not setting itself properly
  //the bounding rectangle for the rectangle around the balance button
  sf::RectangleShape ownRect = (this->buyOrSell) -> getButtonRect();

  //position
  sf::Vector2f ownRectPos = ownRect.getPosition();
  //dimensions
  sf::Vector2f ownRecDimensions = ownRect.getSize();

  //the xPosition is the length of the balance button plus some padding
  float newxPos = (dimensions.x - ownRecDimensions.x + normalButtonXPadding)/2 + pos.x;
  //the yPosition is the
  float newyPos =  pos.y + dimensions.y + ownRecDimensions.y;

  //rescale the button and reset it
  (this -> buyOrSell) -> scaleButton( newxPos, newyPos);

}

/*
 * Initliaze the buttons that will show the statistics for the tower
 * only used if this is a buy option
 */
void BuyTowerOption::initStatisticsButtons(){

  //get the statistics for the tower being drawn as an option
  shared_ptr<vector<int>> towerStats = towerToShow -> getStatistics();

  //padding between each button in a tile
  int optionTileButtonPaddingX = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Padding_X"));
  int optionTileButtonPaddingY = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Padding_Y"));

  //normal padding for a button we must account for
  int normalButtonXPadding = textLoader->getInteger(string("IDS_Button_Position_Padding"));

  //position used for all statisticsto orient them in terms of the picture of the tower
  sf::Vector2f towerPictureRectPosition = towerPictureRect.getPosition();
  //dimensions used for all statisticsto orient them in terms of the picture of the tower
  sf::Vector2f towerPictureRectDimensions = towerPictureRect.getSize();

  //the bounding rectangle for the purchase button
  sf::RectangleShape purchaseRect = (this->buyOrSell) -> getButtonRect();

  //position used for initial statstic
  sf::Vector2f pos = purchaseRect.getPosition();
  //dimensions used for initial statistic
  sf::Vector2f dimensions = purchaseRect.getSize();

  //the ypos to use (will change to whatever button is above the current ont)
  float yPosAbove = pos.y;
  //the ySize of the object above
  float yDimensionAbove = dimensions.y;

  //the base for the string changes with the type of tower (ranged or melee)
  string baseIDPath = towerToShow -> isMelee ? "Melee_Tower" : "Range_Tower";

  //base of the text for this statistic button
  string baseText =  string("IDS_Buy_Tower_Option_Tile_Button_") + baseIDPath;

  //iterate through the statistics buttons and initalize them
  for(int i = 0; i < towerStats -> size();i++){

    //the xPosition is the length of the balance button plus some padding
    float xPos = pos.x;
    //the yPosition is the
    float yPos =  yPosAbove + yDimensionAbove;

    //the full title for this statistic
    string statisticsText = textLoader -> getString(baseText + string("_")+to_string(i)) + string(" ")+  to_string(towerStats->at(i));


    assert(statisticsText != "String Not Found");

    string fontpath = textLoader -> getString(string("IDS_SFP"));
    shared_ptr<Button> statToAdd = make_shared<Button>(windowX, windowY, xPos, yPos,
      statisticsText, textLoader, fontpath);

    // set the fill color for the button rectangle
    statToAdd -> setFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Fill_Color_Alpha")));

    // set the outline color for the button
    statToAdd -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Color_Alpha")));

    //set the button outline thickness
    //statToAdd -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Outline_Thickness")));

    //set the fill color for the button text
    statToAdd -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Fill_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Fill_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Fill_Color_Alpha")));


    //set the outline color for the text
    statToAdd -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Outline_Color_Red")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Outline_Color_Green")),
    this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Outline_Color_Alpha")));

    //set the button text outline thickness
    statToAdd -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Outline_Thickness")));

    //set the text character size
    statToAdd -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Text_Size")));

    //set the font inside the button so it can be used to calculate a bounds
    (statToAdd) -> setFont(fontpath);

    //we have to iterate a few times to get the buttons aligned properly
    //the dimensions reset after the button is scaled in its final posisiton
    //so it has to be repositioned, rescaled, then repositioned again
    for(int repeatUntilAligned = 0; repeatUntilAligned < 2; repeatUntilAligned++){
      //was not setting itself properly around the current button
      sf::RectangleShape ownRect = (statToAdd) -> getButtonRect();

      //position
      sf::Vector2f ownRectPos = ownRect.getPosition();
      //dimensions
      sf::Vector2f ownRecDimensions = ownRect.getSize();

      //their xmidpoint
      float towerPicMidpointX = towerPictureRectDimensions.x/2 + towerPictureRectPosition.x;
      //our x midpoint
      float ownRecMidpointX = ownRecDimensions.x/2 + ownRectPos.x;

      //the difference between ours and their
      float difference = towerPicMidpointX - ownRecMidpointX + normalButtonXPadding;

      float newxPos = ownRectPos.x + difference;

      //the yPosition is the
      float newyPos =  yPosAbove + ((yDimensionAbove > ownRecDimensions.y) ? yDimensionAbove : ownRecDimensions.y) + optionTileButtonPaddingY;

      //rescale the button and reset it
      (statToAdd) -> scaleButton( newxPos, newyPos);

    }

    //now add the statistic button
    statisticsButtons.push_back(statToAdd);

    //next time around we use the dimensions and position of the just created statistic button
    //the bounding rectangle for the purchase button
    sf::RectangleShape newPurchaseRect = (statisticsButtons.at(i)) -> getButtonRect();

    //position used for next statistic
    sf::Vector2f newPos  = newPurchaseRect.getPosition();
    //dimensions used for next statistic
    sf::Vector2f newDimensions =  newPurchaseRect.getSize();

    //was not setting itself properly around the current button
    sf::RectangleShape check = (statToAdd) -> getButtonRect();

    //position
    sf::Vector2f checkpos = check.getPosition();
    sf::Vector2f checkdim = check.getSize();
    yPosAbove = newPos.y;
    yDimensionAbove = newDimensions.y;
  }
}

/*
 * Initalize the rectangle that will serve as the background of the
 * tower option and the buy/sell button
 */
void BuyTowerOption::initBackgroundRectangle(){

  //the dimensions that will serve as the background of the rectangle
  sf::Vector2f dimensions = towerPictureRect.getSize();

  //padding in the x and y direction for the options
  float yPadding = (float) textLoader -> getInteger(string("IDS_Buy_Tower_Screen_Options_Padding_Y"));
  float xPadding = (float) textLoader -> getInteger(string("IDS_Buy_Tower_Screen_Options_Padding_X"));

  //our backgrounds dimensions
  float xDim = dimensions.x + 2*xPadding;
  float yDim = dimensions.y + 2*yPadding;
  //our backgrounds position
  float x = xPos - xPadding ;
  float y = yPos - yPadding;

  backgroundRect.setSize(sf::Vector2f(xDim, yDim));
  backgroundRect.setPosition(x, y);

  //set the colors for the outline of the rectangle for the option
  int redComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Outline_Color_Red"));
  int greenComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Outline_Color_Green"));
  int blueComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Outline_Color_Blue"));
  int alphaComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Outline_Color_Alpha"));

  backgroundRect.setOutlineColor(sf::Color(redComponent, greenComponent, blueComponent, alphaComponent));

  //set the outline thickness
  int outlineThickness = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Outline_Thickness"));
  backgroundRect.setOutlineThickness(outlineThickness);

  redComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Fill_Color_Red"));
  greenComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Fill_Color_Green"));
  blueComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Fill_Color_Blue"));
  alphaComponent = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Background_Fill_Color_Alpha"));

  backgroundRect.setFillColor(sf::Color (redComponent, greenComponent, blueComponent, alphaComponent));

}


/*
 * Draw the option to the screen
 * @param window: the screen to draw on
 */
void BuyTowerOption::draw(sf::RenderWindow& window){

  //draw the background for the option
  //window.draw(backgroundRect);

  //draw the rectangle holding the picture
  window.draw(towerPictureRect);

  drawPurchaseButton(window);

  //draw the statistics
  drawStatisticsButtons(window);
}

/*
 * Draw the button to purchase the present choice
 * @param window: the window we draw on
 */
void BuyTowerOption::drawPurchaseButton(sf::RenderWindow& window){
  //if the button is invisible do not draw it
  if(!buyOrSell -> isCurrentlyVisible()){
    return;
  }

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_SFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }

  text = buyOrSell -> getButtonText();
  text.setFont(mainFont);

  window.draw(buyOrSell -> getButtonRect());
  window.draw(text);
}

/*
 * Draw on the screen the buttons with statistics if we want
 * @param window: the window we draw on
 */
void BuyTowerOption::drawStatisticsButtons(sf::RenderWindow& window){
  if(showStats){
    //used to make the font local
    string mainFontPath = textLoader -> getString(string("IDS_SFP"));

    if(!mainFont.loadFromFile(mainFontPath)){
      cout << "No font!" << endl;
    }
    else{
    //  cout << "loaded font!" << endl;
    }

    for(shared_ptr<Button> toDraw: statisticsButtons){
      if(toDraw->isCurrentlyVisible()){
        text = toDraw -> getButtonText();
        text.setFont(mainFont);

        window.draw(toDraw -> getButtonRect());
        window.draw(text);
      }
    }

  }
}


/*
 * Whether the button to buy/sell has been clicked
 */
bool BuyTowerOption::isClicked(float xPos, float yPos){

  if(buyOrSell -> isSelected(xPos, yPos)){

    if(!isClickable) {
      auto now = std::chrono::high_resolution_clock::now();
      //the actual count in nanoseconds for the time
      auto nowInNano = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

      shared_ptr<EventInterface> playSound = make_shared<PlaySoundEvent>("", textLoader->getString("IDS_Failure_Noise"),
                                                                         nowInNano);

      this->eventManager->queueEvent(playSound);
      return false;
    }
    return true;
  }else{
    return false;
  }
}


/*
 * Indicate that a statistic is different from the others displayed alongside it
 * this is called by BuyTowerScreen to indicate what is different between the options
 * @param indexOfStat: the index in the list of statistics that we will be highlighted
 * @param differential: the number of points below the max value of the optiosn that statistic is
 *                      the max is indicated with a 0 and thus is colored green
 */
 void BuyTowerOption::indicateStatDifferential(int indexOfStat, int differential){

   if(differential == 0){
     //set the fill color for the button text
     statisticsButtons.at(indexOfStat) -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Fill_Color_Red")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Fill_Color_Green")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Fill_Color_Blue")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Fill_Color_Alpha")));


     //set the outline color for the text
     statisticsButtons.at(indexOfStat) -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Outline_Color_Red")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Outline_Color_Green")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Positive_Text_Outline_Color_Alpha")));

   }
   else{
     //set the fill color for the button text
     statisticsButtons.at(indexOfStat) -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Fill_Color_Red")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Fill_Color_Green")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Fill_Color_Blue")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Fill_Color_Alpha")));


     //set the outline color for the text
     statisticsButtons.at(indexOfStat) -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Outline_Color_Red")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Outline_Color_Green")),
     this->textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Negative_Text_Outline_Color_Alpha")));

     //we get the string currently in the button and then add on how much negative from the max it is
     sf::Text buttonText = (statisticsButtons).at(indexOfStat) -> getButtonText();
     const string prefix = buttonText.getString();
     string newString = prefix + string(" (") + to_string(differential) + string(")");
     statisticsButtons.at(indexOfStat) -> setString(newString);
   }
 }


/*
 * Realign the buttons that hold statistics
 */
void BuyTowerOption::realignStatButtons(){
  //padding between each button in a tile
  int optionTileButtonPaddingX = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Padding_X"));
  int optionTileButtonPaddingY = textLoader -> getInteger(string("IDS_Buy_Tower_Option_Tile_Button_Padding_Y"));

  //normal padding for a button we must account for
  int normalButtonXPadding = textLoader->getInteger(string("IDS_Button_Position_Padding"));

  //position used for all statisticsto orient them in terms of the picture of the tower
  sf::Vector2f towerPictureRectPosition = towerPictureRect.getPosition();
  //dimensions used for all statisticsto orient them in terms of the picture of the tower
  sf::Vector2f towerPictureRectDimensions = towerPictureRect.getSize();

  //the bounding rectangle for the purchase button
  sf::RectangleShape purchaseRect = (this->buyOrSell) -> getButtonRect();

  //position used for initial statstic
  sf::Vector2f pos = purchaseRect.getPosition();
  //dimensions used for initial statistic
  sf::Vector2f dimensions = purchaseRect.getSize();

  //the ypos to use (will change to whatever button is above the current ont)
  float yPosAbove = pos.y;
  //the ySize of the object above
  float yDimensionAbove = dimensions.y;

  //iterate through the statistics buttons and initalize them
  for(int i = 0; i < statisticsButtons.size();i++){

    //the xPosition is the length of the balance button plus some padding
    float xPos = pos.x;
    //the yPosition is the
    float yPos =  yPosAbove + yDimensionAbove;


    //we have to iterate a few times to get the buttons aligned properly
    //the dimensions reset after the button is scaled in its final posisiton
    //so it has to be repositioned, rescaled, then repositioned again
    for(int repeatUntilAligned = 0; repeatUntilAligned < 2; repeatUntilAligned++){
      //was not setting itself properly around the current button
      sf::RectangleShape ownRect = (statisticsButtons.at(i)) -> getButtonRect();

      //position
      sf::Vector2f ownRectPos = ownRect.getPosition();
      //dimensions
      sf::Vector2f ownRecDimensions = ownRect.getSize();

      //their xmidpoint
      float towerPicMidpointX = towerPictureRectDimensions.x/2 + towerPictureRectPosition.x;
      //our x midpoint
      float ownRecMidpointX = ownRecDimensions.x/2 + ownRectPos.x;

      //the difference between ours and their
      float difference = towerPicMidpointX - ownRecMidpointX + normalButtonXPadding;

      float newxPos = ownRectPos.x + difference;

      //the yPosition is the
      float newyPos =  yPosAbove + ((yDimensionAbove > ownRecDimensions.y) ? yDimensionAbove : ownRecDimensions.y) + optionTileButtonPaddingY;

      //rescale the button and reset it
      (statisticsButtons.at(i)) -> scaleButton( newxPos, newyPos);

    }

    //next time around we use the dimensions and position of the just created statistic button
    //the bounding rectangle for the purchase button
    sf::RectangleShape newPurchaseRect = (statisticsButtons.at(i)) -> getButtonRect();

    //position used for next statistic
    sf::Vector2f newPos  = newPurchaseRect.getPosition();
    //dimensions used for next statistic
    sf::Vector2f newDimensions =  newPurchaseRect.getSize();

    //was not setting itself properly around the current button
    sf::RectangleShape check = (statisticsButtons.at(i)) -> getButtonRect();

    //position
    sf::Vector2f checkpos = check.getPosition();
    sf::Vector2f checkdim = check.getSize();
    yPosAbove = newPos.y;
    yDimensionAbove = newDimensions.y;
  }
}
