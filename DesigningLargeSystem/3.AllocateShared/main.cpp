#include <iostream>
#include <memory>

using namespace std;
class A {
public:
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};


template<typename T1, typename T2>
struct MyAlloc {

    MyAlloc() = default;
    using value_type = T1;

    template <class T3, class T4>
    constexpr MyAlloc (const MyAlloc<T3, T4>&) noexcept {};

    T1* allocate (std::size_t n) {
        std::cout << "allocate is done" << std::endl;
        return reinterpret_cast<T1*>( T2::operator new(n*sizeof(T1)));
    }

    void deallocate (T1* p, std::size_t n) {
        std::cout << "deallocate is done" << std::endl;
        return T2::operator delete(p, n*sizeof(T1));
    }
};

int main() {
    auto p = std::allocate_shared<A>(MyAlloc<A, A>());
}