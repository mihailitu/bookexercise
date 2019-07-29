#ifndef BAG_IMPL_H
#define BAG_IMPL_H

#include <iterator>

template<class T>
struct baglist
{
    baglist *next = nullptr;
    baglist *previous = nullptr;
    T item;
};

/**
 * bag class, using a linked list
 */
template<class T> class bag {
    class bag_iterator {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef bag value_type;
        typedef std::size_t difference_type;
        typedef bag* pointer;
        typedef bag& reference;

        bag_iterator() {}
        bag_iterator begin() {
            return bag_iterator();
        }
    };

public:
    bag();
    ~bag();
    void add(T item);
    void remove(T item);
    bool exists(T item);
    bool isEmpty();
    unsigned size();

private:
    unsigned count;
    baglist<T> *root;
    baglist<T> *tail;
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
        root = new baglist<T>;
        tail = root;
    }

    baglist<T> *elem = new baglist<T>;
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

    baglist<T> *current = root->next;
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
