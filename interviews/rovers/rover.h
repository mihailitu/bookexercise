#ifndef ROVER_H
#define ROVER_H

#include <map>
#include <vector>
#include <string>

enum Compass {
    East,
    South,
    West,
    North
};

struct mars_cell {
    int x;
    int y;
    Compass positioning;
};

class Rover
{
    // the id of each rover is the position in the input file
    int id;
    Compass positioning;
    int posX, posY;
    std::string steps;
    int mapW, mapH;
    mars_cell currentPosition;
public:
    Rover(int _id, Compass _positioning, int _posX, int _posY, const std::string &_steps, int _mapW, int _mapH);
    mars_cell process(const std::map<int, mars_cell> &usedLocations);

private:
    void rotateLeft();
    void rotateRight();

    void move(const std::map<int, mars_cell> &usedLocations);
};

#endif // ROVER_H
