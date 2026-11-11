#pragma once

#include "container.h"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class Stack final : public Container {
  public:
    Stack() = default;
    Stack(const Stack &other);
    Stack(Stack &&other) noexcept;
    Stack &operator=(const Stack &other);
    Stack &operator=(Stack &&other) noexcept;
    ~Stack() override;

    void push(const std::string &value);
    std::string pop();
    const std::string &top() const;

    std::string type() const override { return "Stack"; }
    std::size_t size() const noexcept override { return size_; }
    std::vector<std::string> values() const override;
    void clear() noexcept override;

  protected:
    void swapContents(Container &other) noexcept override { swap(static_cast<Stack &>(other)); }
    void appendSerialized(const std::string &value) override;

  private:
    struct Node {
        std::string value;
        Node *next = nullptr;
    };

    void swap(Stack &other) noexcept;
    Node *top_ = nullptr;
    std::size_t size_ = 0;
};
