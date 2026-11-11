#pragma once

#include "container.h"

#include <cstddef>
#include <iosfwd>
#include <string>
#include <utility>
#include <vector>

class Array final : public Container {
  public:
    Array() = default;
    Array(const Array &other);
    Array(Array &&other) noexcept;
    Array &operator=(const Array &other);
    Array &operator=(Array &&other) noexcept;
    ~Array() override;

    void pushBack(const std::string &value);
    void insert(std::size_t index, const std::string &value);
    void erase(std::size_t index);
    const std::string &at(std::size_t index) const;
    void set(std::size_t index, const std::string &value);
    const std::string &operator[](std::size_t index) const { return at(index); }
    friend std::ostream &operator<<(std::ostream &output, const Array &array);
    int find(const std::string &value) const noexcept;

    std::string type() const override { return "Array"; }
    std::size_t size() const noexcept override { return size_; }
    std::vector<std::string> values() const override;
    void clear() noexcept override;

  protected:
    void swapContents(Container &other) noexcept override { *this = std::move(static_cast<Array &>(other)); }
    void appendSerialized(const std::string &value) override { pushBack(value); }

  private:
    void reserve(std::size_t newCapacity);

    std::string *data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};
