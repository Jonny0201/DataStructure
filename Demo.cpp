#include <iostream>

using namespace std;
union __node {
    union __node *__link;
    char __client_data[0];
};
enum {
    __TOTAL_SIZE = 128,
    __NODE_SIZE = 8
};
struct __memory_pool_prototype {
    friend void __deallocate_memory_pool() noexcept;
private:
    static char *__start;
    static char *__end;
    static void __allocate() {
        self::__start = reinterpret_cast<char *>(::operator new (static_cast<unsigned long>(__TOTAL_SIZE)));
        if(not self::__start) {
            throw;
        }
        self::__end = self::__start + static_cast<long>(__TOTAL_SIZE);
        auto __node_end {
            reinterpret_cast<__node *>(self::__start + (static_cast<long>(__TOTAL_SIZE) - static_cast<long>(8)))
        };
        auto __cursor {reinterpret_cast<__node *>(self::__start)};
        while(__cursor not_eq __node_end) {
            __cursor->__link = __cursor + 1;
            ++__cursor;
        }
        __cursor->__link = nullptr;
        /*__cursor = reinterpret_cast<__node *> (self::__start);
        constexpr auto __node_size {__TOTAL_SIZE / __NODE_SIZE};
        for(auto i {0}; i < __node_size; ++i) {
            cout << __cursor++->__link << endl;
        }*/
    }
    static void __deallocate() noexcept {
        ::operator delete (self::__start);
    }
    static void __refill(unsigned long size);
    static constexpr unsigned long __round_up(unsigned long size) {
        return (size + __NODE_SIZE - 1) & ~(__NODE_SIZE - 1);
    }
    using self = __memory_pool_prototype;
public:
    __memory_pool_prototype() = delete;
    __memory_pool_prototype(const __memory_pool_prototype &) = delete;
    __memory_pool_prototype(__memory_pool_prototype &&) noexcept = delete;
    ~__memory_pool_prototype() = delete;
    static inline void *operator new (unsigned long __size) {
        if(not self::__start) {
            self::__allocate();
        }
        __size = self::__round_up(__size);
        if(self::__end - self::__start > __size) {
            self::__end -= __size;
            return self::__end;
        }
        return ::operator new (__size);
    }
    static inline void operator delete(void *__p, unsigned long __size) noexcept {
        __size = self::__round_up(__size);
        auto __node_number {__size / __NODE_SIZE};
        auto __cursor {reinterpret_cast<__node *>(__p)};
        for(auto i {0}; i < __node_number; ++i) {
            __cursor->__link = __cursor + 1;
            ++__cursor;
        }
        (reinterpret_cast<__node *>(self::__end) - 1)->__link = reinterpret_cast<__node *>(__p);
    }
};
char *__memory_pool_prototype::__start = nullptr;
char *__memory_pool_prototype::__end = nullptr;
inline void __deallocate_memory_pool() noexcept {
    __memory_pool_prototype::__deallocate();
}
class Foo {
public:
    int a;
    int b;
    int c;
    long d;
};
int main(int argc, char *argv[]) {
    auto x {reinterpret_cast<long *>(__memory_pool_prototype::operator new (sizeof(long)))};
    *x = 10;
    auto p {reinterpret_cast<int *>(__memory_pool_prototype::operator new (sizeof(int)))};
    *p = 4;
    cout << p << endl << *p << endl;
    cout << x << endl << *x << endl;
    __memory_pool_prototype::operator delete (p, sizeof(int));
    __memory_pool_prototype::operator delete (x, sizeof(long));
    auto f {reinterpret_cast<Foo *>(__memory_pool_prototype::operator new (sizeof(Foo)))};
    f->a = 1;
    f->b = 2;
    f->c = 3;
    f->d = 4;
    cout << f << endl;
    __memory_pool_prototype::operator delete (f, sizeof *f);
    __deallocate_memory_pool();
}
