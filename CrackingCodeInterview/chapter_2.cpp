#include "chapter_2.h"

#include <iostream>

template<class T>
class LinkedList {

    struct Node {
        Node *next;
        Node *previous;
        T data;
    };
    unsigned size = 0;
    Node *root = nullptr;

public:
    LinkedList() {
    }

    bool empty() { return size == 0; }

    void appendToTail(T data) {
        Node *end = new Node;
        end->data = data;
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
};

//class Node {
//    Node *next = nullptr;
//    int data;

//public:
//    Node( int d ) : data( d ) {}

//    void appendToTail( int d ) {
//        Node *end = new Node(d);
//        Node *n = this;
//        while( n->next != nullptr )
//            n = n->next;

//        n->next = end;
//    }

//    Node* deleteNode(Node *head, int d) {
//        Node *n = head;

//        if (n->data == d)
//            return head->next;

//        while (n->next != nullptr) {
//            if (n->next->data == d) {
//                n->next = n->next->next;
//                return head;
//            }
//            n = n->next;
//        }
//        return head;
//    }
//};

#include <list>

void run_chapter_2()
{
    std::list<int> lll;
    lll.push_back(4);
    std::cout << lll.size();

    LinkedList<int> ll;

    ll.appendToTail(5);
    ll.appendToTail(7);
}
