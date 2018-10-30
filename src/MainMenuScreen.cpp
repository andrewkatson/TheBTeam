#include "MainMenuScreen.hpp"

MainMenuScreen::MainMenuScreen(int windowX, int windowY, int numItems, sf::Font font){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> font = font;

  for(int i = 0; i < numItems; i++){
    sf::Text text;
    screen.push_back(text);
  }
  //Main Menu
  if(numItems == 3){
    screen[0].setFont(font);
    screen[0].setFillColor(sf::Color::Red);
    screen[0].setString("Play");
    screen[0].setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 1));

    screen[1].setFont(font);
    screen[1].setFillColor(sf::Color::White);
    screen[1].setString("Options");
    screen[1].setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 2));

    screen[2].setFont(font);
    screen[2].setFillColor(sf::Color::White);
    screen[2].setString("Exit");
    screen[2].setPosition(sf::Vector2f(windowX / 2, windowY / (numItems + 1) * 3));

  }
}

void MainMenuScreen::draw(sf::RenderWindow &window){

  for(int i = 0; i < numItems; i++){
    //window.draw(screen.at(i));
    //cout << i << endl;
    //cout << "d" << endl;
  }

}
void MainMenuScreen::moveUp()
{
if (selectedItem - 1 >= 0)
{
  screen[selectedItem].setColor(sf::Color::White);
  selectedItem--;
  screen[selectedItem].setColor(sf::Color::Red);
}
}

void MainMenuScreen::moveDown()
{
if (selectedItem + 1 < numItems)
{
  screen[selectedItem].setColor(sf::Color::White);
  selectedItem++;
  screen[selectedItem].setColor(sf::Color::Red);
}

}
