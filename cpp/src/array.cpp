#include "array.h"

#include <algorithm>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>

Array::Array(const Array &other) : Array() {
    reserve(other.size_);
    for (std::size_t i = 0; i < other.size_; ++i)
        data_[i] = other.data_[i];
    size_ = other.size_;
}

Array::Array(Array &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
}

Array &Array::operator=(const Array &other) {
    if (this == &other)
        return *this;
    Array copy(other);
    std::swap(data_, copy.data_);
    std::swap(size_, copy.size_);
    std::swap(capacity_, copy.capacity_);
    return *this;
}

Array &Array::operator=(Array &&other) noexcept {
    if (this == &other)
        return *this;
    clear();
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = other.capacity_ = 0;
    return *this;
}

Array::~Array() { clear(); }

void Array::reserve(std::size_t newCapacity) {
    if (newCapacity <= capacity_)
        return;
    auto *replacement = new std::string[newCapacity];
    for (std::size_t i = 0; i < size_; ++i)
        replacement[i] = std::move(data_[i]);
    delete[] data_;
    data_ = replacement;
    capacity_ = newCapacity;
}

void Array::pushBack(const std::string &value) {
    insert(size_, value);
}

void Array::insert(std::size_t index, const std::string &value) {
    if (index > size_)
        throw std::out_of_range("индекс массива вне диапазона");
    std::string saved(value);
    if (size_ == capacity_)
        reserve(capacity_ == 0 ? 4 : capacity_ * 2);
    for (std::size_t i = size_; i > index; --i)
        data_[i] = std::move(data_[i - 1]);
    data_[index] = std::move(saved);
    ++size_;
}

void Array::erase(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("индекс массива вне диапазона");
    for (std::size_t i = index; i + 1 < size_; ++i)
        data_[i] = std::move(data_[i + 1]);
    --size_;
    data_[size_].clear();
}

const std::string &Array::at(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("индекс массива вне диапазона");
    return data_[index];
}

void Array::set(std::size_t index, const std::string &value) {
    if (index >= size_)
        throw std::out_of_range("индекс массива вне диапазона");
    data_[index] = value;
}

int Array::find(const std::string &value) const noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == value)
            return static_cast<int>(i);
    }
    return -1;
}

std::vector<std::string> Array::values() const {
    std::vector<std::string> result;
    result.reserve(size_);
    for (std::size_t i = 0; i < size_; ++i)
        result.push_back(data_[i]);
    return result;
}

std::ostream &operator<<(std::ostream &output, const Array &array) {
    output << '[';
    for (std::size_t i = 0; i < array.size(); ++i) {
        if (i != 0)
            output << ", ";
        output << array[i];
    }
    return output << ']';
}

void Array::clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = capacity_ = 0;
}
