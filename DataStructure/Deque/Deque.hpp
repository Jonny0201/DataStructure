#ifndef DATA_STRUCTURE_DEQUE_HPP
#define DATA_STRUCTURE_DEQUE_HPP

#include "Base.hpp"

namespace DataStructure {
#ifdef __DATASTRUCTURE_USE_VECTOR_DEQUE
    template <typename T, typename Alloc = Allocator<T>>
    using Deque = Vector<T, Alloc>;
#elif defined(__DATASTRUCTURE_USE_LIST_DEQUE)
#include "List.hpp"
    template <typename T, typename Alloc = Allocator<T>>
    class Deque final : public List<T, Alloc> {
        //TODO
    };
#elif defined(__DATASTRUCTURE_SIMPIFY_DEQUE)
    template <typename T, typename Alloc = Allocator<T>>
    class Deque final {
        //TODO
    };
#else
    template <typename T, unsigned long BufferSize = 64, typename Alloc = Allocator<T>>
    class Deque final {
        friend inline void swap(Deque &a, Deque &b) {
            using std::swap;
            swap(a.bufferNumber, b.bufferNumber);
            swap(a.buffer, b.buffer);
            swap(a.first, b.first);
            swap(a.last, b.last);
        }
    private:
        class EmptyDeque;
        class OutOfRange;
    public:
        class Iterator;
    public:
        using differenceType = long;
        using sizeType = unsigned long;
        using valueType = T;
        using reference = T &;
        using constReference = const T &;
        using pointer = T *;
        using constPointer = const T *;
        using constPointerConstant = const T *const;
        using rightValueReference = T &&;
        using iterator = Iterator;
        using constIterator = const Iterator;
        using allocator = Alloc;
    private:
        enum : unsigned long {
            bufferSize = BufferSize not_eq 0 ? BufferSize :
                    (sizeof(valueType) < 512 ? 512 / sizeof(valueType) : 1)
        };
        enum {
            preserveSize = 2
        };
    private:
        sizeType bufferNumber;
        allocator *buffer;
        iterator first;
        iterator last;
    private:
        static constexpr sizeType startSize(sizeType size);
        template <typename ForwardIterator>
        void init(ForwardIterator, ForwardIterator);
        void initBuffer();
        void free() noexcept;
        void addBufferToFront(sizeType = 1, bool = true);
        void addBufferToBack(sizeType = 1);
        void removeBufferFromFirst(sizeType = 1);
        void removeBufferFromLast(sizeType = 1);
        void checkLast();
        void checkFirst();
        template <typename ForwardIterator>
        void assignAuxiliary(ForwardIterator, ForwardIterator);
        void checkLastAdd();
        void checkFirstAdd();
    public:
        Deque();
        explicit Deque(sizeType);
        Deque(sizeType, constReference);
        Deque(pointer, pointer);
        Deque(iterator, iterator);
        Deque(std::initializer_list<valueType>);
        Deque(const Deque &);
        Deque(Deque &&) noexcept;
        ~Deque();
        Deque &operator=(const Deque &);
        Deque &operator=(Deque &&) noexcept;
        reference operator[](differenceType) &;
        bool operator==(const Deque &) const;
        bool operator not_eq(const Deque &) const;
        bool operator<(const Deque &) const;
        bool operator<=(const Deque &) const;
        bool operator>(const Deque &) const;
        bool operator>=(const Deque &) const;
        explicit operator bool() const;
        Deque &operator+() const noexcept;
        Deque &operator-();
    public:
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        popBack();
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        popFront();
        void pushBack(constReference);
        void pushBack(rightValueReference);
        void pushFront(constReference);
        void pushFront(rightValueReference);
        void assign(sizeType, constReference);
        void assign(pointer, pointer);
        void assign(iterator, iterator);
        void assign(std::initializer_list<valueType>);
        valueType at(differenceType) const;
        valueType front() const;
        valueType back() const;
        iterator begin() const;
        iterator end() const;
        constIterator constBegin() const;
        constIterator constEnd() const;
        bool empty() const;
        sizeType size() const;
        void clear();
        iterator insert(constIterator, constReference, sizeType = 1);
        iterator insert(constIterator, rightValueReference, sizeType = 1);
        iterator insert(constReference, differenceType, sizeType = 1);
        iterator insert(rightValueReference, differenceType, sizeType = 1);
        iterator insert(constIterator, std::initializer_list<valueType>);
        template <typename ForwardIterator>
        iterator insert(constIterator, ForwardIterator, ForwardIterator);
        template <typename ...Args>
        iterator emplace(constIterator, Args &&...);
        template <typename ...Args>
        void emplaceFront(Args &&...);
        template <typename ...Args>
        void emplaceBack(Args &&...);
        iterator erase(constIterator, sizeType = 1);
        iterator erase(differenceType, sizeType = 1);
        iterator erase(constIterator, constIterator);
        void swap(Deque &);
#ifdef OTHER_FUNCTION
        Deque get(differenceType, sizeType) const;
        void resize(sizeType);
        void shrinkToFit();
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_DEQUE
        map *&getBuff() {
            return this->buffer;
        }
        sizeType getBuffSize() const {
            return this->bufferNumber;
        }
        iterator &getFirst() {
            return this->first;
        }
        iterator &getLast() {
            return this->last;
        }
#endif
    };
}

template <typename T, unsigned long BufferSize, typename Alloc>
class DataStructure::Deque<T, BufferSize, Alloc>::EmptyDeque : public DataStructure::RuntimeException {
public:
    explicit EmptyDeque(const char *error) : RuntimeException(error) {}
    explicit EmptyDeque(const std::string &error) : RuntimeException(error) {}
};
template <typename T, unsigned long BufferSize, typename Alloc>
class DataStructure::Deque<T, BufferSize, Alloc>::OutOfRange : public DataStructure::LogicException {
public:
    explicit OutOfRange(const char *error) : LogicException(error) {}
    explicit OutOfRange(const std::string &error) : LogicException(error) {}
};
template <typename T, unsigned long BufferSize, typename Alloc>
class DataStructure::Deque<T, BufferSize, Alloc>::Iterator {
    friend void swap(Iterator &a, Iterator &b) {
        using std::swap;
        swap(a.iterator, b.iterator);
        swap(a.node, b.node);
    }
public:
    using differenceType = long;
    using sizeType = unsigned long;
    using valueType = T;
    using reference = T &;
    using constReference = const T &;
    using pointer = T *;
    using constPointer = const T *;
    using constPointerConstant = const T *const;
    using rightValueReference = T &&;
private:
    using allocator = Alloc;
private:
    decltype(static_cast<allocator *>(nullptr)->getEnd()) iterator;
    allocator *node;
public:
    constexpr Iterator() : iterator(), node {nullptr} {}
    Iterator(decltype(static_cast<allocator *>(nullptr)->getEnd()) iterator, allocator *node) :
            iterator {iterator}, node {node} {}
    Iterator(const Iterator &other) = default;
    Iterator(Iterator &&other) noexcept : iterator {other.iterator}, node {other.node} {
        other.iterator = nullptr;
        other.node = nullptr;
    }
    Iterator &operator=(const Iterator &other) {
        if(&other == this) {
            return *this;
        }
        this->iterator = other.iterator;
        this->node = other.node;
        return *this;
    }
    Iterator &operator=(Iterator &&other) noexcept {
        if(&other == this) {
            return *this;
        }
        this->iterator = other.iterator;
        this->node = other.node;
        other.iterator = nullptr;
        other.node = nullptr;
        return *this;
    }
    ~Iterator() = default;
    reference operator[](differenceType n) {
        return *(*this + n);
    }
    reference operator*() {
        return *iterator;
    }
    pointer operator->() {
        return &**this;
    }
    differenceType operator-(const Iterator &other) const {
        return (this->node - other.node - 1) *
                static_cast<differenceType>(this->node->maxSize()) +
                (other.node->getEnd() - other.iterator) +
                (this->iterator - this->node->getFirst());
    }
    Iterator &operator++() {
        if(++this->iterator < this->node->getEnd()) {
            return *this;
        }
        ++this->node;
        this->iterator = this->node->getFirst();
        return *this;
    }
    Iterator operator++(int) {
        auto temp {*this};
        ++*this;
        return temp;
    }
    Iterator &operator--() {
        if(--this->iterator >= this->node->getFirst()) {
            return *this;
        }
        --this->node;
        this->iterator = this->node->getEnd() - 1;
        return *this;
    }
    Iterator operator--(int) {
        auto temp {*this};
        --*this;
        return temp;
    }
    Iterator &operator+=(differenceType n) {
        const auto offset {n + (this->iterator - this->node->getFirst())};
        const auto size {static_cast<differenceType>(this->node->maxSize())};
        if(offset >= 0 and offset < size) {
            this->iterator += n;
            return *this;
        }
        const auto nodeOffset {offset > 0 ? offset / size : -((-offset - 1) / size) - 1};
        this->node += nodeOffset;
        this->iterator = this->node->getFirst() + (offset - nodeOffset * size);
        return *this;
    }
    Iterator &operator-=(differenceType n) {
        return *this += -n;
    }
    Iterator operator+(differenceType n) const {
        auto temp {*this};
        return temp += n;
    }
    Iterator operator-(differenceType n) const {
        return *this + -n;
    }
    bool operator==(const Iterator &other) const {
        return this->iterator == other.iterator;
    }
    bool operator not_eq(const Iterator &other) const {
        return not(*this == other);
    }
    bool operator<(const Iterator &other) const {
        std::less<void *> l;
        return this->node == other.node ? l(this->iterator, other.iterator) : l(this->node, other.node);
    }
    bool operator<=(const Iterator &other) const {
        return *this < other or *this == other;
    }
    bool operator>(const Iterator &other) const {
        return not(*this <= other);
    }
    bool operator>=(const Iterator &other) const {
        return not(*this < other);
    }
    explicit operator bool() const {
        return this->iterator;
    }
    bool isFirst() const {
        return this->iterator == this->node->getFirst();
    }
    bool isCursor() const {
        return this->iterator == this->node->getCursor();
    }
    bool isEnd() const {
        return this->iterator == this->node->getEnd();
    }
    void destroy() {
        this->node->destroy(this->iterator);
    }
    void construct(constReference value) {
        this->node->construct(this->iterator, value);
    }
    void construct(rightValueReference value) {
        this->node->construct(this->iterator, std::move(value));
    }
    template <typename ...Args>
    void construct(Args &&...args) {
        this->node->construct(this->iterator, std::forward<Args>(args)...);
    }
};

template <typename T, unsigned long BufferSize, typename Alloc>
constexpr inline typename DataStructure::Deque<T, BufferSize, Alloc>::sizeType
DataStructure::Deque<T, BufferSize, Alloc>::startSize(sizeType size) {
    return (size + static_cast<sizeType>(preserveSize)) / bufferSize == 0 ?
            1 : (size + static_cast<sizeType>(preserveSize)) / bufferSize + (
                    (size + static_cast<sizeType>(preserveSize)) % bufferSize == 0 ? 0 : 1
                    );
}
template <typename T, unsigned long BufferSize, typename Alloc>
template <typename ForwardIterator>
inline void DataStructure::Deque<T, BufferSize, Alloc>::
        init(ForwardIterator begin, ForwardIterator end) {
    this->initBuffer();
    if(begin == end) {
        return;
    }
    while(begin not_eq end) {
        if(this->last.isEnd()) {
            ++this->last;
        }
        this->last.construct(std::move(*begin++));
    }
    this->checkLastAdd();
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::initBuffer() {
    if(this->bufferNumber > 1) {
        for(auto i {1}; i < this->bufferNumber; ++i) {
            this->buffer[i].allocate(bufferSize);
        }
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::free() noexcept {
    delete[] this->buffer;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::addBufferToBack(sizeType size) {
    if(not size) {
        return;
    }
    auto newBufferNumber {this->bufferNumber + size};
    auto newBuffer {new allocator[newBufferNumber]()};
    auto difference {this->first - iterator(this->buffer->getFirst(), this->buffer)};
    auto oldSize {static_cast<differenceType>(this->size())};
    for(auto i {0}; i < this->bufferNumber; ++i) {
        newBuffer[i] = std::move(static_cast<allocator &&>(this->buffer[i]));
    }
    for(auto i {this->bufferNumber}; i < newBufferNumber; ++i) {
        newBuffer[i].allocate(bufferSize);
    }
    this->free();
    this->buffer = newBuffer;
    this->bufferNumber += size;
    this->first = iterator(newBuffer->getFirst() + difference, newBuffer);
    this->last = this->first + oldSize + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::addBufferToFront(sizeType size, bool isPush) {
    if(not size) {
        return;
    }
    auto newBuffer {new allocator[this->bufferNumber + size]()};
    auto difference {this->first - iterator(this->buffer->getFirst(), this->buffer)};
    const auto oldSize {this->size()};
    for(auto i {static_cast<differenceType>(size)},
            j {static_cast<differenceType>(0)}; j < this->bufferNumber; ++i, ++j) {
        newBuffer[i] = std::move(static_cast<allocator &&>(this->buffer[j]));
    }
    this->free();
    this->buffer = newBuffer;
    this->bufferNumber += size;
    for(auto i {0}; i < size;) {
        this->buffer[i++].allocate(bufferSize);
    }
    if(isPush) {
        auto first {static_cast<differenceType>(size - 1)};
        this->first = iterator(this->buffer[first].getEnd() - 1, this->buffer + first);
    }else {
        this->first = iterator(this->buffer[size].getFirst() + difference, this->buffer + size);
    }
    this->last = this->first + oldSize + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::removeBufferFromFirst(sizeType size) {
    if(not size) {
        return;
    }
    const auto oldSize {this->size()};
    const auto newBufferNumber {this->bufferNumber - size};
    const auto difference {this->first - iterator(this->buffer[size].getFirst(), this->buffer + size)};
    auto newBuffer {new allocator[newBufferNumber]()};
    for(auto i {0}; i < newBufferNumber; ++i) {
        newBuffer[i] = std::move(static_cast<allocator &&>(this->buffer[i + size]));
    }
    this->free();
    this->buffer = newBuffer;
    this->bufferNumber = newBufferNumber;
    this->first = iterator(newBuffer->getFirst() + difference, newBuffer);
    this->last = this->first + oldSize + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::removeBufferFromLast(sizeType size) {
    if(not size) {
        return;
    }
    const auto newBufferNumber {this->bufferNumber - size};
    auto newBuffer {new allocator[newBufferNumber]()};
    const auto difference {this->first - iterator(this->buffer->getFirst(), this->buffer)};
    const auto oldSize {this->size()};
    for(auto i {0}; i < newBufferNumber; ++i) {
        newBuffer[i] = std::move(static_cast<allocator &&>(this->buffer[i]));
    }
    this->free();
    this->buffer = newBuffer;
    this->bufferNumber = newBufferNumber;
    this->first = iterator(newBuffer->getFirst() + difference, this->buffer);
    this->last = this->first + oldSize + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::checkFirst() {
    if(this->first - 1 == iterator(this->buffer[1].getFirst(), this->buffer + 1)) {
        this->removeBufferFromFirst();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::checkLast() {
    const auto afterLastNode {static_cast<differenceType>(this->bufferNumber - 2)};
    if(this->last + 1 == iterator(
            this->buffer[afterLastNode].getEnd() - 1, this->buffer + afterLastNode)
    ) {
        this->removeBufferFromLast();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::checkLastAdd() {
    if(this->last.isEnd()) {
        auto last {this->buffer + (this->bufferNumber - 1)};
        if(this->last not_eq iterator(last->getEnd(), last)) {
            ++this->last;
            return;
        }
        this->addBufferToBack();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::checkFirstAdd() {
    if(this->first.isFirst()) {
        if(this->first not_eq iterator(this->buffer->getFirst(), this->buffer)) {
            --this->first;
            return;
        }
        this->addBufferToFront();
        ++this->last;
        return;
    }
    --this->first;
}
template <typename T, unsigned long BufferSize, typename Alloc>
template <typename ForwardIterator>
inline void DataStructure::Deque<T, BufferSize, Alloc>::assignAuxiliary(
        ForwardIterator begin, ForwardIterator end
) {
    const auto size {end - begin};
    if(Deque::startSize(size) - this->bufferNumber) {
        this->free();
        this->bufferNumber = Deque::startSize(size);
        this->buffer = new allocator[this->bufferNumber]();
        this->initBuffer();
        this->first = iterator(this->buffer->allocate(bufferSize), this->buffer);
        this->last = this->first + 1;
        while(begin not_eq end) {
            this->pushBack(*begin++);
        }
        return;
    }
    const auto firstNext {this->first + 1};
    while(firstNext not_eq this->last) {
        --this->last;
        this->last.destroy();
    }
    while(begin not_eq end) {
        this->last.construct(*begin++);
        this->checkLastAdd();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque() : bufferNumber {Deque::startSize(0)},
        buffer {new allocator[bufferNumber]()},
        first {iterator(this->buffer->allocate(bufferSize), this->buffer)},
        last {this->first + 1} {}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(sizeType size, constReference value) :
        bufferNumber {Deque::startSize(size)}, buffer {new allocator[bufferNumber]()},
        first {iterator(this->buffer->allocate(bufferSize), this->buffer)},
        last {this->first + 1} {
    if(not size) {
        return;
    }
    this->initBuffer();
    while(size--) {
        this->last.construct(value);
        this->checkLastAdd();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(sizeType size) : Deque(size, valueType()) {}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(pointer begin, pointer end) :
        bufferNumber {Deque::startSize(end - begin)}, buffer {new allocator[bufferNumber]()},
        first {iterator(this->buffer->allocate(bufferSize), this->buffer)},
        last {this->first + 1} {
    this->init(begin, end);
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(iterator begin, iterator end) :
        bufferNumber {Deque::startSize(end - begin)}, buffer {new allocator[bufferNumber]()},
        first {iterator(this->buffer->allocate(bufferSize), this->buffer)},
        last {this->first + 1} {
    this->init(begin, end);
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(std::initializer_list<valueType> list) :
        bufferNumber {Deque::startSize(list.end() - list.begin())},
        buffer {new allocator[bufferNumber]()},
        first {iterator(this->buffer->allocate(bufferSize), this->buffer)},
        last {this->first + 1} {
    this->init(list.begin(), list.end());
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(const Deque &other) :
        bufferNumber {other.bufferNumber}, buffer {new allocator[bufferNumber]()},
        first {iterator(this->buffer->allocate(bufferSize), this->buffer)},
        last {this->first + 1} {
    this->init(other.constBegin(), other.constEnd());
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::Deque(Deque &&other) noexcept :
        bufferNumber(std::move(other.bufferNumber)), buffer {std::move(other.buffer)},
        first {std::move(other.first)}, last {std::move(other.last)} {
    other.buffer = nullptr;
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::~Deque() {
    delete[] this->buffer;
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc> &
DataStructure::Deque<T, BufferSize, Alloc>::operator=(const Deque &other) {
    if(&other == this) {
        return *this;
    }
    this->bufferNumber = other.bufferNumber;
    this->free();
    this->buffer = new allocator[this->bufferNumber]();
    this->first = iterator(this->buffer->allocate(bufferSize), this->buffer);
    this->init(other.constBegin(), other.constEnd());
    return *this;
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc> &
DataStructure::Deque<T, BufferSize, Alloc>::operator=(Deque &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->bufferNumber = std::move(other.bufferNumber);
    this->free();
    this->buffer = std::move(other.buffer);
    this->first = std::move(other.first);
    this->last = std::move(other.last);
    other.buffer = nullptr;
    return *this;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline typename DataStructure::Deque<T, BufferSize, Alloc>::reference
DataStructure::Deque<T, BufferSize, Alloc>::operator[](differenceType n) & {
    return this->first[++n];
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline bool DataStructure::Deque<T, BufferSize, Alloc>::operator==(const Deque &other) const {
    return this->size() == other.size() and [](const Deque &a, const Deque &b) -> bool {
        auto begin {b.constBegin()};
        for(auto &c : a) {
            if(c not_eq *begin++) {
                return false;
            }
        }
        return true;
    }(*this, other);
}
template <typename T, unsigned long BufferSize, typename Alloc>
bool DataStructure::Deque<T, BufferSize, Alloc>::operator not_eq(const Deque &other) const {
    return not(*this == other);
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline bool DataStructure::Deque<T, BufferSize, Alloc>::operator<(const Deque &other) const {
    auto thisSize {this->size()};
    auto otherSize {other.size()};
    return thisSize not_eq otherSize ? thisSize < otherSize :
            [](const Deque &a, const Deque &b) -> bool {
        auto begin {b.constBegin()};
        for(auto &c : a) {
            if(c not_eq *begin) {
                return c < *begin;
            }
        }
        return false;
    }(*this, other);
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline bool DataStructure::Deque<T, BufferSize, Alloc>::operator<=(const Deque &other) const {
    return *this < other or *this == other;
}
template <typename T, unsigned long BufferSize, typename Alloc>
bool DataStructure::Deque<T, BufferSize, Alloc>::operator>(const Deque &other) const {
    return not(*this <= other);
}
template <typename T, unsigned long BufferSize, typename Alloc>
bool DataStructure::Deque<T, BufferSize, Alloc>::operator>=(const Deque &other) const {
    return not(*this < other);
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline DataStructure::Deque<T, BufferSize, Alloc>::operator bool() const {
    return this->empty();
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline DataStructure::Deque<T, BufferSize, Alloc> &
DataStructure::Deque<T, BufferSize, Alloc>::operator+() const noexcept {
    return *this;
}
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc> &
DataStructure::Deque<T, BufferSize, Alloc>::operator-() {
    for(auto &c : *this) {
        c = -c;
    }
    return *this;
}
template <typename T, unsigned long BufferSize, typename Alloc>
#ifdef POP_GET_OBJECT
inline typename DataStructure::Deque<T, BufferSize, Alloc>::valueType
#else
inline void
#endif
DataStructure::Deque<T, BufferSize, Alloc>::popBack() {
    if(not this->size()) {
        throw EmptyDeque("The deque is empty!");
    }
    --this->last;
#ifdef POP_GET_OBJECT
    auto object {*this->last};
#endif
    this->last.destroy();
    this->checkLast();
#ifdef POP_GET_OBJECT
    return object;
#endif
}
template <typename T, unsigned long BufferSize, typename Alloc>
#ifdef POP_GET_OBJECT
inline typename DataStructure::Deque<T, BufferSize, Alloc>::valueType
#else
inline void
#endif
DataStructure::Deque<T, BufferSize, Alloc>::popFront() {
    if(not this->size()) {
        throw EmptyDeque("The deque is empty!");
    }
#ifdef POP_GET_OBJECT
    auto object {*(this->first + 1)};
#endif
    ++this->first;
    this->first.destroy();
    this->checkFirst();
#ifdef POP_GET_OBJECT
    return object;
#endif
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::pushBack(constReference value) {
    this->last.construct(value);
    this->checkLastAdd();
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::pushBack(rightValueReference value) {
    this->last.construct(std::move(value));
    this->checkLastAdd();
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::pushFront(constReference value) {
    this->first.construct(value);
    --this->first;
    this->checkFirstAdd();
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::pushFront(rightValueReference value) {
    this->first.construct(std::move(value));
    --this->first;
    this->checkFirstAdd();
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::assign(sizeType size, constReference value) {
    if(Deque::startSize(size) - this->bufferNumber) {
        this->free();
        this->bufferNumber = Deque::startSize(size);
        this->buffer = new allocator[this->bufferNumber]();
        this->initBuffer();
        this->first = iterator(this->buffer->allocate(bufferSize), this->buffer);
        this->last = this->first + 1;
        while(size--) {
            this->pushBack(value);
        }
        return;
    }
    const auto firstNext {this->first + 1};
    while(firstNext not_eq this->last) {
        --this->last;
        this->last.destroy();
    }
    while(size--) {
        this->last.construct(value);
        this->checkLastAdd();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::assign(pointer begin, pointer end) {
    this->assignAuxiliary(begin, end);
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::assign(iterator begin, iterator end) {
    this->assignAuxiliary(begin, end);
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::assign(std::initializer_list<valueType> list) {
    this->assignAuxiliary(list.begin(), list.end());
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::valueType
DataStructure::Deque<T, BufferSize, Alloc>::at(differenceType index) const {
    return this->first[++index];
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::valueType
DataStructure::Deque<T, BufferSize, Alloc>::front() const {
    if(not this->size()) {
        throw EmptyDeque("The deque is empty!");
    }
    return *(this->first + 1);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::valueType
DataStructure::Deque<T, BufferSize, Alloc>::back() const {
    if(not this->size()) {
        throw EmptyDeque("The deque is empty!");
    }
    return *(this->last - 1);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::begin() const {
    return this->first + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::end() const {
    return this->last;
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::constIterator
DataStructure::Deque<T, BufferSize, Alloc>::constBegin() const {
    return this->first + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::constIterator
DataStructure::Deque<T, BufferSize, Alloc>::constEnd() const {
    return this->last;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline bool DataStructure::Deque<T, BufferSize, Alloc>::empty() const {
    return this->first + 1 == this->last;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline typename DataStructure::Deque<T, BufferSize, Alloc>::sizeType
DataStructure::Deque<T, BufferSize, Alloc>::size() const {
    return static_cast<sizeType>(this->last - this->first - 1);
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::clear() {
    this->free();
    this->buffer = new allocator();
    this->first = iterator(this->buffer->allocate(bufferSize) + 1, this->buffer);
    this->last = this->first + 1;
}
template <typename T, unsigned long BufferSize, typename Alloc>
inline void DataStructure::Deque<T, BufferSize, Alloc>::swap(Deque &other) {
    using std::swap;
    swap(this->bufferNumber, other.bufferNumber);
    swap(this->buffer, other.buffer);
    swap(this->first, other.first);
    swap(this->last, other.last);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::
        insert(constReference value, differenceType index, sizeType size) {
    if(not size) {
        return this->first + index + 1;
    }
    auto oldSize {this->size()};
    if(index > oldSize) {
        throw OutOfRange("The index is out of range!");
    }
    if(not index) {
        while(size--) {
            this->pushFront(value);
        }
        return this->last - size;
    }else if(index == oldSize) {
        while(size--) {
            this->pushBack(value);
        }
        return this->first + 1;
    }
    auto increment {static_cast<differenceType>(size * 2)};
    if(this->last - this->first - index - 1 <= index) {
        const auto remain {iterator(this->buffer[this->bufferNumber - 1].getEnd() - 1, this->buffer + (
                this->bufferNumber - 1)) - this->last};
        this->addBufferToBack(remain < size ? (size - remain) / bufferSize + (
                (size - remain) % bufferSize == 0 ? 0 : 1
        ) : 0);
        auto insertPosition {this->begin() + index};
        auto cursor {this->last};
        auto moveCursor {this->last - size};
        while(moveCursor >= insertPosition) {
            for(auto i {0}; i < size; ++i) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor++.destroy();
                if(cursor.isEnd()) {
                    ++cursor;
                }
            }
            cursor -= increment;
            moveCursor -= increment;
        }
        const auto difference {size - (cursor - insertPosition)};
        if(difference) {
            cursor += difference;
            moveCursor = insertPosition;
            auto remain {size - difference};
            while(remain--) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor++.destroy();
                if(cursor.isEnd()) {
                    ++cursor;
                }
            }
        }
        for(auto i {0}; i < size; ++i) {
            insertPosition.construct(value);
            if(insertPosition.isEnd()) {
                ++insertPosition;
            }
        }
        this->last += size;
    }else {
        auto remain {this->first - iterator(this->buffer->getFirst(), this->buffer)};
        this->addBufferToFront(remain < size ? (size - remain) / bufferSize + (
                (size - remain) % bufferSize == 0 ? 0 : 1
        ) : 0, false);
        auto insertPosition {this->first + index};
        auto cursor {this->first};
        auto moveCursor {this->first + size};
        while(moveCursor <= insertPosition) {
            for(auto i {0}; i < size; ++i) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor--.destroy();
                cursor -= 2;
            }
            cursor += increment;
            moveCursor += increment;
        }
        if(cursor < insertPosition) {
            auto difference {insertPosition - cursor};
            cursor -= size - difference;
            moveCursor = insertPosition;
            while(difference--) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor--.destroy();
                cursor -= 2;
            }
        }
        insertPosition -= size - 1;
        for(auto i {0}; i < size; ++i) {
            insertPosition.construct(value);
            if(insertPosition.isEnd()) {
                ++insertPosition;
            }
        }
        this->first -= size;
    }
    return this->first + (index + 1);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::
        insert(rightValueReference value, differenceType index, sizeType size) {
    if(not size) {
        return this->first + index + 1;
    }
    auto oldSize {this->size()};
    if(index > oldSize) {
        throw OutOfRange("The index is out of range!");
    }
    if(not index) {
        while(--size) {
            this->pushFront(value);
        }
        this->pushFront(std::move(value));
        return this->last - size;
    }else if(index == oldSize) {
        while(--size) {
            this->pushBack(value);
        }
        this->pushBack(std::move(value));
        return this->first + 1;
    }
    const auto increment {static_cast<differenceType>(size * 2)};
    if(this->last - this->first - index - 1 <= index) {
        const auto remain {iterator(this->buffer[this->bufferNumber - 1].getEnd() - 1, this->buffer + (
                this->bufferNumber - 1)) - this->last};
        this->addBufferToBack(remain < size ? (size - remain) / bufferSize + (
                (size - remain) % bufferSize == 0 ? 0 : 1
        ) : 0);
        auto insertPosition {this->begin() + index};
        auto cursor {this->last};
        auto moveCursor {this->last - size};
        while(moveCursor >= insertPosition) {
            for(auto i {0}; i < size; ++i) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor++.destroy();
                if(cursor.isEnd()) {
                    ++cursor;
                }
            }
            cursor -= increment;
            moveCursor -= increment;
        }
        const auto difference {size - (cursor - insertPosition)};
        if(difference) {
            cursor += difference;
            moveCursor = insertPosition;
            auto remain {size - difference};
            while(remain--) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor++.destroy();
                if(cursor.isEnd()) {
                    ++cursor;
                }
            }
        }
        for(auto i {1}; i < size; ++i) {
            insertPosition.construct(value);
            if(insertPosition.isEnd()) {
                ++insertPosition;
            }
        }
        insertPosition.construct(std::move(value));
        this->last += size;
    }else {
        auto remain {this->first - iterator(this->buffer->getFirst(), this->buffer)};
        this->addBufferToFront(remain < size ? (size - remain) / bufferSize + (
                (size - remain) % bufferSize == 0 ? 0 : 1
        ) : 0, false);
        auto insertPosition {this->first + index};
        auto cursor {this->first};
        auto moveCursor {this->first + size};
        while(moveCursor <= insertPosition) {
            for(auto i {0}; i < size; ++i) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor--.destroy();
                cursor -= 2;
            }
            cursor += increment;
            moveCursor += increment;
        }
        if(cursor < insertPosition) {
            auto difference {insertPosition - cursor};
            cursor -= size - difference;
            moveCursor = insertPosition;
            while(difference--) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor--.destroy();
                cursor -= 2;
            }
        }
        insertPosition -= size - 1;
        for(auto i {1}; i < size; ++i) {
            insertPosition.construct(value);
            if(insertPosition.isEnd()) {
                ++insertPosition;
            }
        }
        insertPosition.construct(std::move(value));
        this->first -= size;
    }
    return this->first + (index + 1);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::
        insert(constIterator position, constReference value, sizeType size) {
    return this->insert(value, [](constIterator &a, constIterator &b) -> differenceType {
        return b - a;
    }(this->first, position), size);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::
        insert(constIterator position, rightValueReference value, sizeType size) {
    return this->insert(
            std::move(value), [](constIterator &a, constIterator &b) -> differenceType {
        return b - a;
            }(this->first, position), size
    );
}
template <typename T, unsigned long BufferSize, typename Alloc>
template <typename ForwardIterator>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::
        insert(constIterator position, ForwardIterator begin, ForwardIterator end) {
    if(begin == end) {
        return position;
    }
    auto oldSize {this->size()};
    auto size {[=]() mutable -> differenceType {
        differenceType size {0};
        while(begin not_eq end) {
            ++size;
            ++begin;
        }
        return size;
    }()};
    auto first {this->begin()};
    auto index {position - first};
    if(index > oldSize) {
        throw OutOfRange("The index is out of range!");
    }
    if(position == first) {
        while(size--) {
            this->pushFront(std::move(static_cast<rightValueReference>(*begin++)));
        }
        return this->last - size;
    }else if(index == oldSize) {
        while(size--) {
            this->pushBack(std::move(static_cast<rightValueReference>(*begin++)));
        }
        return this->first + 1;
    }
    auto increment {static_cast<differenceType>(size * 2)};
    if(this->last - this->first - index - 1 <= index) {
        const auto remain {iterator(this->buffer[this->bufferNumber - 1].getEnd() - 1, this->buffer + (
                this->bufferNumber - 1)) - this->last};
        this->addBufferToBack(remain < size ? (size - remain) / bufferSize + (
                (size - remain) % bufferSize == 0 ? 0 : 1
        ) : 0);
        auto insertPosition {this->begin() + index};
        auto cursor {this->last};
        auto moveCursor {this->last - size};
        while(moveCursor >= insertPosition) {
            for(auto i {0}; i < size; ++i) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor++.destroy();
                if(cursor.isEnd()) {
                    ++cursor;
                }
            }
            cursor -= increment;
            moveCursor -= increment;
        }
        const auto difference {size - (cursor - insertPosition)};
        if(difference) {
            cursor += difference;
            moveCursor = insertPosition;
            auto remain {size - difference};
            while(remain--) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor++.destroy();
                if(cursor.isEnd()) {
                    ++cursor;
                }
            }
        }
        for(auto i {1}; i < size; ++i) {
            insertPosition.construct(*begin++);
            if(insertPosition.isEnd()) {
                ++insertPosition;
            }
        }
        this->last += size;
    }else {
        auto remain {this->first - iterator(this->buffer->getFirst(), this->buffer)};
        this->addBufferToFront(remain < size ? (size - remain) / bufferSize + (
                (size - remain) % bufferSize == 0 ? 0 : 1
        ) : 0, false);
        auto insertPosition {this->first + index};
        auto cursor {this->first};
        auto moveCursor {this->first + size};
        while(moveCursor <= insertPosition) {
            for(auto i {0}; i < size; ++i) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor--.destroy();
                cursor -= 2;
            }
            cursor += increment;
            moveCursor += increment;
        }
        if(cursor < insertPosition) {
            auto difference {insertPosition - cursor};
            cursor -= size - difference;
            moveCursor = insertPosition;
            while(difference--) {
                cursor.construct(std::move(static_cast<rightValueReference>(*moveCursor)));
                moveCursor--.destroy();
                cursor -= 2;
            }
        }
        insertPosition -= size - 1;
        for(auto i {1}; i < size; ++i) {
            insertPosition.construct(*begin++);
            if(insertPosition.isEnd()) {
                ++insertPosition;
            }
        }
        this->first -= size;
    }
    return this->first + index;
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::
        insert(constIterator position, std::initializer_list<valueType> list) {
    return this->insert(position, list.begin(), list.end());
}
template <typename T, unsigned long BufferSize, typename Alloc>
template <typename ...Args>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::emplace(constIterator position, Args &&...args) {
    return this->insert(position, valueType(std::forward<Args>(args)...));
}
template <typename T, unsigned long BufferSize, typename Alloc>
template <typename ...Args>
void DataStructure::Deque<T, BufferSize, Alloc>::emplaceBack(Args &&...args) {
    this->pushBack(valueType(std::forward<Args>(args)...));
}
template <typename T, unsigned long BufferSize, typename Alloc>
template <typename ...Args>
void DataStructure::Deque<T, BufferSize, Alloc>::emplaceFront(Args &&...args) {
    this->pushFront(valueType(std::forward<Args>(args)...));
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::erase(differenceType index, sizeType size) {
    if(not size) {
        return this->begin() + index;
    }
    const auto oldSize {this->size()};
    if(index >= oldSize or index < 0 or index + size > oldSize) {
        throw OutOfRange("The index or size is out of size!");
    }
    const long removeNumber {(
                this->first - iterator(this->buffer->getFirst(), this->buffer)
        ) / static_cast<long>(bufferSize)
    };
    if(oldSize == index) {
        while(size--) {
            this->popBack();
        }
        return this->last - 1;
    }else if(not index) {
        if(size == oldSize) {
            this->clear();
            return this->last;
        }
        while(size--) {
            this->popFront();
        }
        return this->first + 1;
    }
    if(oldSize - index - size <= index) {
        auto cursor {this->first + (index + size + 1)};
        auto erasePosition {this->begin() + index};
        while(cursor not_eq this->last) {
            erasePosition.destroy();
            erasePosition.construct(std::move(static_cast<rightValueReference>(*cursor)));
            cursor++.destroy();
            if(erasePosition.isEnd()) {
                ++erasePosition;
            }
        }
        while(erasePosition not_eq --this->last) {
            this->last.destroy();
        }
        this->last.destroy();
        if(removeNumber) {
            this->removeBufferFromLast(static_cast<sizeType>(removeNumber));
        }
    }else {
        auto cursor {this->first + (index + size)};
        while(cursor - this->first not_eq size) {
            cursor.destroy();
            cursor.construct(static_cast<rightValueReference>(*(cursor - size)));
            cursor -= 2;
        }
        while(cursor not_eq ++this->first) {
            this->first.destroy();
        }
        this->first.destroy();
        if(removeNumber) {
            this->removeBufferFromFirst(static_cast<sizeType>(removeNumber));
        }
    }
    return this->first + (index + 1);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::erase(constIterator position, sizeType size) {
    return this->erase(position - static_cast<constIterator>(this->first), size);
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::iterator
DataStructure::Deque<T, BufferSize, Alloc>::erase(constIterator begin, Deque::constIterator end) {
    return this->erase(begin - static_cast<constIterator>(this->first), end - begin);
}
#ifdef OTHER_FUNCTION
template <typename T, unsigned long BufferSize, typename Alloc>
DataStructure::Deque<T, BufferSize, Alloc>
DataStructure::Deque<T, BufferSize, Alloc>::get(differenceType index, sizeType size) const {
    return Deque(this->begin() + index, this->begin() + index + size);
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::resize(sizeType size) {
    if(size < this->buffer->maxSize()) {
        return;
    }
    for(auto i {0}; i < this->bufferNumber; ++i) {
        this->buffer[i].resize(size);
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
void DataStructure::Deque<T, BufferSize, Alloc>::shrinkToFit() {
    for(auto i {0}; i < this->bufferNumber; ++i) {
        this->buffer[i].shrinkToFit();
    }
}
template <typename T, unsigned long BufferSize, typename Alloc>
typename DataStructure::Deque<T, BufferSize, Alloc>::sizeType
DataStructure::Deque<T, BufferSize, Alloc>::capacity() const {
    return iterator(
            this->buffer[this->bufferNumber - 1].getEnd(), this->buffer + (this->bufferNumber - 1)
            ) - iterator(this->buffer->getFirst(), this->buffer);
}
#endif
#endif

#endif //DATA_STRUCTURE_DEQUE_HPP
