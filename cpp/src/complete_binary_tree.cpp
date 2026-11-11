#include "complete_binary_tree.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <utility>

CompleteBinaryTree::CompleteBinaryTree(const CompleteBinaryTree &other) : CompleteBinaryTree() {
    for (const auto &value : other.values())
        insert(value);
}

CompleteBinaryTree::CompleteBinaryTree(CompleteBinaryTree &&other) noexcept { swap(other); }

CompleteBinaryTree &CompleteBinaryTree::operator=(const CompleteBinaryTree &other) {
    if (this != &other) {
        CompleteBinaryTree copy(other);
        swap(copy);
    }
    return *this;
}

CompleteBinaryTree &CompleteBinaryTree::operator=(CompleteBinaryTree &&other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

CompleteBinaryTree::~CompleteBinaryTree() { clear(); }

void CompleteBinaryTree::swap(CompleteBinaryTree &other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
}

void CompleteBinaryTree::insert(const std::string &value) {
    auto owner = std::make_unique<Node>();
    owner->value = value;
    if (!root_) {
        root_ = owner.release();
        ++size_;
        return;
    }
    std::queue<Node *> pending;
    pending.push(root_);
    while (!pending.empty()) {
        Node *current = pending.front();
        pending.pop();
        if (!current->left) {
            current->left = owner.release();
            ++size_;
            return;
        }
        if (!current->right) {
            current->right = owner.release();
            ++size_;
            return;
        }
        pending.push(current->left);
        pending.push(current->right);
    }
}

bool CompleteBinaryTree::contains(const std::string &value) const {
    const auto stored = values();
    return std::find(stored.begin(), stored.end(), value) != stored.end();
}

bool CompleteBinaryTree::isComplete() const {
    if (!root_)
        return true;
    std::queue<Node *> pending;
    pending.push(root_);
    bool gap = false;
    while (!pending.empty()) {
        Node *current = pending.front();
        pending.pop();
        if (!current) {
            gap = true;
        } else {
            if (gap)
                return false;
            pending.push(current->left);
            pending.push(current->right);
        }
    }
    return true;
}

std::vector<std::string> CompleteBinaryTree::values() const {
    std::vector<std::string> result;
    result.reserve(size_);
    if (!root_)
        return result;
    std::queue<Node *> pending;
    pending.push(root_);
    while (!pending.empty()) {
        Node *current = pending.front();
        pending.pop();
        result.push_back(current->value);
        if (current->left)
            pending.push(current->left);
        if (current->right)
            pending.push(current->right);
    }
    return result;
}

void CompleteBinaryTree::destroy(Node *node) noexcept {
    if (!node)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void CompleteBinaryTree::clear() noexcept {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
}
