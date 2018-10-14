#ifndef MAPFACTORY_H
#define MAPFACTORY_H
#include "Direction.hpp"
#include "MapChoices.hpp"
#include "rngs.hpp"
#include <vector>
#include <memory>
#include <cmath>

using std::unique_ptr;
using std::vector;

class MapFactory{
private:

  unique_ptr<MapChoices> mapCustomizationChoices;

  //x dimension of board
  int xDim;
  //y dimension of board
  int yDim;

  /* the direction the exit is facing
   * so if it is in the right hand column then
   * the direction is Left
   */
  Direction exitDirection;

  //array identifying the exit position
  vector<int> exitPos;

  //array with each entry position
  vector<int> entryPos;

  /* 2d array where any index not related to a path tile
   * is a -1, the exit is 0, and any path is identified with n >= 1
   */
  vector<vector<int>> paths;

  /* 2d array where the index has a value indicating the distance
   * from the exit from that spot. a -1 is used for a tile that is not
   * a tile on a path and 0 is used for the exit. any path tile is
   * assigned a value n >= 1
   */
  vector<vector<int>> distances;

   /* 2d array where the index has a value indicating the texture used
    * on the board at that position. only considers the "floor" so any non path
    * tile, a path tile, or the exit tile. 0 is reserved for the exit. posiitve
    * numbers are for path tiles. negative values are for non path tiles.
    */
   vector<vector<int>> floor;

    /* 2d array where the index has a value indicating the texture used on the
     * board at that position ABOVE the floor level. These values correspond
     * to towers and obstacles. -1 indicates nothing is at this space.
     * 0 is the exit. positive numebers are towers. negative numbers less than
     * -1 are different obstacles
     */
    vector<vector<int>> aboveFloor;

public:

  MapFactory(MapChoices *mapCustomizationChoices, int xDim, int yDim);



  double Equilikely(double a, double b);
  double Geometric(double p);
  double Exponential(double m);
  double Uniform(double a, double b);

};

#endif
