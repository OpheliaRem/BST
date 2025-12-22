#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <stdexcept>

namespace ds {
    template<typename T>
    class BinarySearchTree {
        struct Node {
            T data;
            Node* left;
            Node* right;

            Node(T data) : data{std::move(data)}, left(nullptr), right(nullptr) {}
        };

        Node* root;
        std::size_t size;

        void remove_node_from(Node* node) {
            if (!node) {
                return;
            }

            Node* left = node->left;
            Node* right = node->right;

            delete node;
            remove_node_from(left);
            remove_node_from(right);
        }

        void perform_action_for_node(Node* node, std::function<void(const T&)> action) const {
            if (!node) {
                return;
            }

            action(node->data);

            perform_action_for_node(node->left, action);
            perform_action_for_node(node->right, action);
        }

        void perform_action_for_node(Node* node, std::function<void(T&)> action) {
            if (!node) {
                return;
            }

            action(node->data);

            perform_action_for_node(node->left, action);
            perform_action_for_node(node->right, action);
        }

    public:

        BinarySearchTree() : root{nullptr}, size{0} {}

        BinarySearchTree(const BinarySearchTree<T>& other) = delete;
        BinarySearchTree(BinarySearchTree<T>&& other) : root{other.root}, size{other.size} {
            other.root = nullptr;
            other.size = 0;
        }

        BinarySearchTree<T>& operator=(BinarySearchTree<T> other) = delete;

        ~BinarySearchTree() {
            remove_node_from(root);
            root = nullptr;

            size = 0;
        }

        void add(T data) {
            if (!root) {
                root = new Node(std::move(data));
                root->left = nullptr;
                root->right = nullptr;
                return;
            }

            Node* node = root;
            while (true) {
                if (!(node->left) && data <= node->data) {
                    node->left = new Node(std::move(data));
                    return;
                }

                if (!(node->right) && data > node->data) {
                    node->right = new Node(std::move(data));
                    return;
                }

                node = data > node->data ? node->right : node->left;
            }
            size++;
        }

        void foreach(std::function<void(const T&)> action) const {
            perform_action_for_node(root, action);
        }

        void foreach(std::function<void(T&)> action) {
            perform_action_for_node(root, action);
        }

        [[nodiscard]]
        bool is_empty() const {
            return size == 0;
        }

        [[nodiscard]]
        bool is_present(const T& data) {
            Node* node = root;
            while (node) {
                if (data == node->data) {
                    return true;
                }

                node = data < node->data ? node->left : node->right;
            }

            return false;
        }

        T& find(const T& data) {
            if (is_empty()) {
                throw std::out_of_range("BST is empty");
            }

            Node* node = root;
            while (node) {
                if (node->data == data) {
                    return node->data;
                }

                node = data < node->data ? node->left : node->right;
            }

            throw std::out_of_range("Element not found");
        }

        const T& find(const T& data) const {
            if (is_empty()) {
                throw std::out_of_range("BST is empty");
            }

            Node* node = root;
            while (node) {
                if (node->data == data) {
                    return node->data;
                }

                node = data < node->data ? node->left : node->right;
            }

            throw std::out_of_range("Element not found");
        }

        const T& min() const {
            if (is_empty()) {
                throw std::out_of_range("BST is empty");
            }

            Node* node = root;
            while (node->left) {
                node = node->left;
            }

            return node->data;
        }

        const T& max() const {
            if (is_empty()) {
                throw std::out_of_range("BST is empty");
            }

            Node* node = root;
            while (node->right) {
                node = node->right;
            }

            return node->data;
        }
    };
}
