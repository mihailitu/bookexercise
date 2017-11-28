#include "_54_josephus_problem.h"

#include <iostream>
#include <list>
/*
 * Josephus problem: People are standing in a circle waiting to be executed.
 * Counting begins at a specified point in the circle and proceeds around the circle in a specified direction.
 * After a specified number of people are skipped, the next person is executed.
 * The procedure is repeated with the remaining people, starting with the next person,
 * going in the same direction and skipping the same number of people, until only one person remains, and is freed.
 *
 * The problem — given the number of people, starting point, direction, and number to be skipped —
 * is to choose the position in the initial circle to avoid execution.
 *
 * Eg: N = 7, K = 2
 * result: 1 3 5 0 4 2 eliminated, 6 saved
 */

void _54_josephus_problem()
{
    int N = 7;
    int K = 3;

    std::list<int> josephus_list;
    for(int i = 0; i < N; ++i)
        josephus_list.push_back(i);

    int elim = 1;
    auto current = josephus_list.begin();
    while(josephus_list.size() > 1) {
        if(current == josephus_list.end())
            current = josephus_list.begin();
        if(elim == K) {
            std::cout << *current << ' ';
            current = josephus_list.erase(current);
            elim = 1;
        } else {
            ++elim;
            ++current;// = std::next(current);
        }
    }
    std::cout << std::endl;
    std::cout << "Pos: " << *josephus_list.begin() << std::endl;
}
