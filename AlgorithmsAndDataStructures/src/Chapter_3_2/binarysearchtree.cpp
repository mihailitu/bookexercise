#include <gtest/gtest.h>

template<typename Key, typename Value>
class BinarySearchTree
{
    struct Node {
        Key key;
        Value val;
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        Node(Key _key, Value _val) : key(_key), val(_val)
        {}
    };

    std::shared_ptr<Node> root = nullptr;

    std::shared_ptr<Node> insert(std::shared_ptr<Node> x, Key k, Value v) {
        if (x == nullptr)
            return std::make_shared<Node>(k, v);
        if (k < x->key)
            x->left = insert(x->left, k, v);
        else if (k > x->key)
            x->right = insert(x->right, k, v);
        else
            x->val = v;
        return x;
    }

    void _print(std::shared_ptr<Node> node) const {
        if (node == nullptr)
            return;

        _print(node->left);
        _print(node->right);
        std::cout << "[" << node->key << ", " << node->val << "]\n";
    }
public:
    void add(Key k, Value v) {
        root = insert(root, k, v);
    }

    Value get(Key k) {
        Node x = root;
        while(x != nullptr) {
            if (k < x.key)
                x = x.left;
            else if (k > x.key)
                x = x.right;
            else return x.val;
        }
        return nullptr;
    }
    void remove(Key k);

    void print() const {
        _print(root);
    }
};

TEST(Chapter_3_2, BinarySearchTrees)
{
    std::vector<char> ascii;
    for(unsigned i = 0; i < 255; ++i)
        ascii.push_back(static_cast<char>(i));
    std::random_shuffle(ascii.begin(), ascii.end());
    BinarySearchTree<unsigned char, int> bt;
    for(unsigned char c : ascii)
        bt.add(c, static_cast<int>(c));
    bt.print();

    BinarySearchTree<unsigned char, int> bt1;
    for(unsigned i = 0; i < 255; ++i)
        bt1.add(static_cast<unsigned char>(i), i);
    bt1.print();
}
