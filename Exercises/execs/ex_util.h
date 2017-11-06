#ifndef EX_UTIL_H
#define EX_UTIL_H

#include <iostream>

namespace ex_util {
template <typename T>
struct Node {
    T data;
    Node *left;
    Node *right;
    explicit Node(T d) : data(d) {}
};

template <typename T>
void inorder(Node<T>* node)
{
    if(node == nullptr)
        return;

    inorder(node->left);
    std::cout << node->data << std::endl;
    inorder(node->right);
}

template <typename T>
void postorder(Node<T> *node)
{
    if(node == nullptr)
        return;

    inorder(node->left);
    inorder(node->right);
    std::cout << node->data << std::endl;
}

template <typename T>
void preorder(Node<T> *node)
{
    if(node == nullptr)
        return;

    std::cout << node->data << std::endl;
    inorder(node->left);
    inorder(node->right);
}

template <typename T>
void clearTree(Node<T>* node)
{
    if(node == nullptr)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

} // namespace EX_UTIL_H

#endif // EX_UTILITY_H
