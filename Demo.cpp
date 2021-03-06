#include <iostream>
struct __memory_pool_prototype {
    friend void __deallocate_memory_pool() noexcept;
private:
    union __node {
        union __node *__link;
        char __client_data[0];        //__client_data[1] for compatibility, Clang compile succeeded.
    };
    enum {
        __TOTAL_SIZE = 128,
        __NODE_SIZE = 8
    };
private:
    static char *__start;
    static char *__end;
    static void __allocate() {
        __self::__start = reinterpret_cast<char *>(::operator new (static_cast<unsigned long>(__TOTAL_SIZE)));
        if(not __self::__start) {
            throw;
        }
        __self::__end = __self::__start + static_cast<long>(__TOTAL_SIZE);
        auto __node_end {
            reinterpret_cast<__node *>(__self::__start + (static_cast<long>(__TOTAL_SIZE) - static_cast<long>(8)))
        };
        auto __cursor {reinterpret_cast<__node *>(__self::__start)};
        while(__cursor not_eq __node_end) {
            __cursor->__link = __cursor + 1;
            ++__cursor;
        }
        __cursor->__link = nullptr;
        /*__cursor = reinterpret_cast<__node *> (__self::__start);
        constexpr auto __node_size {__TOTAL_SIZE / __NODE_SIZE};
        for(auto i {0}; i < __node_size; ++i) {
            std::cout << __cursor++->__link << std::endl;
        }*/
    }
    static void __deallocate() noexcept {
        ::operator delete (__self::__start);
    }
    static void __refill(unsigned long __size);
    static constexpr unsigned long __round_up(unsigned long __size) {
        return (__size + __NODE_SIZE - 1) & ~(__NODE_SIZE - 1);
    }
    using __self = __memory_pool_prototype;
public:
    __memory_pool_prototype() = delete;
    __memory_pool_prototype(const __memory_pool_prototype &) = delete;
    __memory_pool_prototype(__memory_pool_prototype &&) noexcept = delete;
    ~__memory_pool_prototype() = delete;
    static inline void *operator new (unsigned long __size) {
        if(not __self::__start) {
            __self::__allocate();
        }
        __size = __self::__round_up(__size);
        if(__self::__end - __self::__start > __size) {
            __self::__end -= __size;
            return __self::__end;
        }
        return ::operator new (__size);
    }
    static inline void operator delete (void *__p, unsigned long __size) noexcept {
        __size = __self::__round_up(__size);
        auto __node_number {__size / __NODE_SIZE};
        auto __cursor {reinterpret_cast<__node *>(__p)};
        for(auto i {0}; i < __node_number; ++i) {
            __cursor->__link = __cursor + 1;
            ++__cursor;
        }
        (reinterpret_cast<__node *>(__self::__end) - 1)->__link = reinterpret_cast<__node *>(__p);
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
template <typename T, typename ...Args>
struct tuple : tuple<Args...> {
    T t;
protected:
    template <unsigned long N>
    decltype(auto) __get_aux() const noexcept {
        if constexpr(not N) {
            return this->t;
        }
        return tuple<Args...>::template __get_aux<N - 1>();
    }
public:
    explicit tuple(const T &t, Args &&...args) : t {t}, tuple<Args...>(std::forward<Args>(args)...) {}
    void print() const noexcept override {
        tuple<Args...>::print();
        std::cout << this->t << std::endl;
    }
    template <unsigned long N>
    decltype(auto) get() const noexcept {
        return this->__get_aux<N>();
    }
};
template <typename T>
struct tuple<T> {
    T t;
protected:
    template <unsigned long>
    T __get_aux() const noexcept {
        return this->t;
    }
public:
    explicit tuple(const T &t) : t {t} {}
    virtual void print() const noexcept {
        std::cout << this->t << std::endl;
    }
};
int main(int argc, char *argv[]) {
    auto x {reinterpret_cast<long *>(__memory_pool_prototype::operator new (sizeof(long)))};
    *x = 10;
    auto p {reinterpret_cast<int *>(__memory_pool_prototype::operator new (sizeof(int)))};
    *p = 4;
    std::cout << p << std::endl << *p << std::endl;
    std::cout << x << std::endl << *x << std::endl;
    __memory_pool_prototype::operator delete (p, sizeof(int));
    __memory_pool_prototype::operator delete (x, sizeof(long));
    auto f {reinterpret_cast<Foo *>(__memory_pool_prototype::operator new (sizeof(Foo)))};
    f->a = 1;
    f->b = 2;
    f->c = 3;
    f->d = 4;
    std::cout << f << std::endl;
    __memory_pool_prototype::operator delete (f, sizeof *f);
    __deallocate_memory_pool();
    tuple<int, char, double> f(1, 'f', 9.9);
    std::cout << f.get<2>();
}
