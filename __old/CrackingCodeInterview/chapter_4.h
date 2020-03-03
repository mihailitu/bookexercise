#ifndef CHAPTER_4_H
#define CHAPTER_4_H

#include <iostream>
#include <list>
#include <vector>

template<typename T>
class BinaryTree
{
    struct Node {
        T data;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(T item) : data(item) {}
    };

    Node *root = nullptr;
    Node* _insert(Node *current, T item) {
        if (current == nullptr) {
            current = new Node(item);
        } else if(item < current->data)
            current->left = _insert(current->left, item);
        else
            current->right = _insert(current->right, item);
        return current;
    }

    void _inorder(Node* node) {
        if(node == nullptr)
            return;
        _inorder(node->left);
        std::cout << node->data << std::endl;
        _inorder(node->right);
    }

    void _postorder(Node* node) {
        if (node == nullptr)
            return;
        _postorder(node->left);
        _postorder(node->right);
        std::cout << node->data << std::endl;
    }

    void _preorder(Node *node) {
        if (node == nullptr)
            return;
        std::cout << node->data << std::endl;
        _preorder(node->left);
        _preorder(node->right);
    }

    void rmNode(Node *node) {
        if(node == nullptr)
            return;
        rmNode(node->left);
        rmNode(node->right);
        delete node;
    }

public:

    ~BinaryTree() {
        rmNode(root);
    }

    void insert(T item) {
        if (root == nullptr) {
            root = new Node(item);
            return;
        }
        _insert(root, item);
    }

    void InOrder() {
        std::cout << "InOrder" << std::endl;
        _inorder(root);
    }

    void PostOrder() {
        std::cout << "PostOrder" << std::endl;
        _postorder(root);
    }

    void PreOrder() {
        std::cout << "PreOrder" << std::endl;
        _preorder(root);
    }
};

class Graph
{
    int vNo; // vertices
    std::vector<std::list<int>> adjacentList;
    std::vector<bool> visited;
    void _dfs(int v);
public:
    Graph(int vertices);
    void addEdge(int v, int w);
    void DFS(int v);
    void BFS(int v);


};

void run_chapter_4();

#endif // CHAPTER_4_H
