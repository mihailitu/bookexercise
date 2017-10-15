#ifndef CHAPTER_3_H
#define CHAPTER_3_H

template <typename T>
class Stack
{
    struct Node {
        Node *next;
        T data;
        Node(T item) : next(nullptr), data(item)
        { }
    };
    Node *top = nullptr;
    unsigned size = 0;
public:

    ~Stack() {
        Node *current = top;
        while(current != nullptr) {
            Node *temp = current->next;
            delete current;
            --size;
            current = temp;
        }
    }

    T pop() {
        if(top != nullptr) {
            T data = top->data;
            Node *rm = top;
            top = top->next;
            delete top;
            --size;
            return data;
        } else
            return nullptr;
    }

    void push(T data) {
        Node *n = new Node;
        if (top == nullptr) {
            top = n;
            ++size;
            return;
        } else {
            n->next = top;
            top = n;
        }
    }

    T peek() {
        return top->data;
    }
};

template <typename T>
class Queue
{
    struct Node {
        Node *next;
        T data;
        Node(T item) : next(nullptr), data(item)
        { }
    };
    Node *first = nullptr;
    Node *last = nullptr;
    unsigned size = 0;

public:

    ~Queue() {
        Node *current = first;
        while(current != nullptr) {
            Node *temp = current->next;
            delete current;
            --size;
            current = temp;
        }
    }
    void enqueue(T data) {
        if (first == nullptr) {
            last = new Node(data);
            last->data = data;
            first = last;
        } else {
            last->next = new Node(data);
            last = last->next;
        }
    }

    T dequeue() {
        if ( first != nullptr ) {
            T item = first->data;
            Node *rm = first;
            first = first->next;
            delete rm;
            --size;
            return item;
        }

        return nullptr;
    }
};

void run_chapter_3();

#endif // CHAPTER_3_H
