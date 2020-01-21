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

    enum class ParseOrder {
        PREORDER,
        INORDER,
        POSTORDER
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

    void _print(std::shared_ptr<Node> node, ParseOrder order) const {
        if (node == nullptr)
            return;

        if (order == ParseOrder::PREORDER)
            std::cout << "[" << node->key << ", " << node->val << "], ";

        _print(node->left, order);

        if (order == ParseOrder::INORDER)
            std::cout << "[" << node->key << ", " << node->val << "], ";

        _print(node->right, order);

        if (order == ParseOrder::POSTORDER)
            std::cout << "[" << node->key << ", " << node->val << "], ";

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

    Value min() const {
        std::shared_ptr<Node> x = root;
        while(x != nullptr) {
            if (x->left == nullptr)
                return x->val;
            x = x->left;
        }
        throw std::runtime_error("Empty BST");
    }

    Value max() const {
        std::shared_ptr<Node> x = root;
        while(x != nullptr) {
            if (x->right == nullptr)
                return x->val;
            x = x->right;
        }
        throw std::runtime_error("Empty BST");
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void remove(Key k);

    void print_inorder() const {
        std::cout << "INORDER\n";
        _print(root, ParseOrder::INORDER);
        std::cout << "\n";
    }
    void print_preorder() const {
        std::cout << "PREORDER\n";
        _print(root, ParseOrder::PREORDER);
        std::cout << "\n";
    }
    void print_postorder() const {
        std::cout << "POSTORDER\n";
        _print(root, ParseOrder::POSTORDER);
        std::cout << "\n";
    }

};

TEST(Chapter_3_2, BinarySearchTrees)
{
    std::vector<char> ascii;
    for(unsigned i = 97; i <= 122; ++i)
        ascii.push_back(static_cast<char>(i));
    std::random_shuffle(ascii.begin(), ascii.end());

    BinarySearchTree<unsigned char, int> bt;
    for(unsigned char c : ascii) {
        std::cout << "[" << c << ", " << static_cast<int>(c) << "]\n";
        bt.add(c, static_cast<int>(c));
    }

    bt.print_preorder();
    bt.print_inorder();
    bt.print_postorder();

    std::cout << "Min: " << bt.min() << "\n";
    std::cout << "Max: " << bt.max() << "\n";

    BinarySearchTree<unsigned char, int> bt1;

    try {
        std::cout << "Min: " << bt1.min() << "\n";
        std::cout << "Max: " << bt1.max() << "\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

//    BinarySearchTree<unsigned char, int> bt1;
//    for(unsigned i = 0; i < 256; ++i)
//        bt1.add(static_cast<unsigned char>(i), i);
//    bt1.print();
}
