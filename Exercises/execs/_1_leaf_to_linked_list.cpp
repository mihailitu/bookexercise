#include "_1_leaf_to_linked_list.h"
#include <iostream>
#include <list>

struct Node {
    int data;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int d) : data(d) {}
};

Node* insert(Node *current, int data)
{
    if (current == nullptr)
        current = new Node(data);
    else
        if (data < current->data)
            current->left = insert(current->left, data);
    else
            current->right = insert(current->right, data);
    return current;
}

bool isLeaf(Node* node) {
    return (node->left == nullptr && node->right == nullptr);
}

void inorder(Node* node, std::list<Node*> &list)
{
    if(node == nullptr)
        return;
    if(isLeaf(node))
        list.push_back(node);
    inorder(node->left, list);
    // std::cout << node->data << std::endl;
    inorder(node->right, list);
}

/* 1. Save all leaf nodes of a Binary tree in a Doubly Linked List by using Right node as Next node and Left Node as Previous Node.

Let the following be input binary tree
        1
     /     \
    2       3
   / \       \
  4   5       6
 / \         / \
7   8       9   10


Output:
Doubly Linked List
7<->8<->5<->9<->10
*/
void _1_leaf_to_linked_list()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    root->left->left->left = new Node(7);
    root->left->left->right = new Node(8);
    root->right->right->left = new Node(9);
    root->right->right->right = new Node(10);
    std::list<Node*> dllist;
    inorder(root, dllist);
    for(auto i : dllist)
        std::cout << i->data << " ";
}
