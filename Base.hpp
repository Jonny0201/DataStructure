#ifndef DATA_STRUCTURE_BASE_HPP
#define DATA_STRUCTURE_BASE_HPP

#include <iostream>

namespace DataStructure {
    template <typename T>
    class ArrayBase {
    public:
        typedef T type;
        typedef const T constType;
        typedef T & reference;
        typedef const T & constReference;
        typedef T * pointer;
        typedef const T * constPointer;
        typedef const T *const constPointerConstant;
        typedef T && valueReference;
    protected:
        mutable ptrdiff_t allocateSize {50};
        std::allocator<T> array;
        T *first {nullptr};
        T *cursor {nullptr};
        T *end {nullptr};
        virtual bool checkFull() const = 0;
        virtual void reallocate() = 0;
        virtual void free() = 0;
        virtual void allocate() = 0;
    };
    template <typename T>
    class ListBase {
    public:
        typedef T type;
        typedef const T constType;
        typedef T & reference;
        typedef const T & constReference;
        typedef T * pointer;
        typedef const T * constPointer;
        typedef const T *const constPointerConstant;
        typedef T && valueReference;
    private:
        template <typename U>
        struct Node {
            U data;
            Node *next {nullptr};
        };
    protected:
        std::allocator<Node<T>> list;
        Node<T> *first {nullptr};
        virtual void free() = 0;
    };
}

#endif //DATA_STRUCTURE_BASE_HPP
