#ifndef MAPCHOICES_H
#define MAPCHOICES_H

enum class cafeteria {Elementary=1, Middle=2, High=3};
class MapChoices {
public:
  //number of obstacles on the board
  int obstacleChoice;
  //the specific level of school (lower numbers are easier)
  cafeteria cafeteriaChoice;
  //number of entries on the board
  int pathEntryChoice;

  MapChoices(int obstacles, cafeteria cafeteria, int entries);
};

#endif
