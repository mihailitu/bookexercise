#include "_9_binary_tree_from_inorder_and_postorder.h"

/* Construct a binary tree from given inorder and preorder traversals.
 * Eg:
 *      Inorder sequence: D B E A F C
 *      Preorder sequence: A B D E C F
 */
namespace _problem_9
{
    struct Node {
        char data;
        Node *left;
        Node *right;
        Node(char d) : data(d) {}
    };
}

#include <vector>
void _9_binary_tree_from_inorder_and_postorder()
{
    using namespace _problem_9;
    std::vector<char> inorder = {'D', 'B', 'E', 'A', 'F', 'C'};
    std::vector<char> preorder = {'A', 'B', 'D', 'E', 'C', 'F'};

    Node *root = new Node(preorder[0]);
}
