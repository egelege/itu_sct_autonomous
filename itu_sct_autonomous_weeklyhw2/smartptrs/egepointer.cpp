#include <iostream>
#include <memory>

class Ege {
public:
    Ege() {
        std::cout << "Ege Constructor\n";
    }
    ~Ege() {
        std::cout << "Ege Destructor\n";
    }

   // friend std::ostream& operator<<(std::ostream& os, const Ege& ege);

    

};

 std::ostream& operator<<(std::ostream& os, const Ege& ege) {
    // Customize the output as needed
    os << "Ege object details here";
    return os;
};


template <typename T>
class SmartPointer {
private:
    T* ptr; // Raw pointer

public:
    // Constructor
     SmartPointer(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~SmartPointer() {
        delete ptr;
    }

    // Overload * operator
    T& operator*() {
        return *ptr;
    }

    // Overload -> operator
    T* operator->() {
        return ptr;
    }
};

int main() {
  

    // unique_ptr usage with get() and move()
    std::unique_ptr<int> uniquePtr1 = std::make_unique<int>(25);
    
    //smartptr
    SmartPointer<int> smartPtr1(new int(27));
    std::cout << "Value pointed by smartPtr1: " << *smartPtr1 << "\n";
    //smartptr address
    std::cout << "Address of smartPtr1: " << smartPtr1.operator->() << "\n";
    std::cout << "Value pointed by uniquePtr1: " << *uniquePtr1 << "\n";
    std::cout << "Address of uniquePtr1: " << uniquePtr1.get() << "\n";

    std::unique_ptr<int> uniquePtr2 = std::move(uniquePtr1);
    std::cout << "Address of uniquePtr2 after move: " << uniquePtr2.get() << "\n";
    if (!uniquePtr1) {
        std::cout << "uniquePtr1 is now null after move : " << uniquePtr1.get() << "\n";
    }

    {
        std::unique_ptr<Ege> uniquePtr3 = std::make_unique<Ege>();
        std::cout << "Using unique_ptr for Ege object: " << *uniquePtr3 << "\n";
    }

    std::unique_ptr<int> uniquePtr4 = std::make_unique<int>(31);
    int* rawPointer = uniquePtr4.get();
    std::cout << "Value pointed by uniquePtr4: " << *rawPointer << "\n";

    std::unique_ptr<int> uniquePtr5 = std::move(uniquePtr4);
    if (!uniquePtr4) {
        std::cout << "uniquePtr4 is now null after move\n";
    }
    std::cout << "Value pointed by uniquePtr5: " << *uniquePtr5 << "\n";



    // shared_ptr usage with use_count() and reset()

    std::shared_ptr<Ege> sharedPtr1 = std::make_shared<Ege>();
    std::cout << "Shared count: " << sharedPtr1.use_count() << "\n";

    {
        std::shared_ptr<Ege> sharedPtr2 = sharedPtr1;
        std::cout << "Shared count: " << sharedPtr1.use_count() << "\n";
    }

    std::cout << "Shared count: " << sharedPtr1.use_count() << "\n";
    sharedPtr1.reset();
    std::cout << "After reset(), sharedPtr1 use count: " << sharedPtr1.use_count() << "\n";

    // weak_ptr usage with shared_ptr and reset()

    std::shared_ptr<int> sharedPtr3 = std::make_shared<int>();
    *sharedPtr3 = 52;

    
    std::weak_ptr<int> weakPtr1 = sharedPtr3;
    sharedPtr3.reset(new int);
    *sharedPtr3 = 1903;


    std::weak_ptr<int> weakPtr2 = sharedPtr3;

    std::cout << "weakPtr1 use count: " << weakPtr1.use_count() << "\n";
    std::cout << "weakPtr2 use count: " << weakPtr2.use_count() << "\n";
    std::cout << "sharedPtr3 use count: " << sharedPtr3.use_count() << "\n";
    std::cout << "Value pointed by sharedPtr3: " << *sharedPtr3 << "\n";

    if (auto lockedWeakPtr1 = weakPtr1.lock()) {
        std::cout << "Value pointed by weakPtr1: " << *lockedWeakPtr1 << "\n";
    } else {
        std::cout << "weakPtr1 is expired\n";
    }

    if (auto lockedWeakPtr2 = weakPtr2.lock()) {
        std::cout << "Value pointed by weakPtr2: " << *lockedWeakPtr2 << "\n";
    } else {
        std::cout << "weakPtr2 is expired\n";
    }

    std::cout << "sharedPtr3 address: " << sharedPtr3.get() << "\n";
    std::cout << "weakPtr1 address: " << weakPtr1.lock().get() << "\n";



    // Explanation of std::auto_ptr deprecation
    // std::auto_ptr has been deprecated because it does not enforce unique ownership semantics.
    // When you assign one std::auto_ptr to another, ownership is transferred silently, which can lead to confusion and bugs.
    // std::unique_ptr enforces unique ownership clearly using move semantics, making it safer and more predictable.

 
    return 0;
}