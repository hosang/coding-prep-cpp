#ifndef TREE_H
#define TREE_H

#include <vector>

template <typename T>
struct Node {
  T value;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;

  Node(const T& value) : value(value) {}
};

template <typename T>
class Tree {
 public:
  using VisitFn = std::function<void(const T& value)>;

  ~Tree() { Clear(); }
  void Insert(const T& value);
  void Clear();
  void InOrder(const VisitFn& visit) const;
  void MorrisInOrder(const VisitFn& visit);

 private:
  Node<T>* root = nullptr;

  Node<T>* Insert(Node<T>* node, const T& value);
  void Clear(Node<T>* node);
  void InOrder(Node<T>* node, const VisitFn& visit) const;
  void MorrisInOrder(Node<T>* node, const VisitFn& visit);
};

template <typename T>
void Tree<T>::Insert(const T& value) {
  root = Insert(root, value);
}

template <typename T>
Node<T>* Tree<T>::Insert(Node<T>* node, const T& value) {
  if (node == nullptr) {
    return new Node<T>(value);
  }

  if (value < node->value) {
    node->left = Insert(node->left, value);
  } else {
    node->right = Insert(node->right, value);
  }
  return node;
}

template <typename T>
void Tree<T>::Clear() {
  Clear(root);
  root = nullptr;
}

template <typename T>
void Tree<T>::Clear(Node<T>* node) {
  if (node == nullptr) {
    return;
  }

  Clear(node->left);
  Clear(node->right);
  delete node;
}

template <typename T>
void Tree<T>::InOrder(const VisitFn& visit) const {
  InOrder(root, visit);
}

template <typename T>
void Tree<T>::InOrder(Node<T>* node, const VisitFn& visit) const {
  if (node == nullptr) {
    return;
  }

  InOrder(node->left, visit);
  visit(node->value);
  InOrder(node->right, visit);
}

namespace {

template <typename Node>
bool AttachRightmostOrDetach(Node* tree, Node* node) {
  while (tree->right != nullptr) {
    if (tree->right == node) {
      // Found, detach.
      tree->right = nullptr;
      return false;
    }
    tree = tree->right;
  }
  // tree->right == nullptr: Not found, attach.
  tree->right = node;
  return true;
}

}  // namespace

template <typename T>
void Tree<T>::MorrisInOrder(const VisitFn& visit) {
  Node<T>* curr = root;
  while (curr != nullptr) {
    if (curr->left == nullptr) {
      visit(curr->value);
      curr = curr->right;
      continue;
    }

    // Attach node to the last node to be visited in node->left.
    const bool attached = AttachRightmostOrDetach(curr->left, curr);
    if (attached) {
      // Seeing curr for the first time, so we're not visiting it yet. Attached
      // current at after the last node in the left subtree, so we're going to
      // see it in the correct order.
      curr = curr->left;
    } else {
      // curr is already present in the curr->left subtree and it was detached.
      // So we're touching it for the second and last time.
      visit(curr->value);
      curr = curr->right;
    }
  }
}

#endif  // TREE_H