#include "_10_sum_of_childs_tree.h"

#include "binarytree.h"

#include <iostream>

/* Given an arbitrary binary tree, convert it to a binary tree that holds Children Sum Property.
 * You can only increment data values in any node (You cannot change structure of tree and cannot decrement value of any node).
 *
 * For example, the below tree doesn’t hold the children sum property, convert it to a tree that holds the property.
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
 *           50
 *         /    \
 *       /        \
 *     19           31
 *    / \           /  \
 /     \       /      \
14      5     1       30
 */

using namespace binarytree;

void _10_sum_of_childs_tree()
{
    Node<int> *root = new Node<int>(50);
    root->left = new Node<int>(7); root->right = new Node<int>(2);
    root->left->left = new Node<int>(3); root->left->right = new Node<int>(5);
    root->right->left = new Node<int>(1); root->right->right = new Node<int>(30);
}
