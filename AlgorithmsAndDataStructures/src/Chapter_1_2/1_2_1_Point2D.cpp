// #include "fundamentals.h"
#include "gtest.h"

#include <random>
/**
 * @brief _1_2_1_Point_2D
 * 1.2.1 Write a Point2D client that takes an integer value N from the command line,
 * generates N random points in the unit square, and computes the distance separating
 * the closest pair of points.
 */
struct Point2D {
    int x;
    int y;
};

std::vector<Point2D> create_random_points_vector(int N)
{

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 1000);

    std::vector<Point2D> points;
    for(int i = 0; i < N; ++i) {
        points.push_back({dis(gen), dis(gen)});
    }
    return points;
}

// calculate distance between two 2D points
double calcDistance(const Point2D &p1, const Point2D &p2)
{
    return std::sqrt(
                ((p2.x - p1.x) * (p2.x - p1.x)) +
                ((p2.y - p1.y) * (p2.y - p1.y)));
}

// compare x coordinate for sorting
bool compareX(const Point2D &p, const Point2D &q) {
    return p.x < q.x;
}

// compare y coordinate for sorting
bool compareY(const Point2D &p, const Point2D &q) {
    return p.y < q.y;
}

// Complexity: O(n^2)
std::pair<int, int> _1_2_1_Point_2D(const std::vector<Point2D> &points)
{
    if (points.size() <= 1) { // we need at least two points
        throw std::runtime_error("We need at least two points");
    }
    unsigned closestP1Index = 0;
    unsigned closestP2Index = 0;
    double overallMinDistance = std::numeric_limits<double>::max();

    for(unsigned i = 0; i < points.size() - 1; ++i) {
        double minDistance = std::numeric_limits<double>::max();
        unsigned closestTo_i = 0;
        for(unsigned j = i + 1; j < points.size(); ++j) {
            double distance = calcDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestTo_i = j;
            }
        }
        if(overallMinDistance >= minDistance) {
            closestP1Index = i;
            closestP2Index = closestTo_i;
            overallMinDistance = minDistance;
        }
    }

    fprintf(stdout, "Closest distance (%4f) is between: {%d, %d} and {%d, %d} (%d, %d)\n", overallMinDistance,
            points[closestP1Index].x, points[closestP1Index].y, points[closestP2Index].x, points[closestP2Index].y,
            closestP1Index, closestP2Index);
    return {closestP1Index, closestP2Index};
}

/* A utility function to find the distance beween the closest points of strip of given size.
 * All points in strip[] are sorted according to y coordinate.
 * They all have an upper bound on minimum distance as d.
 * Note that this method seems to be a O(n^2) method, but it's a O(n)
 * method as the inner loop runs at most 6 times
 */
double stripClosest(std::vector<Point2D> strip, double d)
{
    double min = d;
    std::sort(strip.begin(), strip.end(), compareY);

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (unsigned i = 0; i < strip.size(); ++i)
         for (unsigned j = i+1; j < strip.size() && (strip[j].y - strip[i].y) < min; ++j)
             if (calcDistance(strip[i],strip[j]) < min)
                 min = calcDistance(strip[i], strip[j]);

     return min;
}

// O(n log(n)):
// https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
std::pair<int, int> _1_2_1_Point_2D_divide_and_conquer(const std::vector<Point2D> &points) {

    return {};
}

TEST(Fundamentals, _1_2_1_Point2D){

    std::vector<Point2D> points = {
        {1, 1}, {1, 2}, {100, 100}, {200, 200}
    };

    std::pair<int, int> result = _1_2_1_Point_2D(points);
    ASSERT_TRUE(result.first == 0 && result.second == 1);

    auto dcPoints = points; //for divide and conquer approach, the list of pointers has to be sorted on x
    std::sort(dcPoints.begin(), dcPoints.end(), compareX);
    result = _1_2_1_Point_2D_divide_and_conquer(dcPoints);
    ASSERT_TRUE(result.first == 0 && result.second == 1);

    points = {
        {1, 1}, {1, 2}
    };

    result = _1_2_1_Point_2D(points);
    ASSERT_TRUE(result.first == 0 && result.second == 1);

    dcPoints = points; //for divide and conquer approach, the list of pointers has to be sorted on x
    std::sort(dcPoints.begin(), dcPoints.end(), compareX);
    result = _1_2_1_Point_2D_divide_and_conquer(dcPoints);
    ASSERT_TRUE(result.first == 0 && result.second == 1);

    points = create_random_points_vector(120);
    auto r1 = _1_2_1_Point_2D(points);

    dcPoints = points; //for divide and conquer approach, the list of pointers has to be sorted on x
    std::sort(dcPoints.begin(), dcPoints.end(), compareX);
    auto r2 = _1_2_1_Point_2D_divide_and_conquer(dcPoints);
    ASSERT_TRUE((r1.first == r2.first) && (r1.second == r2.second));
}
