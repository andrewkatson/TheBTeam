#include "MainMenuScreen.hpp"

MainMenuScreen::MainMenuScreen(int windowX, int windowY, int numItems,shared_ptr<TextLoader> textLoader){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> textLoader = textLoader;

  //get the path for the main font
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

  //load the main font
  if(!font.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
    cout << "loaded font!" << endl;
  }
  this -> initText();


}

void MainMenuScreen::initText(){

  //make a text object for numItems
  for(int i = 0; i < numItems; i++){
    sf::Text text;
    screen.push_back(text);
  }
  //Main Menu
  if(numItems == 3){
    screen.at(0).setFont(font);
    screen.at(0).setFillColor(sf::Color::Red);
    screen.at(0).setString("Play");
    screen.at(0).setCharacterSize(24);
    screen.at(0).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 1));

    screen.at(1).setFont(font);
    screen.at(1).setFillColor(sf::Color::White);
    screen.at(1).setString("Options");
    screen.at(1).setCharacterSize(24);
    screen.at(1).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 2));

    screen.at(2).setFont(font);
    screen.at(2).setFillColor(sf::Color::White);
    screen.at(2).setString("Exit");
    screen.at(2).setCharacterSize(24);
    screen.at(2).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 3));

  }
}

void MainMenuScreen::draw(sf::RenderWindow &window){
  window.clear();

  vector<sf::Text> s;
  //make a text object for numItems
  for(int i = 0; i < numItems; i++){
    sf::Text text;
    s.push_back(text);
  }
  //Main Menu
  if(numItems == 3){
    s.at(0).setFont(font);
    s.at(0).setFillColor(sf::Color::Red);
    s.at(0).setString("Play");
    s.at(0).setCharacterSize(24);
    s.at(0).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 1));

    s.at(1).setFont(font);
    s.at(1).setFillColor(sf::Color::White);
    s.at(1).setString("Options");
    s.at(1).setCharacterSize(24);
    s.at(1).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 2));

    s.at(2).setFont(font);
    s.at(2).setFillColor(sf::Color::White);
    s.at(2).setString("Exit");
    s.at(2).setCharacterSize(24);
    s.at(2).setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 3));

  }

  for(int i = 0; i < numItems; i++){
    //window.draw(screen.at(i));
    window.draw(s.at(i));
  }
  window.display();
}
void MainMenuScreen::moveUp()
{
if (selectedItem - 1 >= 0)
{
  screen[selectedItem].setFillColor(sf::Color::White);
  selectedItem--;
  screen[selectedItem].setFillColor(sf::Color::Red);
}
}

void MainMenuScreen::moveDown()
{
if (selectedItem + 1 < numItems)
{
  screen[selectedItem].setFillColor(sf::Color::White);
  selectedItem++;
  screen[selectedItem].setFillColor(sf::Color::Red);
}

}
