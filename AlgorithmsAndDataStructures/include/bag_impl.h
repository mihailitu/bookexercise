#ifndef BAG_IMPL_H
#define BAG_IMPL_H

#include <iterator>

template<class T>
struct bag_elem
{
    bag_elem *next = nullptr;
    bag_elem *previous = nullptr;
    T item;
};

/**
 * bag class, using a linked list
 */
template<class T> class bag {
    class bag_iterator {

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;

        bag_iterator() {}
    };

public:
    bag();
    ~bag();
    void add(T item);
    void remove(T item);
    bool exists(T item);
    bool isEmpty();
    unsigned size();

    bag_iterator begin() {
        return it;
    }
private:
    bag_iterator it;
    unsigned count;
    bag_elem<T> *root;
    bag_elem<T> *tail;
};

template<class T>
bag<T>::bag() : count(0), root(nullptr), tail(nullptr)
{
}

template<class T>
bag<T>::~bag()
{
    while(root != nullptr) {
        auto next = root->next;
        delete root;
        root = next;
    }
    root = tail = nullptr;
}

template<class T>
void bag<T>::add(T item)
{
    if(root == nullptr) {
        root = new bag_elem<T>;
        tail = root;
    }

    bag_elem<T> *elem = new bag_elem<T>;
    elem->item = item;
    elem->previous = tail;
    tail->next = elem;
    tail = elem;
    ++count;
}

template<class T>
void bag<T>::remove(T item)
{
    if (count == 0)
        return;

    if(count == 1) {
        if (root->item == item) {
            delete root;
            root = nullptr;
            tail = nullptr;
            count = 0;
        }
    }

    bag_elem<T> *current = root->next;
    while(current != tail) {
        if(current->item == item) {
            current->previous->next = current->next;
            current->next->previous = current->previous;
            auto next = current->next;
            delete current;
            current = next;
            --count;
        }
        current = current->next;
    }

    if (current == tail && current->item == item) {
        tail = tail->previous;
        tail->next = nullptr;
        delete current;
        return;
    }
}

template<class T>
unsigned bag<T>::size()
{
    return count;
}

template<class T>
bool bag<T>::exists(T item)
{
    auto current = root;
    while(current != nullptr) {
        if(current->item == item)
            return true;
        current = current->next;
    }
    return false;
}

template<class T>
bool bag<T>::isEmpty()
{
    return count == 0;
}

#endif // BAG_IMPL_H
