#include "_11_one_mil_linked_list.h"
#include "linkedlist.h"

#include <iostream>

/* How will you implement linked list with 1 million nodes? How will you access 999999 th node?
 * Give some optimal design strategy and implementation.
 */

/* A linked list has fairly few variations, because much variation means it would be something other than a linked list.
 * You can vary it by having single or double linking. Single linking is where you have a pointer to the head (the first node, A say) which points to B which points to C, etc.
 * To turn that into a double linked list you would also add a link from C to B and B to A.
 *
 * If you have a double linked list then it's meaningful to retain a pointer to the list tail (the last node) as well as the head,
 * which means accessing the last element is cheap, and elements near the end are cheaper, because you can work backwards or forwards...
 * BUT... you would need to know what you want is at the end of the list...
 * AND at the end of the day a linked list is still just that,
 * and if it is going to get very large and that is a problem because of the nature of its use case,
 * then a storage structure other than a linked list should probably be chosen.
 */

using namespace linkedlist;

void _11_one_mil_linked_list()
{
    const int maxList = 1000000;
    const int findEl = 999996;
    Node<int> *head = new Node<int>(0);

    Node<int> *previous = head;
    int listCount = 1;
    for(int i = 1; i < maxList; ++i) {
        Node<int> *node = new Node<int>(i);
        node->previous = previous;
        previous->next = node;
        previous = node;
        ++listCount;
    }

    Node<int> *tail = previous;

    Node<int> *current = tail;
    int count = maxList;
    while(current->previous != nullptr && --count != findEl) {
        current = current->previous;
    }
    std::cout << current->data << std::endl;
}
