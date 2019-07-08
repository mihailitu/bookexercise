#include "ringbuffer.h"

#include <iostream>
#include <limits>

void testRingBuffer()
{
    const int rbSz = 6;
    ringbuffer rb(rbSz);

    rb.enqueue(14);
    rb.enqueue(22);
    rb.enqueue(13);
    rb.enqueue(-6);

    rb.printBuffer();

    std::cout << "Deq: " << rb.dequeue() <<  ' ' << rb.dequeue() << std::endl;

    rb.enqueue(9);
    rb.enqueue(20);
    rb.enqueue(5);

    rb.printBuffer();

    rb.enqueue(20);
}

ringbuffer::ringbuffer(int sz) : size(sz)
{
    if(sz <= 0)
        size = 1024;

    data.resize(size);
}

bool ringbuffer::enqueue(int val)
{
    if (full) {
        std::cout << "full" << '\n';
        return false;
    }

    if ((startPointer == 0 && endPointer == size - 1) ||
            (endPointer == startPointer - 1 )) {
        std::cout << "full" << '\n';
        full = true;
        return false;
    } else
        if (startPointer == -1) {
            startPointer = endPointer = 0;
            data[endPointer] = val;
        } else
            if (endPointer == size - 1 && startPointer != 0) {
                endPointer = 0;
                data[endPointer] = val;
            } else {
                ++endPointer;
                data[endPointer] = val;
            }
    empty = false;
    return true;
}

int ringbuffer::dequeue()
{
    full = false;

    if (empty) {
        std::cout << "Empty" << '\n';
        return std::numeric_limits<int>::max();
    }

    if (startPointer == -1) {
        std::cout << "Empty" << '\n';
        empty = true;
        return std::numeric_limits<int>::max();
    }

    int ret = data[startPointer];

    if(startPointer == endPointer) {
        startPointer = endPointer = -1;
        empty = true;
    } else
        if (startPointer == size -1)
            startPointer = 0;
    else
            ++startPointer;

    return ret;
}

void ringbuffer::printBuffer()
{
    if(empty) {
        std::cout << "Buffer empty!" << std::endl;
        return;
    }

    int i = startPointer;
    while(i != endPointer) {
        std::cout << data[i] << ' ';
        ++i;
        if(i == size)
            i = 0;
    }

    std::cout << data[endPointer] << ' ';

    std::cout << std::endl;
}
