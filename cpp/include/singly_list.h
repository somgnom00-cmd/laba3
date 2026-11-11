#pragma once

#include "container.h"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class SinglyList final : public Container {
  public:
    SinglyList() = default;
    SinglyList(const SinglyList &other);
    SinglyList(SinglyList &&other) noexcept;
    SinglyList &operator=(const SinglyList &other);
    SinglyList &operator=(SinglyList &&other) noexcept;
    ~SinglyList() override;

    void pushFront(const std::string &value);
    void pushBack(const std::string &value);
    void insert(std::size_t index, const std::string &value);
    void erase(std::size_t index);
    const std::string &at(std::size_t index) const;
    int find(const std::string &value) const noexcept;

    std::string type() const override { return "SinglyList"; }
    std::size_t size() const noexcept override { return size_; }
    std::vector<std::string> values() const override;
    void clear() noexcept override;

  protected:
    void swapContents(Container &other) noexcept override { swap(static_cast<SinglyList &>(other)); }
    void appendSerialized(const std::string &value) override { pushBack(value); }

  private:
    struct Node {
        std::string value;
        Node *next = nullptr;
    };

    Node *nodeAt(std::size_t index) const;
    void swap(SinglyList &other) noexcept;

    Node *head_ = nullptr;
    Node *tail_ = nullptr;
    std::size_t size_ = 0;
};
