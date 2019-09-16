#include "rover.h"

#include <iostream>

Rover::Rover(int _id, Compass _positioning, int _posX, int _posY, const std::string &_steps, int _mapW, int _mapH) :
    id(_id), steps(_steps),
    mapW(_mapW), mapH(_mapH)
{
    currentPosition = {_posX, _posY, _positioning};
}


mars_cell Rover::process(const std::map<int, mars_cell> &usedLocations)
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
    return {};
}

void Rover::move(const std::map<int, mars_cell> &usedLocations)
{
    int nextX = currentPosition.x;
    int nextY = currentPosition.y;
    switch (currentPosition.positioning) {
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

    // make sure we are not moving outside designated area
    if (nextX < 0 || nextX >= mapW)
        return;

    if (nextY < 0 || nextY >= mapH)
        return;

    // make sure that the next cell is empty. We don't want to crash the rovers
    for(auto &loc : usedLocations)
        if(loc.second.x == nextX && loc.second.y == nextY)
            return;

    currentPosition.x = nextX;
    currentPosition.y = nextY;
}

void Rover::rotateLeft()
{
    switch (currentPosition.positioning) {
    case East: {
        currentPosition.positioning = North;
        break;
    }
    case South: {
        currentPosition.positioning = East;
        break;
    }
    case West: {
        currentPosition.positioning = South;
        break;
    }
    case North: {
        currentPosition.positioning = West;
        break;
    }

    }
}

void Rover::rotateRight()
{
    switch (currentPosition.positioning) {
    case East: {
        currentPosition.positioning = South;
        break;
    }
    case South: {
        currentPosition.positioning = West;
        break;
    }
    case West: {
        currentPosition.positioning = North;
        break;
    }
    case North: {
        currentPosition.positioning = East;
        break;
    }

    }
}
