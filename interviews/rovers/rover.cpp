#include "rover.h"

#include <iostream>

Rover::Rover(int _id, Compass _positioning, int _posX, int _posY, int _mapW, int _mapH) :
    id(_id), mapW(_mapW), mapH(_mapH)
{
    currentPosition = {_posX, _posY, _positioning};
    trail.push_back(currentPosition);
}

void Rover::UploadCommands(const std::string &_steps)
{
    steps += _steps;
}

RoverPosition Rover::ProcessCommands(const std::map<int, RoverPosition> &usedLocations)
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
    steps = "";
    return currentPosition;
}

void Rover::move(const std::map<int, RoverPosition> &usedLocations)
{
    int nextX = currentPosition.x;
    int nextY = currentPosition.y;
    switch (currentPosition.heading) {
    case Compass::East: {
        nextX += 1;
        break;
    }
    case Compass::South: {
        nextY -= 1;
        break;
    }
    case Compass::West: {
        nextX -= 1;
        break;
    }
    case Compass::North: {
        nextY += 1;
        break;
    }
    }

    if (!isValidLocation(id, nextX, nextY, mapW, mapH, usedLocations))
        return;

    currentPosition.x = nextX;
    currentPosition.y = nextY;

    trail.push_back(currentPosition);
}

void Rover::rotateLeft()
{
    switch (currentPosition.heading) {
    case Compass::East: {
        currentPosition.heading = Compass::North;
        break;
    }
    case Compass::South: {
        currentPosition.heading = Compass::East;
        break;
    }
    case Compass::West: {
        currentPosition.heading = Compass::South;
        break;
    }
    case Compass::North: {
        currentPosition.heading = Compass::West;
        break;
    }
    }
    trail.push_back(currentPosition);
}

void Rover::rotateRight()
{
    switch (currentPosition.heading) {
    case Compass::East: {
        currentPosition.heading = Compass::South;
        break;
    }
    case Compass::South: {
        currentPosition.heading = Compass::West;
        break;
    }
    case Compass::West: {
        currentPosition.heading = Compass::North;
        break;
    }
    case Compass::North: {
        currentPosition.heading = Compass::East;
        break;
    }
    }
    trail.push_back(currentPosition);
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

char compassToChar(Compass heading)
{
    switch (heading) {
    case Compass::East: {
        return 'S';
    }
    case Compass::South: {
        return 'W';
    }
    case Compass::West: {
        return 'N';
    }
    case Compass::North: {
        return 'E';
    }
    }
    return ' ';
}
