#include "queue.h"

#include <memory>
#include <stdexcept>
#include <utility>

Queue::Queue(const Queue &other) : Queue() {
    for (const auto &value : other.values())
        push(value);
}

Queue::Queue(Queue &&other) noexcept { swap(other); }

Queue &Queue::operator=(const Queue &other) {
    if (this != &other) {
        Queue copy(other);
        swap(copy);
    }
    return *this;
}

Queue &Queue::operator=(Queue &&other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

Queue::~Queue() { clear(); }

void Queue::swap(Queue &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

void Queue::push(const std::string &value) {
    Node *added = new Node{value};
    if (tail_)
        tail_->next = added;
    else
        head_ = added;
    tail_ = added;
    ++size_;
}

std::string Queue::pop() {
    if (!head_)
        throw std::out_of_range("очередь пуста");
    Node *removed = head_;
    std::string value = std::move(removed->value);
    head_ = removed->next;
    if (!head_)
        tail_ = nullptr;
    delete removed;
    --size_;
    return value;
}

const std::string &Queue::front() const {
    if (!head_)
        throw std::out_of_range("очередь пуста");
    return head_->value;
}

std::vector<std::string> Queue::values() const {
    std::vector<std::string> result;
    result.reserve(size_);
    for (Node *node = head_; node; node = node->next)
        result.push_back(node->value);
    return result;
}

void Queue::clear() noexcept {
    while (head_) {
        Node *removed = head_;
        head_ = head_->next;
        delete removed;
    }
    tail_ = nullptr;
    size_ = 0;
}
