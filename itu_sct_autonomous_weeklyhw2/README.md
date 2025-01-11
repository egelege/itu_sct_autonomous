# Smart Pointers in C++

This project demonstrates the use of **smart pointers** in C++ to manage memory effectively. It highlights the capabilities of `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, and a custom `SmartPointer` template class.

## Overview
Smart pointers in C++ provide automatic memory management by ensuring that allocated memory is properly deallocated when it is no longer needed. They help prevent memory leaks and dangling pointer issues.

---

## Features and Usage

### 1. **Custom SmartPointer Template Class**

A custom implementation of a smart pointer template, `SmartPointer`, is included to demonstrate basic ownership and memory management principles.

#### Key Features:
- Manages a raw pointer and ensures it is deleted when the smart pointer goes out of scope.
- Overloaded operators `*` and `->` for pointer-like behavior.

#### Example:
```cpp
SmartPointer<int> smartPtr1(new int(27));
std::cout << "Value pointed by smartPtr1: " << *smartPtr1 << "\n";
std::cout << "Address of smartPtr1: " << smartPtr1.operator->() << "\n";
```

---

### 2. **`std::unique_ptr`**

#### Key Features:
- Ensures unique ownership of the managed object.
- Memory is automatically released when the `unique_ptr` goes out of scope.
- Supports `std::move` for transferring ownership.

#### Example:
```cpp
std::unique_ptr<int> uniquePtr1 = std::make_unique<int>(25);
std::unique_ptr<int> uniquePtr2 = std::move(uniquePtr1);
if (!uniquePtr1) {
    std::cout << "uniquePtr1 is now null after move." << std::endl;
}
```

---

### 3. **`std::shared_ptr`**

#### Key Features:
- Allows multiple `shared_ptr` instances to share ownership of the same resource.
- Automatically deallocates memory when the last `shared_ptr` goes out of scope.
- Provides a `use_count()` method to track the number of `shared_ptr` instances sharing ownership.

#### Example:
```cpp
std::shared_ptr<Ege> sharedPtr1 = std::make_shared<Ege>();
{
    std::shared_ptr<Ege> sharedPtr2 = sharedPtr1;
    std::cout << "Shared count: " << sharedPtr1.use_count() << "\n";
}
std::cout << "Shared count after scope: " << sharedPtr1.use_count() << "\n";
```

---

### 4. **`std::weak_ptr`**

#### Key Features:
- Provides a non-owning reference to an object managed by a `shared_ptr`.
- Avoids circular references that can lead to memory leaks.
- Can be converted to a `shared_ptr` using `lock()`.

#### Example:
```cpp
std::shared_ptr<int> sharedPtr3 = std::make_shared<int>(52);
std::weak_ptr<int> weakPtr1 = sharedPtr3;
if (auto lockedWeakPtr = weakPtr1.lock()) {
    std::cout << "Value pointed by weakPtr1: " << *lockedWeakPtr << "\n";
} else {
    std::cout << "weakPtr1 is expired." << std::endl;
}
```

---

### 5. Explanation of `std::auto_ptr` Deprecation

`std::auto_ptr` has been deprecated in C++11 and removed in C++17 due to its unsafe ownership transfer semantics. Modern alternatives like `std::unique_ptr` and `std::shared_ptr` provide safer and more predictable behavior with clear ownership semantics.

---

## Benefits of Using Smart Pointers
1. **Automatic Memory Management**: Eliminates the need for manual `delete` calls.
2. **Exception Safety**: Prevents memory leaks during exceptions.
3. **Improved Code Readability**: Clearly conveys ownership semantics.
4. **Avoids Dangling Pointers**: Ensures that pointers to deleted objects cannot be accessed.

---

## Example Output
```plaintext
Value pointed by smartPtr1: 27
Address of smartPtr1: 0x7ffeefbff610
Value pointed by uniquePtr1: 25
Address of uniquePtr1: 0x7ffeefbff618
Address of uniquePtr2 after move: 0x7ffeefbff618
uniquePtr1 is now null after move
Ege Constructor
Using unique_ptr for Ege object: Ege object details here
Ege Destructor
Shared count: 1
Shared count: 2
Shared count: 1
After reset(), sharedPtr1 use count: 0
weakPtr1 use count: 0
weakPtr2 use count: 1
sharedPtr3 use count: 1
Value pointed by sharedPtr3: 1903
sharedPtr3 address: 0x7ffeefbff620
weakPtr1 address: 0x0
```

---

This project highlights the importance of modern memory management techniques in C++ and demonstrates how smart pointers can simplify complex memory handling scenarios.

