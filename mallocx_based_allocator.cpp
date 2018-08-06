#include <cstdint>
#include <new>
#include <string>
#include <vector>
#include <mallocx.h>

void* operator new(std::size_t count) {
    void* ptr = mallocx(count);
    if(ptr == nullptr)
        throw std::bad_alloc();

    return ptr;
}

void operator delete(void* oldptr) {
    freex(oldptr);
}

void operator delete[](void* oldptr) {
    operator delete(oldptr);
}

void* operator new[](std::size_t count) {
    return operator new(count);
}

template<typename __Type>
struct Allocatorx {
    public:
        using value_type = __Type;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = __Type*; //deprecated

        Allocatorx() = default;
        ~Allocatorx() = default;

        pointer allocate(std::size_t alloc_size) {
            return static_cast<pointer>(operator new[](alloc_size));
        }
        
        void deallocate(void* ptr, [[maybe_unused]] std::size_t size) {
            operator delete[](ptr);
        }
};

template <typename T>
using vectorx = std::vector<T, Allocatorx<T>>;

using stringx = std::basic_string<char, std::char_traits<char>, Allocatorx<char>>;
