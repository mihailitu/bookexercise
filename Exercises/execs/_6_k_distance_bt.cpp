#include "_6_k_distance_bt.h"
#include <list>
#include <vector>
#include <iostream>
#include <stack>

namespace problem_6
{
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

void clearTree(Node* node)
{
    if(node == nullptr)
        return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}
} // namespace problem_6

/* Find all nodes at k-distance from a given node in a binary tree
 * Eg: Given binay tree:
 *          20
 *        /   \
 *       8     22
 *     /  \
 *    4   12
 *       /  \
 *      10  14
 * Input: target = pointer to node with data 8.
 *        root = pointer to node with data 20.
 *        k = 2.
 * Output : 10 14 22
 *
 * If target is 14 and k is 3, then output should be "4 20"
 */
using namespace problem_6;
void find_downwards(Node *node, int k, std::vector<Node*> &result)
{
    if (node == nullptr)
        return;
    if (k == 0) {
        result.push_back(node);
        return;
    }

    find_downwards(node->left, k - 1, result);
    find_downwards(node->right, k - 1, result);
}

bool build_parent_list(Node *root, Node *target, std::stack<std::pair<Node*, bool>> &parents)
{
    if(root == nullptr) {
        return false; // leaf node. Target not found
    }
    if(root->data == target->data)
        return true; // target found. Unwind

    parents.push(std::pair<Node*, bool> (root, true));
    if(build_parent_list(root->left, target, parents))
        return true;

    parents.pop();
    parents.push(std::pair<Node*, bool> (root, false));
    if(build_parent_list(root->right, target, parents)) {
        return true;
    }

    parents.pop();
    return false;
}

void _6_k_distance_bt()
{
    int k = 2;
    Node *root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);

    Node *target = root->left;

    std::cout << "Target node: " << target->data << std::endl;

    std::vector<Node*> result;
    find_downwards(target, k, result);

    std::stack<std::pair<Node*, bool>> parents;
    build_parent_list(root, target, parents);

    int kk = k - 1;
    while(!parents.empty()) {
        std::pair<Node*, bool> top = parents.top();
        Node *parent = top.first;
        if(kk == 0) {
            result.push_back(parent);
            break;
        }
        if(top.second) // left == true, go to the right branch
            find_downwards(parent->right, kk - 1, result);
        else
            find_downwards(parent->left, kk - 1, result);
        parents.pop();
        --kk;
    }

    for(auto i : result)
        std::cout << i->data << ' ';
    std::cout << std::endl;


    clearTree(root);
}
