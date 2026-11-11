#pragma once

#include "container.h"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class Queue final : public Container {
  public:
    Queue() = default;
    Queue(const Queue &other);
    Queue(Queue &&other) noexcept;
    Queue &operator=(const Queue &other);
    Queue &operator=(Queue &&other) noexcept;
    ~Queue() override;

    void push(const std::string &value);
    std::string pop();
    const std::string &front() const;

    std::string type() const override { return "Queue"; }
    std::size_t size() const noexcept override { return size_; }
    std::vector<std::string> values() const override;
    void clear() noexcept override;

  protected:
    void swapContents(Container &other) noexcept override { swap(static_cast<Queue &>(other)); }
    void appendSerialized(const std::string &value) override { push(value); }

  private:
    struct Node {
        std::string value;
        Node *next = nullptr;
    };

    void swap(Queue &other) noexcept;
    Node *head_ = nullptr;
    Node *tail_ = nullptr;
    std::size_t size_ = 0;
};
