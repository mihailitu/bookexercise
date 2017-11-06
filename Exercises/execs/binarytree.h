#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

namespace binarytree {
template <typename T>
struct Node {
    T data;
    Node *left;
    Node *right;
    explicit Node(T d) : data(d) {}
};

template <typename T>
void inorder(Node<T> *node)
{
    if(node == nullptr)
        return;

    inorder(node->left);
    std::cout << node->data << ' ';
    inorder(node->right);
}

template <typename T>
void postorder(Node<T> *node)
{
    if(node == nullptr)
        return;

    inorder(node->left);
    inorder(node->right);
    std::cout << node->data << ' ';
}

template <typename T>
void preorder(Node<T> *node)
{
    if(node == nullptr)
        return;

    std::cout << node->data << ' ';
    inorder(node->left);
    inorder(node->right);
}

template <typename T>
void clearTree(Node<T> *node)
{
    if(node == nullptr)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

} // namespace binarytree

#endif // BINARYTREE_H
