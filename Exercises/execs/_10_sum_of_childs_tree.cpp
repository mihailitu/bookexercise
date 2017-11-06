#include "_10_sum_of_childs_tree.h"

#include "binarytree.h"

#include <iostream>

/* Return a tree such that each internal node stores sum of all its child nodes. Each leaf node stores zero.
 *
 *              50
 *            /     \
 *          /         \
 *        7             2
 *      / \             /\
 *    /     \          /   \
 *   3        5      1      30
 *
 * Resulting BT:
 *              39
 *            /     \
 *          /         \
 *        8             31
 *      / \             /\
 *    /     \          /   \
 *   3        5      1      30
 */

using namespace binarytree;

void postordersum(Node<int> *node)
{
    if(node == nullptr)
        return;

    postordersum(node->left);
    postordersum(node->right);

    if (!isLeaf(node))
        node->data = 0;
    if(node->left != nullptr)
        node->data += node->left->data;
    if (node->right != nullptr)
        node->data += node->right->data;
}

void _10_sum_of_childs_tree()
{
    Node<int> *root = new Node<int>(50);
    root->left = new Node<int>(7); root->right = new Node<int>(2);
    root->left->left = new Node<int>(3); root->left->right = new Node<int>(5);
    root->right->left = new Node<int>(1); root->right->right = new Node<int>(30);

    inorder(root);
    std::cout << std::endl;
    postorder(root);
    std::cout << std::endl;
    postordersum(root);
    std::cout << std::endl;
    inorder(root);
}
