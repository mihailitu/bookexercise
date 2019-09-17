#include <iostream>

using namespace std;
/*
 * Rovers
A squad of robotic rovers are to be landed by NASA on a different planets like Mars, Pluto
etc.
You are responsible to land and operate the rovers sent for Mars plateau. This plateau,
which is curiously flat and rectangular, must be navigated by the rovers so that their on-
board cameras can get a complete view of the surrounding terrain to send back to Earth.
A rover's position is represented by a combination of an x and y co-ordinates and a letter
representing one of the four cardinal compass points. The plateau is divided up into a grid of
cells to simplify navigation. An example position might be 0, 0, N, which means the rover is
in the bottom left corner and facing North.
In order to control a rover, NASA sends a simple string of letters. The possible letters are 'L', 'R' and 'M'
'L' and 'R' makes the rover spin 90 degrees left or right respectively, without
moving from its current spot.
'M' means move forward one grid cell, and maintain the same heading.
Assume that the square directly North from (x, y) is (x, y+1).
Also assume that each cell size is 1 sq-cm and individual rover occupies the entire cell.

Input:
The first line of input is the upper-right coordinates of the plateau, the lower-left
coordinates are assumed to be 0,0.
The rest of the input is information pertaining to the rovers that have been deployed. Each
rover has two lines of input. The first line gives the rover's position, and the second line is a
series of instructions telling the rover how to explore the plateau.
The position is made up of two integers and a letter separated by spaces, corresponding to
the x and y co-ordinates and the rover's orientation.
Each rover will be finished sequentially, which means that the second rover won't start to
move until the first one has finished moving.

Output:
The trail of rover has to be recorded in an output TXT file including each Rovers final
coordinates and heading.

Part example of Test Input for Rover in TXT i/p file:
5 5
1 2 N
LMLMLMLMM
3 3 E
MMRMMRMRRM

Part example of Expected Output for addressed Rover in TXT o/p file:
1 3 N
5 1 E

Bonus part of Rovers C++ Task
At-least 4 rovers are on plateau at any time.
*/

#include "rover.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

// Read input file and stores each line in a string
std::vector<std::string> readInputFile(const std::string &fileName);

// Decodes the size of the grid and verifies integrity
bool readPlateauSize(const std::string &data, int &mapW, int &mapH);

// Decodes rover's initial position and verifies integrity
bool readRoversInitialPosition(int roverId, const std::string &data, int &x, int &y, Compass &heading, int mapW, int mapH, const std::map<int, RoverPosition> &others);

// Verifies integrity of rover's commands
bool checkMovementDataIntegrity(const std::string &data);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: rovers <input>" << '\n';
        return -1;
    }

    std::string fileName = argv[1];

    std::vector<std::string> inputData = readInputFile(fileName);

    if (inputData.size() < 3) {// we need at least: plateau size, one rover's position and commands
        std::cerr << "Insufficient data! Retry transmission." << '\n';
        return -1;
    }

    int mapW, mapH;
    if (!readPlateauSize(inputData[0], mapW, mapH)) {
        std::cerr << "Malformed data! Retry transmission." << '\n';
        return -1;
    }

    // holds the position of each rover (the initial or the final position)
    // so, for each step, we can check for collisions
    std::map<int, RoverPosition> positions;

    // rovers list, as constructed from input file
    std::vector<Rover> rovers;

    // Start building the rovers. Each rover has two lines of data
    int roverID = 0;
    for(unsigned i = 1; i < inputData.size(); i += 2) {
        if (i + 1 >= inputData.size()) {// the file is incomplete
            std::cerr << "Malformed data for rover " << roverID << "! We won't use it!" << '\n';
            break;
        }

        int posX, posY;
        Compass heading;
        if (!readRoversInitialPosition(roverID, inputData[i], posX, posY, heading, mapW, mapH, positions)) {
            std::cerr << "Malformed data for rover " << roverID << "! We won't use it!" << '\n';
            continue;
        }

        std::string movementData = inputData[i+1];

        if (!checkMovementDataIntegrity(movementData)) {
            std::cerr << "Malformed data for rover " << roverID << "! We won't use it!" << '\n';
            continue;
        }
        rovers.push_back(Rover(roverID, heading, posX, posY, movementData, mapW, mapH));
        positions[roverID] = {posX, posY, heading};

        ++roverID;
    }

    for(Rover &r : rovers) {
        RoverPosition final = r.Process(positions); // process rover actions
        positions[r.GetID()] = final; // update locations that are in use
    }

    for(auto pos : positions) {
        std::cout << pos.second.x << ' ' << pos.second.y << ' ' << compassToChar(pos.second.heading) << '\n';
    }

    ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed to open output file" << '\n';
        return -1;
    }

    for(auto &r : rovers) {
        RoverPosition pos = r.GetCurrentPosition();
        out << pos.x << ' ' << pos.y << ' ' << compassToChar(pos.heading) << '\n';
    }

    out.close();

    return 0;
}

std::vector<std::string> readInputFile(const std::string &fileName)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open " << fileName << "\n";
        return {};
    }

    std::vector<std::string> inputData;
    std::string line;
    // read the file line by line
    while(std::getline(inputFile, line))
        inputData.push_back(line);

    inputFile.close();

    return inputData;
}

bool readPlateauSize(const std::string &data, int &mapW, int &mapH)
{
    std::stringstream parser(data);
    if (!parser) {
        return false;
    }

    parser >> mapW;
    if (!parser)
        return false;

    parser >> mapH;
    if (!parser)
        return false;

    // negative numbers are not allowed
    if (mapW < 0 || mapH < 0)
        return false;

    // plateau size of (0, 0) can be valid: one rover may just look around without moving
    return true;
}

bool readRoversInitialPosition(int roverId, const std::string &data, int &x, int &y, Compass &heading, int mapW, int mapH, const std::map<int, RoverPosition> &others)
{
    std::stringstream parser(data);
    if (!parser)
        return false;

    parser >> x;
    if (!parser)
        return false;

    parser >> y;
    if (!parser)
        return false;

    char c;
    parser >> c;
    if (!parser)
        return false;

    switch(c) {
    case 'E': {
        heading = Compass::East;
        break;
    }
    case 'S': {
        heading = Compass::South;
        break;
    }
    case 'W': {
        heading = Compass::West;
        break;
    }
    case 'N': {
        heading = Compass::North;
        break;
    }
    default:
        return false;
    }

    return isValidLocation(roverId, x, y, mapW, mapH, others);
}

bool checkMovementDataIntegrity(const std::string &data)
{
    for(char c : data)
        if ((c != 'L') && (c != 'R') && c != ('M'))
            return false;
    return true;
}
