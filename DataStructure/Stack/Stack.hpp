#ifndef DATA_STRUCTURE_STACK_HPP
#define DATA_STRUCTURE_STACK_HPP

#include "Vector.hpp"

namespace DataStructure {
    template <typename T, typename Container = DataStructure::Vector<T>, bool Bilateral = false>
    class Stack {
        friend inline void swap(Stack &a, Stack &b) {
            a.swap(b);
        }
    private:
        using container = Container;
    public:
        using sizeType = typename container::sizeType;
        using differenceType = typename container::differenceType;
        using valueType = typename container::valueType;
        using constType = typename container::constType;
        using reference = typename container::reference;
        using constReference = typename container::constReference;
        using pointer = typename container::pointer;
        using constPointer = typename container::constPointer;
        using constPointerConstant = typename container::constPointerConstant;
        using rightValueReference = typename container::rightValueReference;
    protected:
        container c;
    public:
        Stack() = default;
        Stack(const Stack &) = default;
        Stack(Stack &&) noexcept = default;
        Stack &operator=(const Stack &) = default;
        Stack &operator=(Stack &&) noexcept = default;
        bool operator==(const Stack &) const;
        bool operator not_eq(const Stack &) const;
        bool operator<(const Stack &) const;
        bool operator<=(const Stack &) const;
        bool operator>(const Stack &) const;
        bool operator>=(const Stack &) const;
        explicit operator bool() const;
        ~Stack() = default;
    public:
        bool empty() const;
        sizeType size() const;
        constReference top() const;
        void push(constReference);
        void push(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        pop();
        void clear();
        void swap(Stack &);
#ifdef OTHER_FUNCTION
    public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_STACK
    public:
        container &getContainer() {
            return this->c;
        }
#endif
    };
}

template <typename T>
class DataStructure::Stack<T, T *, false> final {
    friend inline void swap(Stack &a, Stack &b) {
        a.swap(b);
    }
private:
    using container = T *;
private:
    class EmptyStack;
public:
    using sizeType = unsigned long;
    using differenceType = long;
    using valueType = T;
    using constType = const T;
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
#ifdef OTHER_FUNCTION
    void reallocate(sizeType = 0);
#else
    void reallocate();
#endif
    bool full() const;
public:
    explicit Stack(sizeType = 64);
    Stack(const Stack &);
    Stack(Stack &&) noexcept;
    Stack &operator=(const Stack &);
    Stack &operator=(Stack &&) noexcept;
    bool operator==(const Stack &) const;
    bool operator not_eq(const Stack &) const;
    bool operator<(const Stack &) const;
    bool operator<=(const Stack &) const;
    bool operator>(const Stack &) const;
    bool operator>=(const Stack &) const;
    explicit operator bool() const;
    ~Stack();
public:
    bool empty() const;
    sizeType size() const;
    constReference top() const;
    void push(constReference);
    void push(rightValueReference);
#ifdef POP_GET_OBJECT
    valueType
#else
    void
#endif
    pop();
    void clear();
    void swap(Stack &);
#ifdef OTHER_FUNCTION
    public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_STACK
    public:
        container &getContainer() {
            return this->c;
        }
        pointer &getLast() {
            return this->last;
        }
        sizeType &getContainerSize() {
            return this->containerSize;
        }
#endif
};
template <typename T>
class DataStructure::Stack<T, T *, true> final {
    friend void swap(Stack &, Stack &);
private:
    using container = T *;
private:
    class EmptyStack;
public:
    using sizeType = unsigned long;
    using differenceType = long;
    using valueType = T;
    using constType = const T;
    using reference = T &;
    using constReference = const T &;
    using pointer = T *;
    using constPointer = const T *;
    using constPointerConstant = const T *const;
    using rightValueReference = T &&;
private:
    sizeType containerSize;
    container c;
    pointer leftLast;
    pointer rightLast;
private:
#ifdef OTHER_FUNCTION
    void reallocate(sizeType = 0);
#else
    void reallocate();
#endif
    bool full() const;
public:
    explicit Stack(sizeType = 128);
    Stack(const Stack &);
    Stack(Stack &&) noexcept;
    Stack &operator=(const Stack &);
    Stack &operator=(Stack &&) noexcept;
    bool operator==(const Stack &) const;
    bool operator not_eq(const Stack &) const;
    bool operator<(const Stack &) const = delete;
    bool operator<=(const Stack &) const = delete;
    bool operator>(const Stack &) const = delete;
    bool operator>=(const Stack &) const = delete;
    explicit operator bool() const;
    ~Stack();
public:
    bool empty() const;
    bool frontEmpty() const;
    bool backEmpty() const;
    sizeType size() const;
    sizeType frontSize() const;
    sizeType backSize() const;
    constReference top() const;
    void pushFront(constReference);
    void pushFront(rightValueReference);
    void pushBack(constReference);
    void pushBack(rightValueReference);
#ifdef POP_GET_OBJECT
    valueType
#else
    void
#endif
    popFront();
#ifdef POP_GET_OBJECT
    valueType
#else
    void
#endif
    popBack();
    void clear();
    void frontClear();
    void backClear();
    void frontSwap(Stack &);
    void backSwap(Stack &);
    void swap(Stack &);
#ifdef OTHER_FUNCTION
    public:
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_STACK
    public:
        container &getContainer() {
            return this->c;
        }
        pointer &getLeftLast() {
            return this->leftLast;
        }
        pointer &getRightLast() {
            return this->rightLast;
        }
        sizeType &getContainerSize() {
            return this->containerSize;
        }
#endif
};

template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::operator==(const Stack &other) const {
    return this->c == other.c;
}
template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::operator not_eq(const Stack &other) const {
    return this->c not_eq other.c;
}
template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::operator<(const Stack &other) const {
    return this->c < other.c;
}
template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::operator<=(const Stack &other) const {
    return this->c <= other.c;
}
template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::operator>(const Stack &other) const {
    return this->c > other.c;
}
template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::operator>=(const Stack &other) const {
    return this->c >= other.c;
}
template <typename T, typename Container, bool Bilateral>
inline DataStructure::Stack<T, Container, Bilateral>::operator bool() const {
    return static_cast<bool>(this->c);
}
template <typename T, typename Container, bool Bilateral>
inline bool DataStructure::Stack<T, Container, Bilateral>::empty() const {
    return this->c.empty();
}
template <typename T, typename Container, bool Bilateral>
inline typename DataStructure::Stack<T, Container, Bilateral>::sizeType
DataStructure::Stack<T, Container, Bilateral>::size() const {
    return this->c.size();
}
template <typename T, typename Container, bool Bilateral>
inline typename DataStructure::Stack<T, Container, Bilateral>::constReference
DataStructure::Stack<T, Container, Bilateral>::top() const {
    return this->c.back();
}
template <typename T, typename Container, bool Bilateral>
inline void DataStructure::Stack<T, Container, Bilateral>::push(constReference value) {
    this->c.pushBack(value);
}
template <typename T, typename Container, bool Bilateral>
inline void DataStructure::Stack<T, Container, Bilateral>::push(rightValueReference value) {
    this->c.pushBack(std::move(value));
}
template <typename T, typename Container, bool Bilateral>
inline
#ifdef POP_GET_OBJECT
typename DataStructure::Stack<T, Container>::valueType
#else
void
#endif
DataStructure::Stack<T, Container, Bilateral>::pop() {
#ifndef POP_GET_OBJECT
    this->c.popBack();
#else
    return this->c.popBack();
#endif
}
template <typename T, typename Container, bool Bilateral>
inline void DataStructure::Stack<T, Container, Bilateral>::clear() {
    this->c.clear();
}
template <typename T, typename Container, bool Bilateral>
inline void DataStructure::Stack<T, Container, Bilateral>::swap(Stack &other) {
    this->c.swap(other.c);
}

template <typename T>
class DataStructure::Stack<T, T *, false>::EmptyStack : public DataStructure::RuntimeException {
public:
    explicit EmptyStack(const char *error) : RuntimeException(error) {}
    explicit EmptyStack(const std::string &error) : RuntimeException(error) {}
};

template <typename T>
class DataStructure::Stack<T, T *, true>::EmptyStack : public DataStructure::RuntimeException {
public:
    explicit EmptyStack(const char *error) : RuntimeException(error) {}
    explicit EmptyStack(const std::string &error) : RuntimeException(error) {}
};

template <typename T>
void DataStructure::Stack<T, T *, false>::reallocate(
#ifdef OTHER_FUNCTION
        sizeType size
#endif
        ) {
#ifdef OTHER_FUNCTION
    if(size) {
        if(size < this->containerSize) {
            return;
        }
        this->containerSize = size;
    }else {
        this->containerSize *= 2;
    }
#else
    this->containerSize *= 2;
#endif
    auto newContainer {
        reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))
    };
    auto i {0};
    for(auto cursor {this->c}; cursor not_eq this->last;) {
        new (&newContainer[i++]) valueType(std::move(*cursor));
        cursor++->~valueType();
    }
    ::operator delete (this->c);
    this->c = newContainer;
    this->last = this->c + i;
}
template <typename T>
bool DataStructure::Stack<T, T *, false>::full() const {
    return this->c + this->containerSize == this->last;
}
template <typename T>
DataStructure::Stack<T, T *, false>::Stack(sizeType size) : containerSize {size},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        last {this->c} {}
template <typename T>
DataStructure::Stack<T, T *, false>::Stack(const Stack &other) : containerSize {other.containerSize},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        last {this->c} {
    for(auto i {other.c}; i not_eq other.last;) {
        new (this->last++) valueType(*i++);
    }
}
template <typename T>
DataStructure::Stack<T, T *, false>::Stack(Stack &&other) noexcept :
        containerSize {other.containerSize}, c {other.c}, last {other.last} {
    other.containerSize = 0;
    other.c = other.last = nullptr;
}
template <typename T>
DataStructure::Stack<T, T *, false>::~Stack() {
    delete[] this->c;
}
template <typename T>
DataStructure::Stack<T, T *, false> &
DataStructure::Stack<T, T *, false>::operator=(const Stack &other) {
    if(&other == this) {
        return *this;
    }
    delete[] this->c;
    this->containerSize = other.containerSize;
    this->c = reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize));
    this->last = this->c;
    for(auto i {other.c}; i not_eq other.last;) {
        new (this->last++) valueType(*i++);
    }
    return *this;
}
template <typename T>
DataStructure::Stack<T, T *, false> &
DataStructure::Stack<T, T *, false>::operator=(Stack &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    delete[] this->c;
    this->c = other.c;
    this->containerSize = other.containerSize;
    this->last = other.last;
    other.containerSize = 0;
    other.c = other.last = nullptr;
    return *this;
}
template <typename T>
inline bool DataStructure::Stack<T, T *, false>::operator==(const Stack &other) const {
    return this->size() == other.size() and [&]() -> bool {
        for(auto i {this->c}, j {other.c}; i not_eq this->last;) {
            if(*i++ not_eq *j++) {
                return false;
            }
        }
        return true;
    }();
}
template <typename T>
bool DataStructure::Stack<T, T *, false>::operator not_eq(const Stack &other) const {
    return not(*this == other);
}
template <typename T>
inline bool DataStructure::Stack<T, T *, false>::operator<(const Stack &other) const {
    auto thisSize {this->size()};
    auto otherSize {other.size()};
    if(thisSize not_eq otherSize) {
        return thisSize < otherSize;
    }
    return [&]() -> bool {
        for(auto i {this->c}, j {other.c}; i not_eq this->last; ++i, ++j) {
            if(*i not_eq *j) {
                return *i < *j;
            }
        }
        return false;
    }();
}
template <typename T>
inline bool DataStructure::Stack<T, T *, false>::operator<=(const Stack &other) const {
    return *this < other or *this == other;
}
template <typename T>
bool DataStructure::Stack<T, T *, false>::operator>(const Stack &other) const {
    return not(*this <= other);
}
template <typename T>
bool DataStructure::Stack<T, T *, false>::operator>=(const Stack &other) const {
    return not(*this < other);
}
template <typename T>
DataStructure::Stack<T, T *, false>::operator bool() const {
    return this->c not_eq this->last;
}
template <typename T>
bool DataStructure::Stack<T, T *, false>::empty() const {
    return this->c == this->last;
}
template <typename T>
typename DataStructure::Stack<T, T *, false>::sizeType
DataStructure::Stack<T, T *, false>::size() const {
    return static_cast<sizeType>(this->last - this->c);
}
template <typename T>
typename DataStructure::Stack<T, T *, false>::constReference
DataStructure::Stack<T, T *, false>::top() const {
    if(this->empty()) {
        throw EmptyStack("The Stack is empty!");
    }
    return *(this->last - 1);
}
template <typename T>
void DataStructure::Stack<T, T *, false>::push(constReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->last++) valueType(value);
}
template <typename T>
void DataStructure::Stack<T, T *, false>::push(rightValueReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->last++) valueType(std::move(value));
}
template <typename T>
#ifdef POP_GET_OBJECT
typename DataStructure::Stack<T, T *, false>::valueType
#else
void
#endif
DataStructure::Stack<T, T *, false>::pop() {
    if(this->empty()) {
        throw EmptyStack("The Stack is empty!");
    }
#ifndef POP_GET_OBJECT
    (--this->last)->~valueType();
#else
    --this->last;
    auto temp {static_cast<rightValueReference>(*this->last)};
    this->last->~valueType();
    return temp;
#endif
}
template <typename T>
void DataStructure::Stack<T, T *, false>::clear() {
    while(--this->last not_eq this->c) {
        this->last->~valueType();
    }
    this->last->~valueType();
}
template <typename T>
void DataStructure::Stack<T, T *, false>::swap(Stack &other) {
    using std::swap;
    swap(this->containerSize, other.containerSize);
    swap(this->c, other.c);
    swap(this->last, other.last);
}

template <typename T>
inline void DataStructure::Stack<T, T *, true>::reallocate(
#ifdef OTHER_FUNCTION
        sizeType size
#endif
        ) {
    const auto last {this->c + (this->containerSize - 1)};
    const auto frontSize {this->frontSize()};
    const auto backSize {this->backSize()};
#ifdef OTHER_FUNCTION
    if(size) {
        if(size < this->containerSize) {
            return;
        }
        this->containerSize = size;
    }else {
        this->containerSize *= 2;
    }
#else
    this->containerSize *= 2;
#endif
    auto newContainer {
            reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))
    };
    auto cursor {newContainer + (frontSize - 1)};
    while(this->leftLast-- not_eq this->c) {
        new (cursor--) valueType(std::move(static_cast<rightValueReference>(*this->leftLast)));
        this->leftLast->~valueType();
    }
    cursor = newContainer + (this->containerSize - backSize);
    while(this->rightLast++ not_eq last) {
        new (cursor++) valueType(std::move(static_cast<rightValueReference>(*this->rightLast)));
        this->rightLast->~valueType();
    }
    ::operator delete (this->c);
    this->c = newContainer;
    this->leftLast = this->c + frontSize;
    this->rightLast = this->c + (this->containerSize - backSize - 1);
}
template <typename T>
inline bool DataStructure::Stack<T, T *, true>::full() const {
    return this->leftLast + 1 == this->rightLast;
}
template <typename T>
DataStructure::Stack<T, T *, true>::Stack(sizeType size) : containerSize {size},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        leftLast {this->c}, rightLast {this->c + (this->containerSize - 1)} {}
template <typename T>
DataStructure::Stack<T, T *, true>::Stack(const Stack &other) : containerSize {other.containerSize},
        c {reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))},
        leftLast {this->c}, rightLast {this->c + (this->containerSize - 1)} {
    for(auto i {other.c}; i not_eq other.leftLast;) {
        new (this->leftLast++) valueType(*i++);
    }
    for(auto i {other.c + (this->containerSize - 1)}; i not_eq other.rightLast;) {
        new (this->rightLast--) valueType(*i--);
    }
}
template <typename T>
DataStructure::Stack<T, T *, true>::Stack(Stack &&other) noexcept : containerSize {other.containerSize},
        c {other.c}, leftLast {other.leftLast}, rightLast {other.rightLast} {
    other.containerSize = 0;
    other.c = other.leftLast = other.rightLast = nullptr;
}
template <typename T>
DataStructure::Stack<T, T *, true>::~Stack() {
    delete[] this->c;
}
template <typename T>
DataStructure::Stack<T, T *, true> &
DataStructure::Stack<T, T *, true>::operator=(const Stack &other) {
    if(&other == this) {
        return *this;
    }
    delete[] this->c;
    this->containerSize = other.containerSize;
    this->c = reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize));
    this->leftLast = this->c;
    this->rightLast = this->c + (this->containerSize - 1);
    for(auto i {other.c}; i not_eq other.leftLast;) {
        new (this->leftLast++) valueType(*i++);
    }
    for(auto i {other.c + (this->containerSize - 1)}; i not_eq other.rightLast;) {
        new (this->rightLast--) valueType(*i--);
    }
    return *this;
}
template <typename T>
DataStructure::Stack<T, T *, true> &
DataStructure::Stack<T, T *, true>::operator=(Stack &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    delete[] this->c;
    this->containerSize = other.containerSize;
    this->c = other.c;
    this->leftLast = other.leftLast;
    this->rightLast = other.rightLast;
    other.containerSize = 0;
    other.c = other.leftLast = other.rightLast = nullptr;
    return *this;
}
template <typename T>
inline bool DataStructure::Stack<T, T *, true>::operator==(const Stack &other) const {
    if(this->frontSize() == other.frontSize() and this->backSize() == other.backSize()) {
        for(auto i {this->c}, j {other.c}; i not_eq this->leftLast;) {
            if(*i++ not_eq *j++) {
                return false;
            }
        }
        auto increment {this->containerSize - 1};
        for(auto i {this->c + increment}, j {other.c + increment}; i not_eq this->rightLast;) {
            if(*i-- not_eq *j--) {
                return false;
            }
        }
        return true;
    }
    return false;
}
template <typename T>
bool DataStructure::Stack<T, T *, true>::operator not_eq(const Stack &other) const {
    return not(*this == other);
}
template <typename T>
inline DataStructure::Stack<T, T *, true>::operator bool() const {
    return this->c not_eq this->leftLast or this->c + (this->containerSize - 1) not_eq this->rightLast;
}
template <typename T>
bool DataStructure::Stack<T, T *, true>::empty() const {
    return not this->operator bool();
}
template <typename T>
bool DataStructure::Stack<T, T *, true>::frontEmpty() const {
    return this->c == this->leftLast;
}
template <typename T>
bool DataStructure::Stack<T, T *, true>::backEmpty() const {
    return this->c + (this->containerSize - 1) == this->rightLast;
}
template <typename T>
typename DataStructure::Stack<T, T *, true>::sizeType
DataStructure::Stack<T, T *, true>::size() const {
    return this->frontSize() + this->backSize();
}
template <typename T>
inline typename DataStructure::Stack<T, T *, true>::sizeType
DataStructure::Stack<T, T *, true>::frontSize() const {
    return static_cast<sizeType>(this->leftLast - this->c);
}
template <typename T>
inline typename DataStructure::Stack<T, T *, true>::sizeType
DataStructure::Stack<T, T *, true>::backSize() const {
    return static_cast<sizeType>(this->c + this->containerSize - this->rightLast - 1);
}
template <typename T>
void DataStructure::Stack<T, T *, true>::pushFront(constReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->leftLast++) valueType(value);
}
template <typename T>
void DataStructure::Stack<T, T *, true>::pushFront(rightValueReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->leftLast++) valueType(std::move(value));
}
template <typename T>
void DataStructure::Stack<T, T *, true>::pushBack(constReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->rightLast--) valueType(value);
}
template <typename T>
void DataStructure::Stack<T, T *, true>::pushBack(rightValueReference value) {
    if(this->full()) {
        this->reallocate();
    }
    new (this->rightLast--) valueType(std::move(value));
}
template <typename T>
#ifdef POP_GET_OBJECT
typename DataStructure::Stack<T, T *, true>::valueType
#else
void
#endif
DataStructure::Stack<T, T *, true>::popFront() {
    if(this->frontEmpty()) {
        throw EmptyStack("The front stack is empty!");
    }
#ifndef POP_GET_OBJECT
    (--this->leftLast)->~valueType();
#else
    --this->leftLast;
    auto temp {std::move(static_cast<rightValueReference>(*this->leftLast))};
    this->leftLast->~valueType();
    return temp;
#endif
}
template <typename T>
#ifdef POP_GET_OBJECT
typename DataStructure::Stack<T, T *, true>::valueType
#else
void
#endif
DataStructure::Stack<T, T *, true>::popBack() {
    if(this->backEmpty()) {
        throw EmptyStack("The back stack is empty!");
    }
#ifndef POP_GET_OBJECT
    (++this->rightLast)->~valueType();
#else
    ++this->rightLast;
    auto temp {std::move(static_cast<rightValueReference>(*this->rightLast))};
    this->rightLast->~valueType();
    return temp;
#endif
}
template <typename T>
inline void DataStructure::Stack<T, T *, true>::frontClear() {
    while(--this->leftLast not_eq this->c) {
        this->leftLast->~valueType();
    }
    this->leftLast->~valueType();
}
template <typename T>
inline void DataStructure::Stack<T, T *, true>::backClear() {
    auto last {this->c + (this->containerSize - 1)};
    while(++this->rightLast not_eq last) {
        this->rightLast->~valueType();
    }
    this->rightLast->~valueType();
}
template <typename T>
void DataStructure::Stack<T, T *, true>::clear() {
    this->frontClear();
    this->backClear();
}
template <typename T>
void DataStructure::Stack<T, T *, true>::frontSwap(Stack &other) {
    if(&other == this) {
        return;
    }
    const auto thisSize {this->frontSize()};
    const auto otherSize {other.frontSize()};
    while(this->rightLast - this->c <= otherSize) {
        this->reallocate();
    }
    while(other.rightLast - other.c <= thisSize) {
        other.reallocate();
    }
    if(thisSize <= otherSize) {
        valueType backup[thisSize];
        auto cursor {this->leftLast};
        for(auto i {static_cast<differenceType>(thisSize - 1)}; i >= 0;) {
            new (&backup[i--]) valueType(std::move(static_cast<rightValueReference>(*cursor)));
            cursor--->~valueType();
        }
        this->leftLast = this->c + (otherSize - 1);
        while(other.leftLast not_eq other.c) {
            new (this->leftLast--) valueType(
                    std::move(static_cast<rightValueReference>(*--other.leftLast))
            );
            other.leftLast->~valueType();
        }
        this->leftLast = this->c + otherSize;
        for(auto i {0}; i < thisSize; ++i) {
            new (other.leftLast++) valueType(std::move(static_cast<rightValueReference>(backup[i])));
        }
        return;
    }
    valueType backup[otherSize];
    auto cursor {other.leftLast};
    for(auto i {static_cast<differenceType>(otherSize - 1)}; i >= 0;) {
        new (&backup[i--]) valueType(std::move(static_cast<rightValueReference>(*cursor)));
        cursor--->~valueType();
    }
    other.leftLast = other.c + (thisSize - 1);
    while(this->leftLast not_eq this->c) {
        new (other.leftLast--) valueType(
                std::move(static_cast<rightValueReference>(*--this->leftLast))
        );
        this->leftLast->~valueType();
    }
    other.leftLast = other.c + thisSize;
    for(auto i {0}; i < otherSize; ++i) {
        new (this->leftLast++) valueType(std::move(static_cast<rightValueReference>(backup[i])));
    }
}
template <typename T>
void DataStructure::Stack<T, T *, true>::backSwap(Stack &other) {
    if(&other == this) {
        return;
    }
    const auto thisSize {this->backSize()};
    const auto otherSize {other.backSize()};
    while(this->containerSize - (this->leftLast - this->c) - 1 <= otherSize) {
        this->reallocate();
    }
    while(other.containerSize - (other.leftLast - other.c) - 1 <= thisSize) {
        other.reallocate();
    }
    const auto thisLast {this->c + (this->containerSize - 1)};
    const auto otherLast {other.c + other.containerSize};
    if(thisSize < otherSize) {
        valueType backup[thisSize];
        for(auto i {0}; i < thisSize; ++i) {
            new (backup + i) valueType(std::move(static_cast<rightValueReference>(*this->rightLast)));
            this->rightLast++->~valueType();
        }
        this->rightLast = thisLast - (otherSize - 1);
        while(++other.rightLast not_eq otherLast) {
            new (this->rightLast++) valueType(
                    std::move(static_cast<rightValueReference>(*other.rightLast))
            );
            other.rightLast->~valueType();
        }
        this->rightLast = thisLast - otherSize;
        --other.rightLast;
        for(auto i {0}; i < thisSize; ++i) {
            new (other.rightLast--) valueType(std::move(static_cast<rightValueReference>(backup[i])));
        }
        return;
    }
    valueType backup[otherSize];
    for(auto i {0}; i < otherSize; ++i) {
        new (backup + i) valueType(std::move(static_cast<rightValueReference>(*other.rightLast)));
        other.rightLast++->~valueType();
    }
    other.rightLast = otherLast - thisSize;
    while(this->rightLast not_eq thisLast) {
        new (other.rightLast++) valueType(
                std::move(static_cast<rightValueReference>(*++this->rightLast))
        );
        this->rightLast->~valueType();
    }
    other.rightLast = otherLast - (thisSize + 1);
    for(auto i {0}; i < otherSize; ++i) {
        new (this->rightLast++) valueType(std::move(static_cast<rightValueReference>(backup[i])));
    }
}
template <typename T>
void DataStructure::Stack<T, T *, true>::swap(Stack &other) {
    using std::swap;
    swap(this->c, other.c);
    swap(this->leftLast, other.leftLast);
    swap(this->rightLast, other.rightLast);
    swap(this->containerSize, other.containerSize);
}

#ifdef OTHER_FUNCTION
template <typename T, typename Container, bool Bilateral>
void DataStructure::Stack<T, Container, Bilateral>::resize(sizeType size) {
    this->c.resize(size);
}
template <typename T, typename Container, bool Bilateral>
void DataStructure::Stack<T, Container, Bilateral>::shrinkToFit() {
    this->c.shrinkToFit();
}
template <typename T, typename Container, bool Bilateral>
typename DataStructure::Stack<T, Container, Bilateral>::sizeType
DataStructure::Stack<T, Container, Bilateral>::reserve() const {
    return this->c.reserve();
}
template <typename T, typename Container, bool Bilateral>
typename DataStructure::Stack<T, Container, Bilateral>::sizeType
DataStructure::Stack<T, Container, Bilateral>::capacity() const {
    return this->c.capacity();
}

template <typename T>
void DataStructure::Stack<T, T *, false>::resize(sizeType size) {
    this->reallocate(size);
}
template <typename T>
void DataStructure::Stack<T, T *, false>::shrinkToFit() {
    if(this->full()) {
        return;
    }
    this->containerSize = this->size();
    auto newContainer {
        reinterpret_cast<container>(::operator new (sizeof(valueType) * this->containerSize))
    };
    for(auto i {0}; i < this->containerSize; ++i) {
        new (newContainer + i) valueType(std::move(static_cast<rightValueReference>(this->c[i])));
    }
    delete[] this->c;
    this->c = newContainer;
    this->last = this->c + this->containerSize;
}
template <typename T>
typename DataStructure::Stack<T, T *, false>::sizeType
DataStructure::Stack<T, T *, false>::reserve() const {
    return this->containerSize - (this->last - this->c);
}
template <typename T>
typename DataStructure::Stack<T, T *, false>::sizeType
DataStructure::Stack<T, T *, false>::capacity() const {
    return this->containerSize;
}

template <typename T>
void DataStructure::Stack<T, T *, true>::resize(sizeType size) {
    this->reallocate(size);
}
template <typename T>
void DataStructure::Stack<T, T *, true>::shrinkToFit() {
    if(this->full()) {
        return;
    }
    auto size {this->size() + 2};
    auto newContainer {reinterpret_cast<container>(::operator new (sizeof(valueType) * size))};
    auto cursor {this->c};
    auto moveCursor {newContainer};
    while(cursor not_eq this->leftLast) {
        new (moveCursor++) valueType(std::move(static_cast<rightValueReference>(*cursor++)));
    }
    this->leftLast = moveCursor;
    moveCursor = newContainer + (size - 1);
    cursor = this->c + (this->containerSize - 1);
    while(cursor not_eq this->rightLast) {
        new (moveCursor--) valueType(std::move(static_cast<rightValueReference>(*cursor--)));
    }
    this->rightLast = moveCursor;
    delete[] this->c;
    this->c = newContainer;
    this->containerSize = size;
}
template <typename T>
typename DataStructure::Stack<T, T *, true>::sizeType
DataStructure::Stack<T, T *, true>::reserve() const {
    return this->rightLast - this->leftLast - 1;
}
template <typename T>
typename DataStructure::Stack<T, T *, true>::sizeType
DataStructure::Stack<T, T *, true>::capacity() const {
    return this->containerSize;
}
#endif

#endif //DATA_STRUCTURE_STACK_HPP
