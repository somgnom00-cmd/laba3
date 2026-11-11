#include "doubly_list.h"

#include <memory>
#include <stdexcept>
#include <utility>

DoublyList::DoublyList(const DoublyList &other) : DoublyList() {
    for (const auto &value : other.values())
        pushBack(value);
}

DoublyList::DoublyList(DoublyList &&other) noexcept { swap(other); }

DoublyList &DoublyList::operator=(const DoublyList &other) {
    if (this != &other) {
        DoublyList copy(other);
        swap(copy);
    }
    return *this;
}

DoublyList &DoublyList::operator=(DoublyList &&other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

DoublyList::~DoublyList() { clear(); }

void DoublyList::swap(DoublyList &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

DoublyList::Node *DoublyList::nodeAt(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("индекс списка вне диапазона");
    if (index < size_ / 2) {
        Node *node = head_;
        for (std::size_t i = 0; i < index; ++i)
            node = node->next;
        return node;
    }
    Node *node = tail_;
    for (std::size_t i = size_ - 1; i > index; --i)
        node = node->prev;
    return node;
}

void DoublyList::linkAfter(Node *before, const std::string &value) {
    auto owner = std::make_unique<Node>();
    owner->value = value;
    owner->prev = before;
    owner->next = before != nullptr ? before->next : head_;
    Node *added = owner.release();
    if (added->next != nullptr)
        added->next->prev = added;
    if (before)
        before->next = added;
    else
        head_ = added;
    if (!added->next)
        tail_ = added;
    ++size_;
}

void DoublyList::pushFront(const std::string &value) { linkAfter(nullptr, value); }

void DoublyList::pushBack(const std::string &value) { linkAfter(tail_, value); }

void DoublyList::insert(std::size_t index, const std::string &value) {
    if (index > size_)
        throw std::out_of_range("индекс списка вне диапазона");
    linkAfter(index == 0 ? nullptr : nodeAt(index - 1), value);
}

void DoublyList::erase(std::size_t index) {
    Node *removed = nodeAt(index);
    if (removed->prev)
        removed->prev->next = removed->next;
    else
        head_ = removed->next;
    if (removed->next)
        removed->next->prev = removed->prev;
    else
        tail_ = removed->prev;
    delete removed;
    --size_;
}

const std::string &DoublyList::at(std::size_t index) const { return nodeAt(index)->value; }

int DoublyList::find(const std::string &value) const noexcept {
    std::size_t index = 0;
    for (Node *node = head_; node; node = node->next, ++index) {
        if (node->value == value)
            return static_cast<int>(index);
    }
    return -1;
}

std::vector<std::string> DoublyList::values() const {
    std::vector<std::string> result;
    result.reserve(size_);
    for (Node *node = head_; node; node = node->next)
        result.push_back(node->value);
    return result;
}

std::vector<std::string> DoublyList::reverseValues() const {
    std::vector<std::string> result;
    result.reserve(size_);
    for (Node *node = tail_; node; node = node->prev)
        result.push_back(node->value);
    return result;
}

void DoublyList::clear() noexcept {
    while (head_) {
        Node *removed = head_;
        head_ = head_->next;
        delete removed;
    }
    tail_ = nullptr;
    size_ = 0;
}
