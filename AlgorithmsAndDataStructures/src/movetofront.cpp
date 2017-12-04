#include "movetofront.h"

#include <iostream>
#include <algorithm>

/* 1.3.40 Move-to-front.
 * Read in a sequence of characters from standard input and maintain the characters in a linked list with no duplicates.
 * When you read in a previously unseen character, insert it at the front of the list.
 * When you read in a duplicate character, delete it from the list and reinsert it at the beginning.
 *
 * Name your program MoveToFront: it implements the well-known move-to-front strategy, which is useful for caching, data compression,
 * and many other applications where items that have been recently accessed are more likely to be reaccessed.
 *
 * Test:
 * input: a, b, c, d, b, c
 * output: c, b, d, a
 */

void push(std::list<char> &q, char c)
{
    auto it = std::find(q.begin(), q.end(), c);
    if (it == q.end())
        q.push_front(c);
    else {
        q.erase(it);
        q.push_front(c);
    }
}

void testMoveToFront()
{
    std::list<char> mf;
    for(char c : {'a', 'b', 'c', 'd', 'b', 'c'})
        push(mf, c);

    for(auto c : mf)
        std::cout << c << ' ';
    std::cout << std::endl;
}
