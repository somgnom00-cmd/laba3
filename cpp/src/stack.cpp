#include "stack.h"

#include <memory>
#include <stdexcept>
#include <utility>

Stack::Stack(const Stack &other) : Stack() {
    auto stored = other.values();
    for (auto it = stored.rbegin(); it != stored.rend(); ++it)
        push(*it);
}

Stack::Stack(Stack &&other) noexcept { swap(other); }

Stack &Stack::operator=(const Stack &other) {
    if (this != &other) {
        Stack copy(other);
        swap(copy);
    }
    return *this;
}

Stack &Stack::operator=(Stack &&other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

Stack::~Stack() { clear(); }

void Stack::swap(Stack &other) noexcept {
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
}

void Stack::push(const std::string &value) {
    top_ = new Node{value, top_};
    ++size_;
}

std::string Stack::pop() {
    if (!top_)
        throw std::out_of_range("стек пуст");
    Node *removed = top_;
    std::string value = std::move(removed->value);
    top_ = removed->next;
    delete removed;
    --size_;
    return value;
}

const std::string &Stack::top() const {
    if (!top_)
        throw std::out_of_range("стек пуст");
    return top_->value;
}

std::vector<std::string> Stack::values() const {
    std::vector<std::string> result;
    result.reserve(size_);
    for (Node *node = top_; node; node = node->next)
        result.push_back(node->value);
    return result;
}

void Stack::appendSerialized(const std::string &value) {
    Node *added = new Node{value};
    if (!top_) {
        top_ = added;
    } else {
        Node *bottom = top_;
        while (bottom->next)
            bottom = bottom->next;
        bottom->next = added;
    }
    ++size_;
}

void Stack::clear() noexcept {
    while (top_) {
        Node *removed = top_;
        top_ = top_->next;
        delete removed;
    }
    size_ = 0;
}
