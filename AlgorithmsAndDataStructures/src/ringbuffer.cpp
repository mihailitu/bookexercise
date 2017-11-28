#include "ringbuffer.h"

#include <iostream>
#include <limits>

void testRingBuffer()
{
    ringbuffer rb(10);
    for(unsigned i = 0; i < 10; ++i)
        rb.enqueue(i);
    rb.printBuffer();
}

ringbuffer::ringbuffer(int sz) : size(sz)
{
    if(sz <= 0)
        size = 1024;

    data.resize(size);
}

bool ringbuffer::enqueue(int val)
{
    if(full)
        return false;

    if(endPointer + 1 == startPointer) {
        full = true;
        return false;
    }

    empty = false;

    data[endPointer] = val;
    ++endPointer;

    if(endPointer == size) {// round robin
        endPointer = 0;
    }

    return true;
}

int ringbuffer::dequeue()
{
    if (empty) {
        return std::numeric_limits<int>::max();
    }

    if(startPointer + 1 == endPointer) {
        empty = true;
    }

    int ret = data[startPointer];
    ++startPointer;

    if(startPointer == size - 1)
        startPointer = 0;

    return ret;
}

void ringbuffer::printBuffer()
{
    if(empty) {
        std::cout << "Buffer empty!" << std::endl;
        return;
    }

    unsigned i = startPointer;
    while(i != endPointer) {
        std::cout << i << ' ';
        ++i;
        if(i == size)
            i = 0;
    }
}
