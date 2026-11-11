#include "singly_list.h"

#include <memory>
#include <stdexcept>
#include <utility>

SinglyList::SinglyList(const SinglyList &other) : SinglyList() {
    for (const auto &value : other.values())
        pushBack(value);
}

SinglyList::SinglyList(SinglyList &&other) noexcept { swap(other); }

SinglyList &SinglyList::operator=(const SinglyList &other) {
    if (this != &other) {
        SinglyList copy(other);
        swap(copy);
    }
    return *this;
}

SinglyList &SinglyList::operator=(SinglyList &&other) noexcept {
    if (this != &other) {
        clear();
        swap(other);
    }
    return *this;
}

SinglyList::~SinglyList() { clear(); }

void SinglyList::swap(SinglyList &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

SinglyList::Node *SinglyList::nodeAt(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("индекс списка вне диапазона");
    Node *node = head_;
    for (std::size_t i = 0; i < index; ++i)
        node = node->next;
    return node;
}

void SinglyList::pushFront(const std::string &value) {
    Node *added = new Node{value, head_};
    head_ = added;
    if (!tail_)
        tail_ = added;
    ++size_;
}

void SinglyList::pushBack(const std::string &value) {
    Node *added = new Node{value};
    if (tail_)
        tail_->next = added;
    else
        head_ = added;
    tail_ = added;
    ++size_;
}

void SinglyList::insert(std::size_t index, const std::string &value) {
    if (index > size_)
        throw std::out_of_range("индекс списка вне диапазона");
    if (index == 0)
        return pushFront(value);
    if (index == size_)
        return pushBack(value);
    Node *before = nodeAt(index - 1);
    before->next = new Node{value, before->next};
    ++size_;
}

void SinglyList::erase(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("индекс списка вне диапазона");
    Node *removed = nullptr;
    if (index == 0) {
        removed = head_;
        head_ = head_->next;
    } else {
        Node *before = nodeAt(index - 1);
        removed = before->next;
        before->next = removed->next;
        if (removed == tail_)
            tail_ = before;
    }
    delete removed;
    --size_;
    if (size_ == 0)
        tail_ = nullptr;
}

const std::string &SinglyList::at(std::size_t index) const { return nodeAt(index)->value; }

int SinglyList::find(const std::string &value) const noexcept {
    std::size_t index = 0;
    for (Node *node = head_; node; node = node->next, ++index) {
        if (node->value == value)
            return static_cast<int>(index);
    }
    return -1;
}

std::vector<std::string> SinglyList::values() const {
    std::vector<std::string> result;
    result.reserve(size_);
    for (Node *node = head_; node; node = node->next)
        result.push_back(node->value);
    return result;
}

void SinglyList::clear() noexcept {
    while (head_) {
        Node *removed = head_;
        head_ = head_->next;
        delete removed;
    }
    tail_ = nullptr;
    size_ = 0;
}
