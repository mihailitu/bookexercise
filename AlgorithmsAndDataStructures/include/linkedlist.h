#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>
#include <iterator>

template <typename T>
struct node {
    T data;
    node *next = nullptr;
    node *prev = nullptr;
    node(T d) : data(d) {}
};

template <typename T>
class fwiterator : public std::iterator<std::forward_iterator_tag, const node<T>*>
{
    node<T> *data;
public:
    fwiterator() {}
    fwiterator(node<T> *d) : data(d) {}
    fwiterator& operator++() {
        data = data->next;
        return *this;
    }
//    fwiterator operator++(int i) {
//        it++;
//        return it;
//    }

    fwiterator operator--()
    {
        data = data->prev;
        return *this;
    }

    T operator->() {
        return data;
    }

    node<T> * operator*() {
        return data;
    }
};


template <typename T>
class linkedlist
{
    node<T> *head = nullptr;
    node<T> *tail = nullptr;
public:
    fwiterator<node<T>*> iterator;
    linkedlist() {}
    void push_back(node<T> *elem) {
        if (head == nullptr) {
            head = elem;
            tail = head;
            fwiterator<node<T>*>(head);
        } else {
            tail->next = elem;
            elem->prev = tail;
            tail = elem;
        }
    }
    fwiterator<node<T>*>& begin() {
        return iterator;
    }

    fwiterator<node<T>*> end() {
        return fwiterator<node<T>*>(tail);
    }
};


#endif // LINKEDLIST_H
