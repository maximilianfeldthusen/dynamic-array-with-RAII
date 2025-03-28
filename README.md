
## Documentation

### dynamic-array-with-RAII

This C++ code defines a `DynamicArray` class that serves as a simple dynamic array implementation. It makes use of RAII (Resource Acquisition Is Initialization) principles and modern C++ features like `std::unique_ptr` and `std::span`. Let's break down the code step by step.

### Includes and Namespace
```cpp
#include <iostream>
#include <memory>
#include <span>
#include <algorithm>
```
- `#include <iostream>`: For standard input and output operations.
- `#include <memory>`: For smart pointers, specifically `std::unique_ptr`.
- `#include <span>`: For `std::span`, which provides a view over a contiguous sequence of elements.
- `#include <algorithm>`: For the `std::fill` algorithm.

### DynamicArray Class
```cpp
template<typename T>
class DynamicArray {
public:
    // Constructor to initialize the array with a given size
    explicit DynamicArray(std::size_t size) 
        : size_(size), data_(std::make_unique<T[]>(size)) {}
```
- The class template `DynamicArray` is defined with a type parameter `T`.
- The constructor takes a `size` argument and initializes the `size_` member variable. It also allocates a dynamic array of type `T` using `std::make_unique`, which ensures that memory is managed automatically.

#### Deleted Copy Operations
```cpp
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
```
- The copy constructor and copy assignment operator are deleted to prevent copying of the `DynamicArray` instances. This is important because it manages a unique resource (the dynamic array).

#### Move Constructor and Move Assignment Operator
```cpp
    DynamicArray(DynamicArray&& other) noexcept 
        : size_(other.size_), data_(std::move(other.data_)) {
        other.size_ = 0; // Leave the moved-from object in a valid state
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            size_ = other.size_;
            data_ = std::move(other.data_);
            other.size_ = 0; // Leave the moved-from object in a valid state
        }
        return *this;
    }
```
- The move constructor transfers ownership of the dynamic array from `other` to the new instance, setting `other.size_` to 0 to maintain a valid state.
- The move assignment operator does the same but also checks for self-assignment.

#### Access Operators
```cpp
    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }
```
- These operators allow access to the array elements using the subscript operator (`[]`). The first version is for non-const objects, while the second is for const objects.

#### Size Method
```cpp
    std::size_t size() const {
        return size_;
    }
```
- Returns the size of the dynamic array.

#### Fill Method
```cpp
    void fill(const T& value) {
        std::fill(data_.get(), data_.get() + size_, value);
    }
```
- Fills the array with a specified value using `std::fill`.

#### Print Method
```cpp
    void print() const {
        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << ' ';
        }
        std::cout << '\n';
    }
```
- Prints the contents of the array to the standard output.

#### Data Method
```cpp
    T* data() {
        return data_.get();
    }

    const T* data() const {
        return data_.get();
    }
```
- Provides access to the raw data pointer of the array, both in mutable and immutable forms.

### Main Function
```cpp
int main() {
    DynamicArray<int> arr(10); // Create a dynamic array of integers
    arr.fill(42); // Fill the array with the value 42
    arr.print(); // Print the contents of the array

    // Using std::span for safe access
    std::span<int> span(arr.data(), arr.size());
    std::cout << "Using std::span:\n";
    for (const auto& val : span) {
        std::cout << val << ' '; // Print values using std::span
    }
    std::cout << '\n';

    return 0;
}
```
- In the `main` function, a `DynamicArray` of integers is created with a size of 10.
- The array is filled with the value 42 and printed.
- A `std::span` is created from the dynamic array's data, allowing for safe iteration over the contents of the array. The values are printed again using the span.

### Summary
The `DynamicArray` class provides a flexible and safe way to manage a dynamic array in C++, leveraging smart pointers to ensure proper memory management while avoiding issues related to copy operations. The use of `std::span` offers a modern way to handle array-like data.


