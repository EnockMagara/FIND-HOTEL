

// bst.hpp
#ifndef BST_HPP
#define BST_HPP

#include <vector>
#include "hotel.h"

// Node class for the Binary Search Tree
template <typename T1, typename T2>
class Node {
    public:
        T1 key; // Key of the node
        std::vector<T2> value; // Value of the node
        Node<T1,T2>* left; // Pointer to the left child
        Node<T1,T2>* right; // Pointer to the right child
        Node<T1,T2>* parent; // Pointer to the parent node

        // Constructor for the Node class
        Node(T1 key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Binary Search Tree class
template <typename T1, typename T2>
class BST {
    private:
        Node<T1,T2>* root; // Root of the BST

        // Helper function for inOrderTraversal
        template <typename Func>
        void inOrderTraversalHelper(Node<T1,T2>* ptr, Func func) {
            if (ptr != nullptr) {
                inOrderTraversalHelper(ptr->left, func); // Traverse the left subtree
                for (const auto& value : ptr->value) {
                    func(value); // Apply the function to the value
                }
                inOrderTraversalHelper(ptr->right, func); // Traverse the right subtree
            }
        }

    public:
        // Constructor for the BST class
        BST() : root(nullptr) {}

        // Destructor for the BST class
        ~BST() {
            deleteNode(root); // Delete the root node
        }

        // Function to delete a node
        void deleteNode(Node<T1,T2>* node) {
            if (node != nullptr) {
                deleteNode(node->left); // Delete the left child
                deleteNode(node->right); // Delete the right child
                delete node; // Delete the node itself
            }
        }

        // Getter for the root
        Node<T1,T2>*& getRoot() {
            return root;
        }
    // Function to find a node and count comparisons
    std::pair<Node<T1,T2>*, int> findAndCount(Node<T1,T2>* ptr, T1 key) {
    int count = 0;
    while (ptr != nullptr) {
        count++;
        if (key == ptr->key) {
            break;
        } else if (key < ptr->key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    return {ptr, count};
}
        // Function to insert a node
        void insert(Node<T1,T2>* &ptr, T1 key, T2 value) {
            if (ptr == nullptr) {
                ptr = new Node<T1,T2>(key); // Create a new node if ptr is null
                ptr->value.push_back(value); // Add the value to the node
            } else if (key < ptr->key) {
                insert(ptr->left, key, value); // Insert in the left subtree if key is less than the current key
            } else if (key > ptr->key) {
                insert(ptr->right, key, value); // Insert in the right subtree if key is greater than the current key
            } else {
                ptr->value.push_back(value); // Add the value to the node if key is equal to the current key
            }
        }

        // Function to find a node
        Node<T1,T2>* find(Node<T1,T2>* ptr, T1 key) {
            if (ptr == nullptr || ptr->key == key) {
                return ptr; // Return the node if ptr is null or key is equal to the current key
            } else if (key < ptr->key) {
                return find(ptr->left, key); // Search in the left subtree if key is less than the current key
            } else {
                return find(ptr->right, key); // Search in the right subtree if key is greater than the current key
            }
        }

        // Function to perform in-order traversal
        template <typename Func>
        void inOrderTraversal(Func func) {
            inOrderTraversalHelper(root, func); // Start the traversal from the root
        }

        // Function to remove a node
        void remove(Node<T1,T2>* &ptr, T1 key) {
            if (ptr == nullptr) {
                return; // Return if ptr is null
            } else if (key < ptr->key) {
                remove(ptr->left, key); // Remove from the left subtree if key is less than the current key
            } else if (key > ptr->key) {
                remove(ptr->right, key); // Remove from the right subtree if key is greater than the current key
            } else {
                if (ptr->left == nullptr) {
                    Node<T1,T2>* temp = ptr->right;
                    delete ptr; // Delete the node
                    ptr = temp; // Replace the node with its right child
                } else if (ptr->right == nullptr) {
                    Node<T1,T2>* temp = ptr->left;
                    delete ptr; // Delete the node
                    ptr = temp; // Replace the node with its left child
                } else {
                    Node<T1,T2>* temp = findMin(ptr->right); // Find the minimum node in the right subtree
                    ptr->key = temp->key; // Replace the key of the node with the key of the minimum node
                    ptr->value = temp->value; // Replace the value of the node with the value of the minimum node
                    remove(ptr->right, temp->key); // Remove the minimum node
                }
            }
        }

        // Function to find the minimum node
        Node<T1,T2>* findMin(Node<T1,T2>* ptr) {
            while (ptr->left != nullptr) {
                ptr = ptr->left; // Keep going left until the left child is null
            }
            return ptr; // Return the leftmost node
        }
};

#endif // BST_HPP
