#include "rover.h"

#include <iostream>

Rover::Rover(int _id, Compass _positioning, int _posX, int _posY, const std::string &_steps, int _mapW, int _mapH) :
    id(_id), steps(_steps),
    mapW(_mapW), mapH(_mapH)
{
    currentPosition = {_posX, _posY, _positioning};
}


RoverPosition Rover::Process(const std::map<int, RoverPosition> &usedLocations)
{
    for(char c : steps) {
        switch(c) {
        case 'L': {
            rotateLeft();
            break;
        }
        case 'R': {
            rotateRight();
            break;
        }
        case 'M': {
            move(usedLocations);
            break;
        }
        }
    }
    return currentPosition;
}

void Rover::move(const std::map<int, RoverPosition> &usedLocations)
{
    int nextX = currentPosition.x;
    int nextY = currentPosition.y;
    switch (currentPosition.heading) {
    case East: {
        nextX += 1;
        break;
    }
    case South: {
        nextY -= 1;
        break;
    }
    case West: {
        nextX -= 1;
        break;
    }
    case North: {
        nextY += 1;
        break;
    }
    }

    if (!isValidLocation(id, nextX, nextY, mapW, mapH, usedLocations))
        return;

    currentPosition.x = nextX;
    currentPosition.y = nextY;
}

// verifies if (newLocX, newLocY) location is valid:
// - is inside plateau boundaries
// - no other rover is in that location
bool isValidLocation(int id, int newLocX, int newLocY, int mapW, int mapH, const std::map<int, RoverPosition> &usedLocations)
{
    // make sure we are not moving outside designated area (mapW and mapH are included in the area)
    if (newLocX < 0 || newLocX > mapW)
        return false;

    if (newLocY < 0 || newLocY > mapH)
        return false;

    // make sure that the next cell is empty. We don't want to crash the rovers
    for(auto &loc : usedLocations)
        if(loc.first != id && loc.second.x == newLocX && loc.second.y == newLocY)
            return false;

    return true;
}

void Rover::rotateLeft()
{
    switch (currentPosition.heading) {
    case East: {
        currentPosition.heading = North;
        break;
    }
    case South: {
        currentPosition.heading = East;
        break;
    }
    case West: {
        currentPosition.heading = South;
        break;
    }
    case North: {
        currentPosition.heading = West;
        break;
    }
    }
}

void Rover::rotateRight()
{
    switch (currentPosition.heading) {
    case East: {
        currentPosition.heading = South;
        break;
    }
    case South: {
        currentPosition.heading = West;
        break;
    }
    case West: {
        currentPosition.heading = North;
        break;
    }
    case North: {
        currentPosition.heading = East;
        break;
    }
    }
}

char compassToChar(Compass heading)
{
    switch (heading) {
    case East: {
        heading = South;
        return 'S';
    }
    case South: {
        heading = West;
        return 'W';
    }
    case West: {
        heading = North;
        return 'N';
    }
    case North: {
        heading = East;
        return 'E';
    }
    }
}
