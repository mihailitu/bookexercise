#include "gtest/gtest.h"
#include "../rover.h"

TEST(Rover, RotateLeftTest)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "L", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::West);
}

TEST(Rover, RotateLeft360Test)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "LLLL", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::North);
}

TEST(Rover, RotateRightTest)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "R", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::East);
}

TEST(Rover, RotateRight360Test)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "RRRR", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::North);
}

TEST(Rover, MoveTest)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "MM", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::North);
    ASSERT_EQ(pos.y, 1);
}

TEST(Rover, CrashTest)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "MM", 1, 1);
    usedLocations[0] = {0, 0, Compass::North};

    Rover r1(1, Compass::South, 0, 1, "MM", 1, 1);
    usedLocations[1] = {0, 1, Compass::South};

    RoverPosition rPos = r.Process(usedLocations);
    RoverPosition r1Pos = r1.Process(usedLocations);

    ASSERT_TRUE(rPos.x == 0 && rPos.y == 0);
    ASSERT_TRUE(r1Pos.x == 0 && r1Pos.y == 1);
}

TEST(Rover, BoundariesTest)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::South, 0, 0, "MMM", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::South);
    ASSERT_EQ(pos.y, 0);
    ASSERT_EQ(pos.x, 0);
}

TEST(Rover, IgnoreWrongCommandTest)
{
    std::map<int, RoverPosition> usedLocations;

    Rover r(0, Compass::North, 0, 0, "A", 1, 1);
    r.Process(usedLocations);

    RoverPosition pos = r.GetCurrentPosition();
    ASSERT_EQ(pos.heading, Compass::North);
}

