#pragma once
/*
 * Loads in the vector of options for each selectable option in the OptionsMenuScreen similar
 * to how the texture loader goes about it.
 *
 */
#include "SFML/Graphics.hpp"
#include<string>
#include<vector>
#include<iostream>
#include "TextLoader.hpp"

using std::to_string;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::vector;
class Switcher{
private:
    sf::Font font;
    sf::Text text;
    int id;
    std::vector<string> options;
    int len;
    int selected;
protected:
    int windowX;
    int windowY;
public:
    Switcher(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader,int windowX, int windowY, sf::Font font, int id, int len);
    void initText();
    void changeSelected(int direction);
    void getSelected();
    void getID();
    void draw();
};
