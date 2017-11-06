#include "_9_binary_tree_from_inorder_and_postorder.h"

#include "ex_util.h"

using namespace ex_util;

/* Construct a binary tree from given inorder and preorder traversals.
 * Eg:
 *      Inorder sequence: D B E A F C
 *      Preorder sequence: A B D E C F
 */

#include <vector>
void _9_binary_tree_from_inorder_and_postorder()
{
    std::vector<char> inorder = {'D', 'B', 'E', 'A', 'F', 'C'};
    std::vector<char> preorder = {'A', 'B', 'D', 'E', 'C', 'F'};

    Node<char> *root = new Node<char>(preorder[0]);

    clearTree(root);
}
