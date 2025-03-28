
#include <iostream>
#include <memory>
#include <span>
#include <algorithm>

// Class representing a dynamic array with RAII
template<typename T>
class DynamicArray {
public:
    // Constructor to initialize the array with a given size
    explicit DynamicArray(std::size_t size) 
        : size_(size), data_(std::make_unique<T[]>(size)) {}

    // Deleted copy constructor and copy assignment operator
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept 
        : size_(other.size_), data_(std::move(other.data_)) {
        other.size_ = 0; // Leave the moved-from object in a valid state
    }

    // Move assignment operator
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            size_ = other.size_;
            data_ = std::move(other.data_);
            other.size_ = 0; // Leave the moved-from object in a valid state
        }
        return *this;
    }

    // Access operator
    T& operator[](std::size_t index) {
        return data_[index];
    }

    // Const access operator
    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    // Get size of the array
    std::size_t size() const {
        return size_;
    }

    // Function to fill the array with values
    void fill(const T& value) {
        std::fill(data_.get(), data_.get() + size_, value);
    }

    // Function to print the contents of the array
    void print() const {
        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << ' ';
        }
        std::cout << '\n';
    }

    // Public function to get raw data pointer
    T* data() {
        return data_.get();
    }

    const T* data() const {
        return data_.get();
    }

private:
    std::size_t size_; // Size of the array
    std::unique_ptr<T[]> data_; // Pointer to the array
};

int main() {
    // Create a dynamic array of integers
    DynamicArray<int> arr(10);

    // Fill the array with values
    arr.fill(42);

    // Print the contents of the array
    arr.print();

    // Using std::span for safe access
    std::span<int> span(arr.data(), arr.size());
    std::cout << "Using std::span:\n";
    for (const auto& val : span) {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    return 0;
}
