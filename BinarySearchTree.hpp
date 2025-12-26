#pragma once

#include <cstddef>
#include <functional>

namespace ds {
    enum class BstTraverseOrder {
        ASCENDING,
        DESCENDING,
        FROM_ROOT,
    };

    template<typename T>
    class BinarySearchTree {
        struct Node {
            T data;
            Node* left;
            Node* right;

            explicit Node(T data) : data{std::move(data)}, left{nullptr}, right{nullptr} {}
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

        void dispatch_action(std::function<void(const T&)> action, BstTraverseOrder order) const {
            switch (order) {
            case BstTraverseOrder::ASCENDING:
                return asc_perform_action_for_node(root, action);
            case BstTraverseOrder::DESCENDING:
                return desc_perform_action_for_node(root, action);
            case BstTraverseOrder::FROM_ROOT:
                return from_root_perform_action_for_node(root, action);
            default: 
                throw std::out_of_range("Unknown way of traversal");
            }
        }

        void dispatch_action(std::function<void(T&)> action, BstTraverseOrder order) {
            switch (order) {
            case BstTraverseOrder::ASCENDING:
                return asc_perform_action_for_node(root, action);
            case BstTraverseOrder::DESCENDING:
                return desc_perform_action_for_node(root, action);
            case BstTraverseOrder::FROM_ROOT:
                return from_root_perform_action_for_node(root, action);
            default: 
                throw std::out_of_range("Unknown way of traversal");
            }
        }

        void from_root_perform_action_for_node(Node* node, std::function<void(const T&)> action) const {
            if (!node) {
                return;
            }

            action(node->data);

            from_root_perform_action_for_node(node->left, action);
            from_root_perform_action_for_node(node->right, action);
        }

        void from_root_perform_action_for_node(Node* node, std::function<void(T&)> action) {
            if (!node) {
                return;
            }

            action(node->data);

            from_root_perform_action_for_node(node->left, action);
            from_root_perform_action_for_node(node->right, action);
        }

        void asc_perform_action_for_node(Node* node, std::function<void(const T&)> action) const {
            if (!node) {
                return;
            }

            asc_perform_action_for_node(node->left, action);

            action(node->data);

            asc_perform_action_for_node(node->right, action);
        }

        void asc_perform_action_for_node(Node* node, std::function<void(T&)> action) {
            if (!node) {
                return;
            }

            asc_perform_action_for_node(node->left, action);

            action(node->data);

            asc_perform_action_for_node(node->right, action);
        }

        void desc_perform_action_for_node(Node* node, std::function<void(const T&)> action) const {
            if (!node) {
                return;
            }

            desc_perform_action_for_node(node->right, action);
        
            action(node->data);

            desc_perform_action_for_node(node->left, action);
        }

        void desc_perform_action_for_node(Node* node, std::function<void(T&)> action) {
            if (!node) {
                return;
            }

            desc_perform_action_for_node(node->right, action);
        
            action(node->data);

            desc_perform_action_for_node(node->left, action);
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
            size++;
            if (!root) {
                root = new Node(std::move(data));
                root->left = nullptr;
                root->right = nullptr;
                return;
            }

            Node* node = root;
            while (true) {
                if (node->data == data) {
                    return;
                }

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
        }

        void foreach(std::function<void(const T&)> action, BstTraverseOrder order = BstTraverseOrder::ASCENDING) const {
            dispatch_action(action, order);
        }

        void foreach(std::function<void(T&)> action, BstTraverseOrder order = BstTraverseOrder::ASCENDING) {
            dispatch_action(action, order);
        }

        [[nodiscard]]
        bool is_empty() const noexcept {
            return size == 0;
        }

        [[nodiscard]]
        bool is_present(const T& data) const noexcept {
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
