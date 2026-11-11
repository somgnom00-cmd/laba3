#pragma once

#include "container.h"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class DoublyList final : public Container {
  public:
    DoublyList() = default;
    DoublyList(const DoublyList &other);
    DoublyList(DoublyList &&other) noexcept;
    DoublyList &operator=(const DoublyList &other);
    DoublyList &operator=(DoublyList &&other) noexcept;
    ~DoublyList() override;

    void pushFront(const std::string &value);
    void pushBack(const std::string &value);
    void insert(std::size_t index, const std::string &value);
    void erase(std::size_t index);
    const std::string &at(std::size_t index) const;
    int find(const std::string &value) const noexcept;
    std::vector<std::string> reverseValues() const;

    std::string type() const override { return "DoublyList"; }
    std::size_t size() const noexcept override { return size_; }
    std::vector<std::string> values() const override;
    void clear() noexcept override;

  protected:
    void swapContents(Container &other) noexcept override { swap(static_cast<DoublyList &>(other)); }
    void appendSerialized(const std::string &value) override { pushBack(value); }

  private:
    struct Node {
        std::string value;
        Node *prev = nullptr;
        Node *next = nullptr;
    };

    Node *nodeAt(std::size_t index) const;
    void linkAfter(Node *before, const std::string &value);
    void swap(DoublyList &other) noexcept;

    Node *head_ = nullptr;
    Node *tail_ = nullptr;
    std::size_t size_ = 0;
};
