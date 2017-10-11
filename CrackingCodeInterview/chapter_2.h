#ifndef CHAPTER_2_H
#define CHAPTER_2_H

template<class T>
class LinkedList {

    struct Node {
        Node *next;
        Node *previous;
        T data;
        Node(T item) : next(nullptr),previous(nullptr), data(item)
        {

        }
    };
    unsigned size = 0;
    Node *root = nullptr;

public:
    ~LinkedList() {
        Node *current = root;
        while(current != nullptr) {
            Node *temp = current->next;
            delete current;
            --size;
            current = temp;
        }
    }

    bool empty() { return size == 0; }

    void appendToTail(T data) {
        Node *end = new Node(data);
        Node *n = root;

        ++size;

        if (n == nullptr) {
            root = end;
            return;
        }

        while(n->next != nullptr)
            n = n->next;
        n->next = end;
    }

    void deleteNode(T d) {
        Node *n = root;
        if(n->data == d) {
            delete root;
            --size;
            root = nullptr;
            return;
        }

        while(n->next != nullptr) {
            if(n->next->data == d) {
                Node *rm = n->next;
                n->next = n->next->next;
                delete rm;
                --size;
                return;
            }
            n = n->next;
        }
    }
};

void run_chapter_2();

#endif // CHAPTER_2_H
