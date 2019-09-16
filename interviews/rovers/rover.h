#ifndef ROVER_H
#define ROVER_H

#include <map>
#include <vector>
#include <string>

struct cell {
    int x;
    int y;
};

class rover
{
    // the id of each rover is the position in the input file
    int id;
    int posX, posY;
    int mapW, mapH;
public:
    rover(int _id, int _posX, int _posY, int _mapW, int _mapH);
    void process(const std::string &steps, const std::map<int, std::vector<cell>> &locations);
};

#endif // ROVER_H
