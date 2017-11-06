#include "_9_binary_tree_from_inorder_and_postorder.h"
#include "binarytree.h"

#include <vector>

using namespace binarytree;

/* Construct a binary tree from given inorder and preorder traversals.
 * Eg:
 *      Inorder sequence: D B E A F C
 *      Preorder sequence: A B D E C F
 */

int findInInorder(const std::vector<char> &v, int start, int end, int value)
{
    for(int i = start; i <= end; ++i)
        if (value == v[i])
            return i;
    // should not get here
    return -1;
}

Node<char>* constructNode(const std::vector<char> &preSeq, const std::vector<char> &inSeq, int inStart, int inEnd)
{
    static int preIndex = 0;

    std::cout << "PreIndex: " << preIndex << " InStart: " << inStart << " InEnd: " << inEnd << std::endl;

    if (inStart > inEnd)
        return nullptr;

    std::cout << "Process node: " << preSeq[preIndex] << std::endl;
    Node<char> *node = new Node<char>(preSeq[preIndex++]);

//    if (preIndex >= preSeq.size())
//        return nullptr;

    if(inStart == inEnd)
        return node;

    int inIndex = findInInorder(inSeq, inStart, inEnd, node->data);

    node->left = constructNode(preSeq, inSeq, inStart, inIndex - 1);
    node->right = constructNode(preSeq, inSeq, inIndex + 1, inEnd);

    return node;
}

void _9_binary_tree_from_inorder_and_postorder()
{
    std::vector<char> inorderSeq = {'D', 'B', 'E', 'A', 'F', 'C'};
    std::vector<char> preorderSeq = {'A', 'B', 'D', 'E', 'C', 'F'};

    Node<char> *root = constructNode(preorderSeq, inorderSeq, 0, inorderSeq.size() - 1);

    inorder(root);

    clearTree(root);
}
