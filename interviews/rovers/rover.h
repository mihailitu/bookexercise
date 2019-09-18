#ifndef ROVER_H
#define ROVER_H

#include <map>
#include <vector>
#include <string>

enum class Compass {
    East,
    South,
    West,
    North
};

// Position of the rover at any given time
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

    // Keep a trail of the rover's moves
    std::vector<RoverPosition> trail;
public:
    Rover(int _id, Compass _positioning, int _posX, int _posY, int _mapW, int _mapH);

    void UploadCommands(const std::string &_steps);

    // Process all command from 'steps'
    RoverPosition ProcessCommands(const std::map<int, RoverPosition> &usedLocations);
    int GetID() const {
        return id;
    }

    RoverPosition GetCurrentPosition() const {
        return currentPosition;
    }

    std::vector<RoverPosition> Trail() const {
        return trail;
    }

private:
    void rotateLeft();
    void rotateRight();

    void move(const std::map<int, RoverPosition> &usedLocations);
};

// Check if the location given by (newLocX, newLocY) can be used
bool isValidLocation(int id, int newLocX, int newLocY, int mapW, int mapH, const std::map<int, RoverPosition> &usedLocations);

// Encodes 'heading' into a E, S, W, N character
char compassToChar(Compass heading);
#endif // ROVER_H
