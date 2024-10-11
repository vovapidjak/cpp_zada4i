#include <iostream>
#include <string>
#include <queue>

// Шаблон класса для узла бинарного дерева
template <typename T>
class TreeNode {
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Шаблон класса для бинарного дерева
template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

    void addHelper(TreeNode<T>*& node, T value) {
        if (node == nullptr) {
            node = new TreeNode<T>(value);
        } else if (value < node->data) {
            addHelper(node->left, value);
        } else {
            addHelper(node->right, value);
        }
    }

    bool searchHelper(TreeNode<T>* node, T value) {
        if (node == nullptr) {
            return false;
        } else if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }

    void inOrderHelper(TreeNode<T>* node) {
        if (node != nullptr) {
            inOrderHelper(node->left);
            std::cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void add(T value) {
        addHelper(root, value);
    }

    bool search(T value) {
        return searchHelper(root, value);
    }

    void inOrderTraversal() {
        inOrderHelper(root);
        std::cout << std::endl;
    }
};

int main() {
    BinaryTree<int> intTree;
    intTree.add(5);
    intTree.add(3);
    intTree.add(7);
    intTree.add(1);
    intTree.add(4);
    intTree.add(6);
    intTree.add(8);

    std::cout << "In-order traversal of integer tree: ";
    intTree.inOrderTraversal();

    std::cout << "Search 4 in integer tree: " << (intTree.search(4) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 10 in integer tree: " << (intTree.search(10) ? "Found" : "Not Found") << std::endl;

    BinaryTree<std::string> stringTree;
    stringTree.add("kal1");
    stringTree.add("kal2");
    stringTree.add("kal3");
    stringTree.add("akl4");
    stringTree.add("kal5");
    stringTree.add("kal6");
    stringTree.add("kal7");

    std::cout << "In-order traversal of string tree: ";
    stringTree.inOrderTraversal();

    std::cout << "Search 'date' in string tree: " << (stringTree.search("kal1") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'mango' in string tree: " << (stringTree.search("kal2") ? "Found" : "Not Found") << std::endl;

    return 0;
}