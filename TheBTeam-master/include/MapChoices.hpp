#ifndef MAPCHOICES_H
#define MAPCHOICES_H

class MapChoices {
public:
  //number of obstacles on the board
  int obstacleChoice;
  //the specific level of school (lower numbers are easier)
  int cafeteriaChoice;
  //number of entries on the board
  int pathEntryChoice;

  MapChoices(int obstacles, int cafeteria, int entries);
};

#endif
