// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& val)
        : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void destroy(Node* node) {
    if (node != nullptr) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }

  void insertHelper(Node*& node, const T& val) {
    if (node == nullptr) {
      node = new Node(val);
    } else if (val < node->value) {
      insertHelper(node->left, val);
    } else if (val > node->value) {
      insertHelper(node->right, val);
    } else {
      node->count++;
    }
  }

  bool searchHelper(const Node* node, const T& val) const {
    if (node == nullptr) {
      return false;
    }
    if (val == node->value) {
      return true;
    }
    if (val < node->value) {
      return searchHelper(node->left, val);
    }
    return searchHelper(node->right, val);
  }

  int depthHelper(const Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    int leftDepth = depthHelper(node->left);
    int rightDepth = depthHelper(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  void extractHelper(const Node* node,
                     std::vector<std::pair<T, int>>* vec) const {
    if (node != nullptr) {
      extractHelper(node->left, vec);
      vec->push_back({node->value, node->count});
      extractHelper(node->right, vec);
    }
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    destroy(root);
  }

  void insert(const T& val) {
    insertHelper(root, val);
  }

  bool search(const T& val) const {
    return searchHelper(root, val);
  }

  int depth() const {
    return depthHelper(root);
  }

  void extractAll(std::vector<std::pair<T, int>>* vec) const {
    if (vec != nullptr) {
      extractHelper(root, vec);
    }
  }
};

#endif  // INCLUDE_BST_H_
