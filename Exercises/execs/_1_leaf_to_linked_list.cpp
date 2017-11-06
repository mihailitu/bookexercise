#include "_1_leaf_to_linked_list.h"
#include "binarytree.h"
#include <iostream>
#include <list>

using namespace binarytree;

bool isLeaf(Node<int>* node) {
    return (node->left == nullptr && node->right == nullptr);
}

template <typename T>
void inorder(Node<T>* node, std::list<Node<T>*> &list)
{
    if(node == nullptr)
        return;

    if (isLeaf(node))
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

    Node<int> *root = new Node<int>(1);
    root->left = new Node<int>(2);
    root->right = new Node<int>(3);
    root->left->left = new Node<int>(4);
    root->left->right = new Node<int>(5);
    root->right->right = new Node<int>(6);
    root->left->left->left = new Node<int>(7);
    root->left->left->right = new Node<int>(8);
    root->right->right->left = new Node<int>(9);
    root->right->right->right = new Node<int>(10);
    std::list<Node<int>*> dllist;
    inorder(root, dllist);
    for(auto i : dllist)
        std::cout << i->data << " ";

    clearTree(root);
}
