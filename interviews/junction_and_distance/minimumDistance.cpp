/**
Amazon Fresh is a grocery delivery services that offers consumers the option of purchasing their groceries online having them delivered on schedule. The Amazon Fresh team is planning a route for a delivery truck to deliver customer orders in the city of Techlandia. The planner will create a delivery area for each order to effectively plan the route. The area is abstracted as a grid. Not all locations are accesible by road. The truck only needs to make a single delivery.

Write an algorithm to determine the minimum distance required for the truck to deliver the order.

Assumptions:
* Some places in the delivery area cannot be accesed by the driver, as there are no roads into those locations.
* The delivery area can be represented as a two-dimensional grid of integers, where each integer represents one cell.
* The truck must start from the top-left corner of the area, which is always accesible, and can move one cell up, down, left or right at a time.
* The truck must navigate around the areas without roads and cannot leave the area.
* The accesible areas are represented as 1, areas without roads are represented by 0 and the order destination is represented by 9.

Input:
The input to the function/method consists of three arguments:
    - numRows, an integer representing the number of numRows;
    - numColumns, an integer representing the number of columns;
    - area, representing the two-dimensional grid of integers.

Output:
    - return an integer representing the total distance traversed to deliver the order, else return -1

Constrains:
    1 <= numRows, numColumns <= 1000

Example:
    Input:
        numRows=3
        numRows = 3
        area =
        [[1, 0, 0],
         [1, 0, 0],
         [1, 9, 1]]
 */

int minimumDistance(int /*numRows*/, int /*numColumns*/, int **/*area*/)
{
    return -1;
}
