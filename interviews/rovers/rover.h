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

struct RoverPosition {
    int x;
    int y;
    Compass heading;
};

class Rover
{
    // the id of each rover is the position in the input file
    int id;
    std::string steps;
    int mapW, mapH;
    RoverPosition currentPosition;
public:
    Rover(int _id, Compass _positioning, int _posX, int _posY, const std::string &_steps, int _mapW, int _mapH);
    RoverPosition Process(const std::map<int, RoverPosition> &usedLocations);
    int GetID() const {
        return id;
    }

    RoverPosition GetCurrentPosition() const {
        return currentPosition;
    }

private:
    void rotateLeft();
    void rotateRight();

    void move(const std::map<int, RoverPosition> &usedLocations);
};

bool isValidLocation(int id, int newLocX, int newLocY, int mapW, int mapH, const std::map<int, RoverPosition> &usedLocations);
char compassToChar(Compass heading);
#endif // ROVER_H
