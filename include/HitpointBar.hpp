/*
 * HitpointBar.hpp
 *
 * Purpose: Handle hitpoint bar rendering
 *
 * @author Jeremy Elkayam
 */

#ifndef CSCI437_HITPOINTBAR_HPP
#define CSCI437_HITPOINTBAR_HPP

#include <SFML/Graphics.hpp>

class HitpointBar {

private:

  //The portion of the health bar that is filled in.
  sf::RectangleShape filledRect;

  //The portion of the health bar that is empty.
  sf::RectangleShape emptyRect;

public:

  /*
   * Set up the attributes of the health bar.
   */
  HitpointBar();

  /*
   *
   *
   * @return the portion of the rectangle that's filled
   */
  sf::RectangleShape getFilled();

  /*
   *
   * @return the portion of the rectangle that's empty
   */
  sf::RectangleShape getEmpty();

};


#endif //CSCI437_HITPOINTBAR_HPP
