#pragma once

#include "container.h"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

// Вариант 3 ЛР1: полное бинарное дерево, заполнение по уровням.
class CompleteBinaryTree final : public Container {
  public:
    CompleteBinaryTree() = default;
    CompleteBinaryTree(const CompleteBinaryTree &other);
    CompleteBinaryTree(CompleteBinaryTree &&other) noexcept;
    CompleteBinaryTree &operator=(const CompleteBinaryTree &other);
    CompleteBinaryTree &operator=(CompleteBinaryTree &&other) noexcept;
    ~CompleteBinaryTree() override;

    void insert(const std::string &value);
    bool contains(const std::string &value) const;
    bool isComplete() const;

    std::string type() const override { return "CompleteBinaryTree"; }
    std::size_t size() const noexcept override { return size_; }
    std::vector<std::string> values() const override;
    void clear() noexcept override;

  protected:
    void swapContents(Container &other) noexcept override { swap(static_cast<CompleteBinaryTree &>(other)); }
    void appendSerialized(const std::string &value) override { insert(value); }

  private:
    struct Node {
        std::string value;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    static void destroy(Node *node) noexcept;
    void swap(CompleteBinaryTree &other) noexcept;

    Node *root_ = nullptr;
    std::size_t size_ = 0;
};
