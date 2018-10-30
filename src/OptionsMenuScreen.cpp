#include "OptionsMenuScreen.hpp"


OptionsMenu::OptionsMenu(int windowX, int windowY, int numItems, sf::Font font) {
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> numItems = numItems;
  this -> font = font;
  /*

  //Options Menu
  if(numItems == 7){
    Screen[0].setFont(font);
    Screen[0].setFillColor(sf::Color::Red);
    Screen[0].setString("School");
    Screen[0].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 1));

    Screen[1].setFont(font);
    Screen[1].setFillColor(sf::Color::White);
    Screen[1].setString("Population");
    Screen[1].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 2));

    Screen[2].setFont(font);
    Screen[2].setFillColor(sf::Color::White);
    Screen[2].setString("Obstacles");
    Screen[2].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 3));

    Screen[3].setFont(font);
    Screen[3].setFillColor(sf::Color::White);
    Screen[3].setString("Waves");
    Screen[3].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 4));

    Screen[4].setFont(font);
    Screen[4].setFillColor(sf::Color::White);
    Screen[4].setString("Start Money");
    Screen[4].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 5));

    Screen[5].setFont(font);
    Screen[5].setFillColor(sf::Color::White);
    Screen[5].setString("Cafetria Size");
    Screen[5].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 6));

    Screen[6].setFont(font);
    Screen[6].setFillColor(sf::Color::White);
    Screen[6].setString("Path Length");
    Screen[6].setPosition(sf::Vector2f(width / 4, height / (numItems + 1) * 7));

    selectedItem = 0;
    */
}

  void OptionsMenu::moveUp()
{
	if (selectedItem - 1 >= 0)
	{
		screen[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		screen[selectedItem].setFillColor(sf::Color::Red);
	}
}

void OptionsMenu::moveDown()
{
	if (selectedItem + 1 < numItems)
	{
		screen[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		screen[selectedItem].setFillColor(sf::Color::Red);
}

}

void OptionsMenu::draw(sf::RenderWindow &window){

}
