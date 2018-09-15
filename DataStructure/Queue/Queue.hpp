//
// Created by Jonny Charlotte on 7/8/2018.
//

#ifndef DATA_STRUCTURE_QUEUE_HPP
#define DATA_STRUCTURE_QUEUE_HPP

#include "Deque.hpp"

namespace DataStructure {
    template <typename T, typename Container = Deque<T>, bool sacrifice = false, bool tag = false>
    class Queue final {
        friend void swap(Queue &a, Queue &b) {
            a.swap(b);
        }
    private:
        using container = Container;
    public:
        using sizeType = typename container::sizeType;
        using differenceType = typename container::differenceType;
        using valueType = typename container::valueType;
        using reference = typename container::reference;
        using constReference = typename container::constReference;
        using pointer = typename container::pointer;
        using constPointer = typename container::constPointer;
        using constPointerConstant = typename container::constPointerConstant;
        using rightValueReference = typename container::rightValueReference;
    private:
        container c;
    public:
        Queue() = default;
        Queue(const Queue &) = default;
        Queue(Queue &&) noexcept = default;
        Queue &operator=(const Queue &) = default;
        Queue &operator=(Queue &&) noexcept = default;
        bool operator==(const Queue &) const;
        bool operator not_eq(const Queue &) const;
        bool operator<(const Queue &) const;
        bool operator<=(const Queue &) const;
        bool operator>(const Queue &) const;
        bool operator>=(const Queue &) const;
        explicit operator bool() const;
        ~Queue() = default;
    public:
        bool empty() const;
        sizeType size() const;
        constReference front() const;
        constReference back() const;
        void push(constReference);
        void push(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        pop();
        void swap(Queue &);
        void clear();
#ifdef OTHER_FUNCTION
    public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_QUEUE
    public:
        container &getContainer() {
            return this->c;
        };
#endif
    };
    template <typename T>
    class Queue<T, T *, false, false> final {
#ifdef DEBUG
    public:
#include <iostream>
        void print() const {
            for(auto cursor {this->c}; cursor not_eq this->last;) {
                std::cout << *cursor++ << ", ";
            }
            std::cout << std::endl;
        }
#endif
        friend void swap(Queue &a, Queue &b) {
            a.swap(b);
        }
    private:
        using container = T *;
    private:
        class EmptyQueue;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = T &;
        using constReference = const T &;
        using pointer = T *;
        using constPointer = const T *;
        using constPointerConstant = const T *const;
        using rightValueReference = T &&;
    private:
        sizeType containerSize;
        container c;
        pointer last;
    private:
        bool full() const;
        void reallocate();
    public:
        explicit Queue(sizeType = 64);
        Queue(const Queue &);
        Queue(Queue &&) noexcept;
        Queue &operator=(const Queue &);
        Queue &operator=(Queue &&) noexcept;
        bool operator==(const Queue &) const;
        bool operator not_eq(const Queue &) const;
        bool operator<(const Queue &) const = delete;
        bool operator<=(const Queue &) const = delete;
        bool operator>(const Queue &) const = delete;
        bool operator>=(const Queue &) const = delete;
        explicit operator bool() const;
        ~Queue();
    public:
        bool empty() const;
        sizeType size() const;
        constReference front() const;
        constReference back() const;
        void push(constReference);
        void push(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        pop();
        void clear();
        void swap(Queue &);
#ifdef OTHER_FUNCTION
        public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_QUEUE
        public:
        container &getContainer() {
            return this->c;
        };
        sizeType &getContainerSize() {
            return this->containerSize;
        }
        pointer &getLast() {
            return this->last;
        }
#endif
    };
    template <typename T>
    class Queue<T, T *, true, false> final {
        friend inline void swap(Queue &a, Queue &b) {
            a.swap(b);
        }
    private:
        using container = T *;
    private:
        class EmptyQueue;
        class FullQueue;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = T &;
        using constReference = const T &;
        using pointer = T *;
        using constPointer = const T *;
        using constPointerConstant = const T *const;
        using rightValueReference = T &&;
    private:
        sizeType containerSize;
        container c;
        pointer first;
        pointer last;
    public:
        explicit Queue(sizeType = 64);
        Queue(const Queue &);
        Queue(Queue &&) noexcept;
        Queue &operator=(const Queue &);
        Queue &operator=(Queue &&) noexcept;
        bool operator==(const Queue &) const;
        bool operator not_eq(const Queue &) const;
        bool operator<(const Queue &) const = delete;
        bool operator<=(const Queue &) const = delete;
        bool operator>(const Queue &) const = delete;
        bool operator>=(const Queue &) const = delete;
        explicit operator bool() const;
        ~Queue();
    public:
        bool full() const;
        bool empty() const;
        sizeType size() const;
        constReference front() const;
        constReference back() const;
        void push(constReference);
        void push(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        pop();
        void clear();
        void swap(Queue &);
#ifdef OTHER_FUNCTION
        public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_QUEUE
        public:
        container &getContainer() {
            return this->c;
        };
        sizeType &getContainerSize() {
            return this->containerSize;
        }
        pointer &getLast() {
            return this->last;
        }
        pointer &getFirst() {
            return this->first;
        }
#endif
    };
    template <typename T>
    class Queue<T, T *, false, true> final {
        friend void swap(Queue &a, Queue &b) {
            a.swap(b);
        }
    private:
        using container = T *;
    private:
        class EmptyQueue;
        class FullQueue;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = T &;
        using constReference = const T &;
        using pointer = T *;
        using constPointer = const T *;
        using constPointerConstant = const T *const;
        using rightValueReference = T &&;
    private:
        sizeType containerSize;
        container c;
        pointer first;
        pointer last;
        bool tag;
    public:
        explicit Queue(sizeType = 64);
        Queue(const Queue &);
        Queue(Queue &&) noexcept;
        Queue &operator=(const Queue &);
        Queue &operator=(Queue &&) noexcept;
        bool operator==(const Queue &) const;
        bool operator not_eq(const Queue &) const;
        bool operator<(const Queue &) const = delete;
        bool operator<=(const Queue &) const = delete;
        bool operator>(const Queue &) const = delete;
        bool operator>=(const Queue &) const = delete;
        explicit operator bool() const;
        ~Queue();
    public:
        bool full() const;
        bool empty() const;
        sizeType size() const;
        constReference front() const;
        constReference back() const;
        void push(constReference);
        void push(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        pop();
        void clear();
        void swap(Queue &);
#ifdef OTHER_FUNCTION
        public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_QUEUE
        public:
        container &getContainer() {
            return this->c;
        };
        sizeType &getContainerSize() {
            return this->containerSize;
        }
        pointer &getLast() {
            return this->last;
        }
        pointer &getFirst() {
            return this->first;
        }
        bool &getTag() {
            return this->tag;
        }
#endif
    };
}

template <typename T, typename Container, bool sacrifice, bool tag>
inline bool
DataStructure::Queue<T, Container, sacrifice, tag>::operator==(const Queue &other) const {
    return this->c == other.c;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline bool
DataStructure::Queue<T, Container, sacrifice, tag>::operator not_eq(const Queue &other) const {
    return this->c not_eq other.c;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline bool
DataStructure::Queue<T, Container, sacrifice, tag>::operator<(const Queue &other) const {
    return this->c < other.c;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline bool
DataStructure::Queue<T, Container, sacrifice, tag>::operator<=(const Queue &other) const {
    return this->c <= other.c;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline bool
DataStructure::Queue<T, Container, sacrifice, tag>::operator>(const Queue &other) const {
    return this->c > other.c;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline bool
DataStructure::Queue<T, Container, sacrifice, tag>::operator>=(const Queue &other) const {
    return this->c >= other.c;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline DataStructure::Queue<T, Container, sacrifice, tag>::operator bool() const {
    if(this->c) {
        return true;
    }
    return false;
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline bool DataStructure::Queue<T, Container, sacrifice, tag>::empty() const {
    return this->c.empty();
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline typename DataStructure::Queue<T, Container, sacrifice, tag>::sizeType
DataStructure::Queue<T, Container, sacrifice, tag>::size() const {
    return this->c.size();
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline typename DataStructure::Queue<T, Container, sacrifice, tag>::constReference
DataStructure::Queue<T, Container, sacrifice, tag>::back() const {
    return this->c.back();
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline typename DataStructure::Queue<T, Container, sacrifice, tag>::constReference
DataStructure::Queue<T, Container, sacrifice, tag>::front() const {
    return this->c.front();
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline void DataStructure::Queue<T, Container, sacrifice, tag>::push(constReference value) {
    this->c.pushBack(value);
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline void DataStructure::Queue<T, Container, sacrifice, tag>::push(rightValueReference value) {
    this->c.pushBack(std::move(value));
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline
#ifdef POP_GET_PBJECT
typename DataStructure::Queue<T, Container, sacrifice, tag>::valueType
#else
void
#endif
DataStructure::Queue<T, Container, sacrifice, tag>::pop() {
#ifdef POP_GET_OBJECT
    return
#endif
    this->c.popFront();
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline void DataStructure::Queue<T, Container, sacrifice, tag>::clear() {
    this->c.clear();
}
template <typename T, typename Container, bool sacrifice, bool tag>
inline void DataStructure::Queue<T, Container, sacrifice, tag>::swap(Queue &other) {
    this->c.swap(other.c);
}

template <typename T>
class DataStructure::Queue<T, T *, false, false>::EmptyQueue : public DataStructure::RuntimeException {
public:
    explicit EmptyQueue(const char *error) : RuntimeException(error) {}
    explicit EmptyQueue(const std::string &error) : RuntimeException(error) {}
};

template <typename T>
class DataStructure::Queue<T, T *, true, false>::EmptyQueue : public DataStructure::RuntimeException {
public:
    explicit EmptyQueue(const char *error) : RuntimeException(error) {}
    explicit EmptyQueue(const std::string &error) : RuntimeException(error) {}
};
template <typename T>
class DataStructure::Queue<T, T *, true, false>::FullQueue : public DataStructure::RuntimeException {
public:
    explicit FullQueue(const char *error) : RuntimeException(error) {}
    explicit FullQueue(const std::string &error) : RuntimeException(error) {}
};

template <typename T>
class DataStructure::Queue<T, T *, false, true>::EmptyQueue : public DataStructure::RuntimeException {
public:
    explicit EmptyQueue(const char *error) : RuntimeException(error) {}
    explicit EmptyQueue(const std::string &error) : RuntimeException(error) {}
};
template <typename T>
class DataStructure::Queue<T, T *, false, true>::FullQueue : public DataStructure::RuntimeException {
public:
    explicit FullQueue(const char *error) : RuntimeException(error) {}
    explicit FullQueue(const std::string &error) : RuntimeException(error) {}
};

template <typename T>
inline bool DataStructure::Queue<T, T *, false, false>::full() const {
    return this->last == this->c + this->containerSize;
}
template <typename T>
inline void DataStructure::Queue<T, T *, false, false>::reallocate() {
    const auto size {this->size()};
    this->containerSize *= 2;
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))};
    for(auto i {0}; i < size; ++i) {
        new (newContainer + i) valueType(std::move(static_cast<rightValueReference>(this->c[i])));
    }
    this->clear();
    ::operator delete (this->c);
    this->c = newContainer;
    this->last = this->c + size;
}
template <typename T>
DataStructure::Queue<T, T *, false, false>::Queue(sizeType size) : containerSize {size},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        last {this->c} {}
template <typename T>
DataStructure::Queue<T, T *, false, false>::Queue(const Queue &other) : containerSize {other.containerSize},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        last {this->c} {
    for(auto cursor {other.c}; cursor not_eq other.last;) {
        new (this->last++) valueType(*cursor++);
    }
}
template <typename T>
DataStructure::Queue<T, T *, false, false>::Queue(Queue &&other) noexcept : containerSize {other.containerSize},
        c {other.c}, last {other.last} {
    other.containerSize = 0;
    other.c = other.last = nullptr;
}
template <typename T>
DataStructure::Queue<T, T *, false, false>::~Queue() {
    this->clear();
    ::operator delete (this->c);
}
template <typename T>
DataStructure::Queue<T, T *, false, false> &
DataStructure::Queue<T, T *, false, false>::operator=(const Queue &other) {
    if(&other == this) {
        return *this;
    }
    this->clear();
    ::operator delete (this->c);
    this->containerSize = other.containerSize;
    this->c = reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize));
    this->last = this->c;
    for(auto cursor {other.c}; cursor not_eq other.last;) {
        new (this->last++) valueType(*cursor++);
    }
    return *this;
}
template <typename T>
DataStructure::Queue<T, T *, false, false> &
DataStructure::Queue<T, T *, false, false>::operator=(Queue &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->clear();
    ::operator delete (this->c);
    this->c = other.c;
    this->last = other.last;
    this->containerSize = other.containerSize;
    other.c = other.last = nullptr;
    other.containerSize = 0;
    return *this;
}
template <typename T>
inline bool DataStructure::Queue<T, T *, false, false>::operator==(const Queue &other) const {
    return this->size() == other.size() and [&]() -> bool {
        for(auto thisCursor {this->c}, otherCursor {other.c}; thisCursor not_eq this->last;) {
            if(*thisCursor++ not_eq *otherCursor++) {
                return false;
            }
        }
        return true;
    }();
}
template <typename T>
bool DataStructure::Queue<T, T *, false, false>::operator not_eq(const Queue &other) const {
    return not(*this == other);
}
template <typename T>
inline DataStructure::Queue<T, T *, false, false>::operator bool() const {
    return not this->empty();
}
template <typename T>
inline bool DataStructure::Queue<T, T *, false, false>::empty() const {
    return this->c == this->last;
}
template <typename T>
inline typename DataStructure::Queue<T, T *, false, false>::sizeType
DataStructure::Queue<T, T *, false, false>::size() const {
    return static_cast<sizeType>(this->last - this->c);
}
template <typename T>
typename DataStructure::Queue<T, T *, false, false>::constReference
DataStructure::Queue<T, T *, false, false>::front() const {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
    return *this->c;
}
template <typename T>
typename DataStructure::Queue<T, T *, false, false>::constReference
DataStructure::Queue<T, T *, false, false>::back() const {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
    return *(this->last - 1);
}
template <typename T>
void DataStructure::Queue<T, T *, false, false>::push(constReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->last++) valueType(value);
}
template <typename T>
void DataStructure::Queue<T, T *, false, false>::push(rightValueReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->last++) valueType(std::move(value));
}
template <typename T>
#ifdef POP_GET_OBJECT
typename DataStructure::Queue<T, T *, false, false>::valueType
#else
void
#endif
DataStructure::Queue<T, T *, false, false>::pop() {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
#ifdef POP_GET_OBJECT
    valueType temp {std::move(static_cast<rightValueReference>(*this->c))};
#endif
    auto size {this->size() - 1};
    if(not size) {
        (--this->last)->~valueType();
#ifdef POP_GET_OBJECT
        return temp;
#else
        return;
#endif
    }
    for(auto i {0}; i < size; ++i) {
        this->c[i].~valueType();
        new (this->c + i) valueType(std::move(static_cast<rightValueReference>(this->c[i + 1])));
    }
    (--this->last)->~valueType();
#ifdef POP_GET_OBJECT
    return temp;
#endif
}
template <typename T>
inline void DataStructure::Queue<T, T *, false, false>::clear() {
    while(this->last-- not_eq this->c) {
        this->last->~valueType();
    }
}
template <typename T>
void DataStructure::Queue<T, T *, false, false>::swap(Queue &other) {
    using std::swap;
    swap(this->c, other.c);
    swap(this->containerSize, other.containerSize);
    swap(this->last, other.last);
}

template <typename T>
DataStructure::Queue<T, T *, true, false>::Queue(sizeType size) : containerSize {++size},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        first {this->c}, last {this->c} {}
template <typename T>
DataStructure::Queue<T, T *, true, false>::Queue(const Queue &other) : containerSize {other.containerSize},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        first {this->c + (other.first - other.c)}, last {this->first} {
    auto cursor {other.first};
    const auto last {other.last + 1};
    while(cursor not_eq last) {
        new (this->last++) valueType(*cursor++);
        if(this->last == this->c + this->containerSize) {
            this->last = this->c;
        }
    }
}
template <typename T>
DataStructure::Queue<T, T *, true, false>::Queue(Queue &&other) noexcept :
        containerSize {other.containerSize}, c {other.c}, first {other.first}, last {other.last} {
    other.first = other.last = other.c = nullptr;
    other.containerSize = 0;
}
template <typename T>
DataStructure::Queue<T, T *, true, false>::~Queue() {
    this->clear();
    ::operator delete (this->c);
}
template <typename T>
DataStructure::Queue<T, T *, true, false> &
DataStructure::Queue<T, T *, true, false>::operator=(const Queue &other) {
    if(&other == this) {
        return *this;
    }
    this->clear();
    ::operator delete (this->c);
    this->containerSize = other.containerSize;
    this->c = reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize));
    this->first = this->c + (other.first - other.c);
    this->last = this->first;
    auto cursor {other.first};
    const auto last {other.last + 1};
    while(cursor not_eq last) {
        new (this->last++) valueType(*cursor++);
        if(this->last == this->c + this->containerSize) {
            this->last = this->c;
        }
    }
    return *this;
}
template <typename T>
DataStructure::Queue<T, T *, true, false> &
DataStructure::Queue<T, T *, true, false>::operator=(Queue &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->clear();
    ::operator delete (this->c);
    this->containerSize = other.containerSize;
    this->c = other.c;
    this->first = other.first;
    this->last = other.last;
    other.c = other.first = other.last = nullptr;
    other.containerSize = 0;
    return *this;
}
template <typename T>
inline bool DataStructure::Queue<T, T *, true, false>::operator==(const Queue &other) const {
    return this->size() == other.size() and [&]() -> bool {
        auto last {this->last + 1};
        auto thisLast {this->c + this->containerSize};
        auto otherLast {other.c + other.containerSize};
        for(auto thisCursor {this->first}, otherCursor {other.first}; thisCursor not_eq last;) {
            if(*thisCursor++ not_eq *otherCursor++) {
                return false;
            }
            if(thisCursor == thisLast) {
                thisCursor = this->c;
            }
            if(otherCursor == otherLast) {
                otherCursor = other.c;
            }
        }
        return true;
    }();
}
template <typename T>
bool DataStructure::Queue<T, T *, true, false>::operator not_eq(const Queue &other) const {
    return not(*this == other);
}
template <typename T>
inline DataStructure::Queue<T, T *, true, false>::operator bool() const {
    return not this->empty();
}
template <typename T>
inline bool DataStructure::Queue<T, T *, true, false>::empty() const {
    return this->first == this->last;
}
template <typename T>
inline bool DataStructure::Queue<T, T *, true, false>::full() const {
    auto increment {this->last + 1};
    return increment == this->c + this->containerSize ? this->first == this->c : increment == this->first;
}
template <typename T>
typename DataStructure::Queue<T, T *, true, false>::sizeType
DataStructure::Queue<T, T *, true, false>::size() const {
    return static_cast<sizeType>(this->first == this->last ? (this->tag ? this->containerSize : 0) : (
            this->first > this->last ? this->last - this->first : this->containerSize - (
                    this->first - this->first
            )
    ));
}
template <typename T>
typename DataStructure::Queue<T, T *, true, false>::constReference
DataStructure::Queue<T, T *, true, false>::front() const {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
    return *this->first;
}
template <typename T>
typename DataStructure::Queue<T, T *, true, false>::constReference
DataStructure::Queue<T, T *, true, false>::back() const {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
    return *this->last;
}
template <typename T>
void DataStructure::Queue<T, T *, true, false>::push(constReference value) {
    if(this->full()) {
        throw FullQueue("The queue is full!");
    }
    new (this->last++) valueType(value);
    if(this->last == this->c + this->containerSize) {
        this->last = this->c;
    }
}
template <typename T>
void DataStructure::Queue<T, T *, true, false>::push(rightValueReference value) {
    if(this->full()) {
        throw FullQueue("The queue is full!");
    }
    new (this->last++) valueType(std::move(value));
    if(this->last == this->c + this->containerSize) {
        this->last = this->c;
    }
}
template <typename T>
#ifdef POP_GET_OBJECT
typename DataStructure::Queue<T, T *, true, false>::valueType
#else
void
#endif
DataStructure::Queue<T, T *, true, false>::pop() {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
#ifdef POP_GET_OBJECT
    auto temp {std::move(static_cast<rightValueReference>(*this->first))};
#endif
    this->first++->~valueType();
    //this->first + 1 == this->c + this->containerSize ? this->first = this->c : ++this->first;
    //this->first = this->c + (this->first - this->c + 1) % this->containerSize;
    if(this->first == this->c + this->containerSize) {
        this->first = this->c;
    }
#ifdef POP_GET_OBJECT
    return temp;
#endif
}
template <typename T>
inline void DataStructure::Queue<T, T *, true, false>::clear() {
    if(this->empty()) {
        return;
    }
    auto last {this->c + this->containerSize};
    while(this->first not_eq this->last) {
        if(this->first == last) {
            this->first = this->c;
        }
        this->first++->~valueType();
    }
}
template <typename T>
void DataStructure::Queue<T, T *, true, false>::swap(Queue &other) {
    using std::swap;
    swap(this->c, other.c);
    swap(this->containerSize, other.containerSize);
    swap(this->first, other.first);
    swap(this->last, other.last);
}

template <typename T>
DataStructure::Queue<T, T *, false, true>::Queue(sizeType size) : containerSize {size},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        first {this->c}, last {this->first}, tag {false} {}
template <typename T>
DataStructure::Queue<T, T *, false, true>::Queue(const Queue &other) : containerSize {other.containerSize},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        first {this->c}, last {this->first}, tag {other.tag} {
    auto cursor {other.first};
    const auto last {other.last + 1};
    while(cursor not_eq last) {
        new (this->last++) valueType(*cursor++);
        if(this->last == this->c + this->containerSize) {
            this->last = this->c;
        }
    }
}
template <typename T>
DataStructure::Queue<T, T *, false, true>::Queue(Queue &&other) noexcept : containerSize {other.containerSize},
        c {other.c}, first {other.first}, last {other.last}, tag {other.tag} {
    other.c = nullptr;
}
template <typename T>
DataStructure::Queue<T, T *, false, true>::~Queue() {
    this->clear();
    ::operator delete (this->c);
}
template <typename T>
DataStructure::Queue<T, T *, false, true> &
DataStructure::Queue<T, T *, false, true>::operator=(const Queue &other) {
    if(&other == this) {
        return *this;
    }
    this->clear();
    ::operator delete (this->c);
    this->containerSize = other.containerSize;
    this->c = reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize));
    this->first = this->c;
    this->last = this->first;
    this->tag = other.tag;
    auto cursor {other.first};
    const auto last {other.last + 1};
    while(cursor not_eq last) {
        new (this->last++) valueType(*cursor++);
        if(this->last == this->c + this->containerSize) {
            this->last = this->c;
        }
    }
    return *this;
}
template <typename T>
DataStructure::Queue<T, T *, false, true> &
DataStructure::Queue<T, T *, false, true>::operator=(Queue &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->clear();
    ::operator delete (this->c);
    this->containerSize = other.containerSize;
    this->c = other.c;
    this->first = other.first;
    this->last = other.last;
    this->tag = other.tag;
    other.c = nullptr;
    return *this;
}
template <typename T>
inline bool DataStructure::Queue<T, T *, false, true>::operator==(const Queue &other) const {
    return this->size() == other.size() and [&]() -> bool {
        const auto last {this->last + 1};
        const auto thisLast {this->c + this->containerSize};
        const auto otherLast {other.c + other.containerSize};
        for(auto thisCursor {this->first}, otherCursor {other.first}; thisCursor not_eq last;) {
            if(*thisCursor++ not_eq *otherCursor++) {
                return false;
            }
            if(thisCursor == thisLast) {
                thisCursor = this->c;
            }
            if(otherCursor == otherLast) {
                otherCursor = other.c;
            }
        }
        return true;
    }();
}
template <typename T>
bool DataStructure::Queue<T, T *, false, true>::operator not_eq(const Queue &other) const {
    return not(*this == other);
}
template <typename T>
inline DataStructure::Queue<T, T *, false, true>::operator bool() const {
    return not this->empty();
}
template <typename T>
inline bool DataStructure::Queue<T, T *, false, true>::empty() const {
    return not this->tag and this->first == this->last;
}
template <typename T>
inline bool DataStructure::Queue<T, T *, false, true>::full() const {
    return this->tag and this->first == this->last;
}
template <typename T>
typename DataStructure::Queue<T, T *, false, true>::sizeType
DataStructure::Queue<T, T *, false, true>::size() const {
    return static_cast<sizeType>(this->first == this->last ? (this->tag ? this->containerSize : 0) : (
            this->first > this->last ? this->last - this->first : this->containerSize - (
                    this->first - this->last
            )
    ));
}
template <typename T>
typename DataStructure::Queue<T, T *, false, true>::constReference
DataStructure::Queue<T, T *, false, true>::front() const {
    return *this->first;
}
template <typename T>
typename DataStructure::Queue<T, T *, false, true>::constReference
DataStructure::Queue<T, T *, false, true>::back() const {
    return *this->last;
}
template <typename T>
void DataStructure::Queue<T, T *, false, true>::push(constReference value) {
    if(this->full()) {
        throw FullQueue("The queue is full!");
    }
    new (this->last++) valueType(value);
    if(this->last == this->c + this->containerSize) {
        this->last = this->c;
    }
    if(this->last == this->first) {
        this->tag = true;
    }
}
template <typename T>
void DataStructure::Queue<T, T *, false, true>::push(rightValueReference value) {
    if(this->full()) {
        throw FullQueue("The queue is full!");
    }
    new (this->last++) valueType(std::move(value));
    if(this->last == this->c + this->containerSize) {
        this->last = this->c;
    }
    if(this->last == this->first) {
        this->tag = true;
    }
}
template <typename T>
#ifdef POP_GET_OBJECT
typename DataStructure::Queue<T, T *, false, true>::valueType
#else
void
#endif
DataStructure::Queue<T, T *, false, true>::pop() {
    if(this->empty()) {
        throw EmptyQueue("The queue is empty!");
    }
#ifdef POP_GET_OBJECT
    auto temp {std::move(static_cast<rightValueReference>(*this->first))};
#endif
    this->first++->~valueType();
    if(this->first == this->c + this->containerSize) {
        this->first = this->c;
    }
    this->tag = false;
#ifdef POP_GET_OBJECT
    return temp;
#endif
}
template <typename T>
inline void DataStructure::Queue<T, T *, false, true>::clear() {
    if(this->empty()) {
        return;
    }
    const auto last {this->c + this->containerSize};
    while(this->first not_eq this->last or this->tag) {
        this->first++->~valueType();
        if(this->first == last) {
            this->first = this->c;
            this->tag = false;
        }
    }
}
template <typename T>
void DataStructure::Queue<T, T *, false, true>::swap(Queue &other) {
    using std::swap;
    swap(this->containerSize, other.containerSize);
    swap(this->first, other.first);
    swap(this->last, other.last);
    swap(this->c, other.c);
    swap(this->tag, other.tag);
}

#ifdef OTHER_FUNCTION
template <typename T, typename Container, bool Sacrifice, bool Tag>
inline void DataStructure::Queue<T, Container, Sacrifice, Tag>::resize(sizeType size) {
    this->c.resize(size);
}
template <typename T, typename Container, bool Sacrifice, bool Tag>
inline void DataStructure::Queue<T, Container, Sacrifice, Tag>::shrinkToFit() {
    this->c.shrinkToFit();
}
template <typename T, typename Container, bool Sacrifice, bool Tag>
inline typename DataStructure::Queue<T, Container, Sacrifice, Tag>::sizeType
DataStructure::Queue<T, Container, Sacrifice, Tag>::reserve() const {
    return this->c.reserve();
}
template <typename T, typename Container, bool Sacrifice, bool Tag>
inline typename DataStructure::Queue<T, Container, Sacrifice, Tag>::sizeType
DataStructure::Queue<T, Container, Sacrifice, Tag>::capacity() const {
    return this->c.capacity();
}

template <typename T>
void DataStructure::Queue<T, T *, false, false>::resize(sizeType size) {
    if(size <= this->containerSize) {
        return;
    }
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    const auto exists {this->size()};
    for(auto i {0}; i < exists; ++i) {
        new (newContainer + i) valueType(std::move(static_cast<rightValueReference>(this->c[i])));
    }
    this->clear();
    ::operator delete (this->c);
    this->last = newContainer + static_cast<differenceType>(exists);
    this->c = newContainer;
    this->containerSize = size;
}
template <typename T>
void DataStructure::Queue<T, T *, false, false>::shrinkToFit() {
    const auto size {this->size()};
    if(size == this->containerSize) {
        return;
    }
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    for(auto i {0}; i < size; ++i) {
        new (newContainer + 1) valueType(std::move(static_cast<rightValueReference>(this->c[i])));
    }
    this->clear();
    ::operator delete (this->c);
    this->last = newContainer + static_cast<differenceType>(size);
    this->c = newContainer;
    this->containerSize = size;
}
template <typename T>
typename DataStructure::Queue<T, T *, false, false>::sizeType
DataStructure::Queue<T, T *, false, false>::reserve() const {
    return this->containerSize - this->size();
}
template <typename T>
typename DataStructure::Queue<T, T *, false, false>::sizeType
DataStructure::Queue<T, T *, false, false>::capacity() const {
    return this->containerSize;
}

template <typename T>
void DataStructure::Queue<T, T *, true, false>::resize(sizeType size) {
    if(size <= this->containerSize) {
        return;
    }
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    const auto last {this->c + this->containerSize};
    auto cursor {this->first};
    auto count {0};
    while(cursor not_eq this->last) {
        new (newContainer + count++) valueType(std::move(static_cast<rightValueReference>(*cursor++)));
        if(cursor == last) {
            cursor = this->c;
        }
    }
    this->clear();
    this->first = newContainer + (this->first - this->c);
    this->last = newContainer + (this->last - this->c);
    ::operator delete (this->c);
    this->c = newContainer;
    this->containerSize = size;
}
template <typename T>
void DataStructure::Queue<T, T *, true, false>::shrinkToFit() {
    const auto size {this->size()};
    if(size == this->containerSize) {
        return;
    }
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    const auto last {this->c + this->containerSize};
    auto cursor {this->first};
    auto count {0};
    while(cursor not_eq this->last) {
        new (newContainer + count++) valueType(std::move(static_cast<rightValueReference>(*cursor++)));
        if(cursor == last) {
            cursor = this->c;
        }
    }
    this->clear();
    this->first = newContainer + (this->first - this->c);
    this->last = newContainer + (this->last - this->c);
    ::operator delete (this->c);
    this->c = newContainer;
    this->containerSize = size;
}
template <typename T>
typename DataStructure::Queue<T, T *, true, false>::sizeType
DataStructure::Queue<T, T *, true, false>::reserve() const {
    return this->containerSize - this->size();
}
template <typename T>
typename DataStructure::Queue<T, T *, true, false>::sizeType
DataStructure::Queue<T, T *, true, false>::capacity() const {
    return this->containerSize;
}

template <typename T>
void DataStructure::Queue<T, T *, false, true>::resize(sizeType size) {
    if(size <= this->containerSize) {
        return;
    }
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    const auto last {this->c + this->containerSize};
    auto cursor {this->first};
    auto count {0};
    while(cursor not_eq this->last) {
        new (newContainer + count++) valueType(std::move(static_cast<rightValueReference>(*cursor++)));
        if(cursor == last) {
            cursor = this->c;
        }
    }
    this->clear();
    this->first = newContainer + (this->first - this->c);
    this->last = newContainer + (this->last - this->c);
    ::operator delete (this->c);
    this->c = newContainer;
    this->containerSize = size;
    this->tag = false;
}
template <typename T>
void DataStructure::Queue<T, T *, false, true>::shrinkToFit() {
    const auto size {this->size()};
    if(size == this->containerSize) {
        return;
    }
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    const auto last {this->c + this->containerSize};
    auto cursor {this->first};
    auto count {0};
    while(cursor not_eq this->last) {
        new (newContainer + count++) valueType(std::move(static_cast<rightValueReference>(*cursor++)));
        if(cursor == last) {
            cursor = this->c;
        }
    }
    this->clear();
    this->first = newContainer + (this->first - this->c);
    this->last = newContainer + (this->last - this->c);
    ::operator delete (this->c);
    this->c = newContainer;
    this->containerSize = size;
    this->tag = false;
}
template <typename T>
typename DataStructure::Queue<T, T *, false, true>::sizeType
DataStructure::Queue<T, T *, false, true>::reserve() const {
    return this->containerSize - this->size();
}
template <typename T>
typename DataStructure::Queue<T, T *, false, true>::sizeType
DataStructure::Queue<T, T *, false, true>::capacity() const {
    return this->containerSize;
}
#endif

#endif //DATA_STRUCTURE_QUEUE_HPP
