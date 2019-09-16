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

struct MarsCell {
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
    MarsCell currentPosition;
public:
    Rover(int _id, Compass _positioning, int _posX, int _posY, const std::string &_steps, int _mapW, int _mapH);
    MarsCell Process(const std::map<int, MarsCell> &usedLocations);
    int GetID() {
        return id;
    }

private:
    void rotateLeft();
    void rotateRight();

    void move(const std::map<int, MarsCell> &usedLocations);
};

bool isValidLocation(int newLocX, int newLocY, int mapW, int mapH, const std::map<int, MarsCell> &usedLocations);

#endif // ROVER_H
