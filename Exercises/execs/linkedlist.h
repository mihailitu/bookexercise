#ifndef LINKEDLIST_H
#define LINKEDLIST_H

namespace linkedlist {

template <typename T>
struct Node
{
    T data;
    Node *next = nullptr;
    Node *previous = nullptr;
    Node(T d) : data(d) { }
};

} // namespace linkedlist

#endif // LINKEDLIST_H
