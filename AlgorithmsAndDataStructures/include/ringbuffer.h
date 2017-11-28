#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>

/*
 * 1.3.39 Ring buffer. A ring buffer, or circular queue, is a FIFO data structure of a fixed size N.
 * It is useful for transferring data between asynchronous processes or for storing log files.
 * When the buffer is empty, the consumer waits until data is deposited; when the buffer is full,
 * the producer waits to deposit data.
 *
 * Develop an API for a RingBuffer and an implementation that uses an array representation (with circular wrap-around).
 */

// template <typename T>
class ringbuffer
{
    std::vector<int> data;
    unsigned startPointer = 0;
    unsigned endPointer = 0;
    unsigned size = 0;

    bool empty = true;
    bool full = false;
public:
    ringbuffer(int sz);
    bool enqueue(int val);
    int dequeue();
    void printBuffer();
    bool isEmpty() const {
        return empty;
    }

    bool isFull() const {
        return full;
    }
};

void testRingBuffer();

#endif // RINGBUFFER_H
