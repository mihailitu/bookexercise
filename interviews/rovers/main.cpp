#include <iostream>

using namespace std;
/*
 * Rovers
A squad of robotic rovers are to be landed by NASA on a different planets like Mars, Pluto
etc.
You are responsible to land and operate the rovers sent for Mars plateau. This plateau,
which is curiously flat and rectangular, must be navigated by the rovers so that their on-
board cameras can get a complete view of the surrounding terrain to send back to Earth.
A rover&#39;s position is represented by a combination of an x and y co-ordinates and a letter
representing one of the four cardinal compass points. The plateau is divided up into a grid of
cells to simplify navigation. An example position might be 0, 0, N, which means the rover is
in the bottom left corner and facing North.
In order to control a rover, NASA sends a simple string of letters. The possible letters are &#39;L&#39;,
&#39;R&#39; and &#39;M&#39;. &#39;L&#39; and &#39;R&#39; makes the rover spin 90 degrees left or right respectively, without
moving from its current spot.
&#39;M&#39; means move forward one grid cell, and maintain the same heading.
Assume that the square directly North from (x, y) is (x, y+1).
Also assume that each cell size is 1 sq-cm and individual rover occupies the entire cell.

Input:
The first line of input is the upper-right coordinates of the plateau, the lower-left
coordinates are assumed to be 0,0.
The rest of the input is information pertaining to the rovers that have been deployed. Each
rover has two lines of input. The first line gives the rover&#39;s position, and the second line is a
series of instructions telling the rover how to explore the plateau.
The position is made up of two integers and a letter separated by spaces, corresponding to
the x and y co-ordinates and the rover&#39;s orientation.
Each rover will be finished sequentially, which means that the second rover won&#39;t start to
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
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
