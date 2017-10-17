#include "_6_k_distance_bt.h"
#include <list>

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
/* Find all nodes at k-distance from a given node in a binary tree */
void _6_k_distance_bt()
{
    using namespace problem_6;
}
