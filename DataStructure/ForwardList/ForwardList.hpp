#ifndef DATA_STRUCTURE_FORWARD_LIST_HPP
#define DATA_STRUCTURE_FORWARD_LIST_HPP

#include "Base.hpp"
#include "Exception.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>>
    class ForwardList final {
    private:
        class OutOfRange;
        class EmptyForwardList;
        class BadIterator;
    public:
        class Iterator {
        public:
            using valueType = Node<T>;
            using reference = Node<T> &;
            using pointer = Node<T> *;
            using constPointer = const Node<T> *;
            using constReference = const Node<T> &;
            using differenceType = ptrdiff_t;
            using sizeType = size_t;
        private:
            pointer iterator;
        public:
            Iterator() = delete;
            explicit Iterator(pointer p) : iterator {p} {}
            Iterator(const Iterator &other) : iterator {other.iterator} {}
            Iterator(Iterator &&other) noexcept : iterator {other.iterator} {
                other.iterator = nullptr;
            }
            Iterator &operator=(const Iterator &other) {
                if(&other == this) {
                    return *this;
                }
                this->iterator = other.iterator;
                return *this;
            }
            Iterator &operator=(Iterator &&other) noexcept {
                if(&other == this) {
                    return *this;
                }
                this->iterator = other.iterator;
                other.iterator = nullptr;
                return *this;
            }
            T &operator*() {
                return iterator->data;
            }
            bool operator==(const Iterator &other) const {
                return this->iterator == other.iterator;
            }
            bool operator not_eq(const Iterator &other) const {
                return not(*this == other);
            }
            Iterator &operator++() {
                if(this->iterator->next == nullptr) {
                    throw BadIterator("The next iterator is a bad-iterator!");
                }
                this->iterator = this->iterator->next;
                return *this;
            }
            Iterator operator++(int) {
                if(this->iterator->next == nullptr) {
                    throw BadIterator("The next iterator is a bad-iterator!");
                }
                Iterator temp {*this};
                ++*this;
                return temp;
            }
#ifdef DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST_ITERATOR
            pointer &getIterator() {
                return this->iterator;
            }
#endif
        };
    public:
        using differenceType = ptrdiff_t;
        using sizeType = size_t;
        using valueType = T;
        using constType = const T;
        using reference = T &;
        using constReference = const T &;
        using pointer = T *;
        using constPointer = const T *;
        using constPointerConstant = const T *const;
        using rightValueReference = T &&;
        using iterator = Iterator;
        using constIterator = const Iterator;
        using iteratorReference = Iterator &;
        using constIteratorReference = const Iterator &;
        using allocator = Alloc;
    private:
        using node = Node<valueType> *;
    private:
        node first;
        node last;
    private:
        template <typename ForwardIterator>
        void init(ForwardIterator begin, ForwardIterator end);
    public:
        ForwardList();
        ForwardList(sizeType, constReference);
        explicit ForwardList(sizeType);
        ForwardList(iterator, iterator);
        ForwardList(pointer, pointer);
        ForwardList(std::initializer_list<valueType>);
        ForwardList(const ForwardList &);
        ForwardList(ForwardList &&) noexcept;
        ~ForwardList();
        ForwardList &operator=(const ForwardList &);
        ForwardList &operator=(ForwardList &&) noexcept;
        bool operator==(const ForwardList &) const;
        bool operator not_eq(const ForwardList &) const;
        bool operator<(const ForwardList &) const;
        bool operator<=(const ForwardList &) const;
        bool operator>(const ForwardList &) const;
        bool operator>=(const ForwardList &) const;
        explicit operator bool() const;
    public:
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        pop();
        void push(const valueType &);
        valueType front() const;
        iterator insertAfter(constReference, differenceType, sizeType = 1);
        void insertAfter(constReference, constIterator, sizeType = 1);
        template <typename ForwardIterator>
        void insertAfter(constIterator, ForwardIterator, ForwardIterator);
        void insertAfter(constIterator, std::initializer_list<valueType>);
        void eraseAfter(constIterator);
        iterator eraseAfter(differenceType, sizeType = 1);
        void eraseAfter(constIterator, constIterator);
        template <typename ...Args>
        void emplaceFront(Args &&...);
        template <typename ...Args>
        iterator emplaceAfter(differenceType, Args &&...);
        void clear();
        bool empty() const;
        sizeType size() const;
        iterator begin() const;
        iterator end() const;
        constIterator constBegin() const;
        constIterator constEnd() const;
#ifdef OTHER_FUNCTION
    public:
        ForwardList get(differenceType, sizeType) const;
        iterator beforeBegin() const;
        constIterator constBeforeBegin() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST
    public:
        node &getFirst() {
            return this->first;
        }
        node &getEnd() {
            return this->last;
        }
#endif
    };
}

template <typename T, typename Alloc>
class DataStructure::ForwardList<T, Alloc>::OutOfRange : public DataStructure::LogicException {
public:
    explicit OutOfRange(const char *error) : LogicException(error) {}
    explicit OutOfRange(const std::string &error) : LogicException(error) {}
};
template <typename T, typename Alloc>
class DataStructure::ForwardList<T, Alloc>::EmptyForwardList : public DataStructure::RuntimeException {
public:
    explicit EmptyForwardList(const char *error) : RuntimeException(error) {}
    explicit EmptyForwardList(const std::string &error) : RuntimeException(error) {}
};
template <typename T, typename Alloc>
class DataStructure::ForwardList<T, Alloc>::BadIterator : public DataStructure::LogicException {
public:
    explicit BadIterator(const char *error) : LogicException(error) {}
    explicit BadIterator(const std::string &error) : LogicException(error) {}
};

template <typename T, typename Alloc>
template <typename ForwardIterator>
inline void DataStructure::ForwardList<T, Alloc>::init(ForwardIterator begin, ForwardIterator end) {
    if(begin == end) {
        this->first->next = this->last;
        this->last->next = nullptr;
        return;
    }
    auto cursor {this->first->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    while(true) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
        cursor->data = *begin++;
        cursor = cursor->next;
        auto save {begin};
        ++save;
        if(save == end) {
            break;
        }
    }
    cursor->data = *begin;
    cursor->next = this->last;
    this->last->next = nullptr;
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList() :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    this->first->next = this->last;
    this->last->next = nullptr;
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(sizeType size) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    if(not(size)) {
        this->first->next = this->last;
        this->last->next = nullptr;
        return;
    }
    auto cursor {this->first->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    using t = typename removeReference<valueType>::type;
    for(auto i {1}; i < size; ++i) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
        cursor->data = t();
        cursor = cursor->next;
    }
    cursor->data = t();
    cursor->next = this->last;
    this->last->next = nullptr;
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(sizeType size, constReference value) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    if(not(size)) {
        this->first->next = this->last;
        this->last->next = nullptr;
        return;
    }
    auto cursor {this->first->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    for(auto i {1}; i < size; ++i) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
        cursor->data = value;
        cursor = cursor->next;
    }
    cursor->data = value;
    cursor->next = this->last;
    this->last->next = nullptr;
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(iterator begin, iterator end) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    this->init(begin, end);
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(pointer begin, pointer end) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    this->init(begin, end);
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(std::initializer_list<valueType> list) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    auto begin {list.begin()};
    auto end {list.end()};
    this->init(begin, end);
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(const ForwardList &other) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))} {
    auto begin {other.constBegin()};
    auto end {other.constEnd()};
    this->init(begin, end);
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::ForwardList(ForwardList &&other) noexcept :
        first {other.first}, last {other.last} {
    other.first = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
    other.last = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
    other.first->next = other.last;
    other.last->next = nullptr;
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::~ForwardList() {
    this->clear();
    Alloc::operator delete (this->first);
    Alloc::operator delete (this->last);
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc> &DataStructure::ForwardList<T, Alloc>::operator=(const ForwardList &other) {
    if(&other == this) {
        return *this;
    }
    auto begin {other.constBegin()};
    auto end {other.constEnd()};
    this->clear();
    this->init(begin, end);
    return *this;
};
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc> &
DataStructure::ForwardList<T, Alloc>::operator=(ForwardList &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->clear();
    Alloc::operator delete (this->first);
    this->first = other.first;
    other.first = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
    Alloc::operator delete (this->last);
    this->last = other.last;
    other.last = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
    other.first->next = other.last;
    other.last->next = nullptr;
    return *this;
}
template <typename T, typename Alloc>
inline bool DataStructure::ForwardList<T, Alloc>::operator==(const ForwardList &other) const {
    return other.size() == this->size() and [](const ForwardList &a, const ForwardList &b) -> bool {
        auto begin {a.constBegin()};
        for(auto &c : b) {
            if(*begin++ not_eq c) {
                return false;
            }
        }
        return true;
    }(*this, other);
}
template <typename T, typename Alloc>
bool DataStructure::ForwardList<T, Alloc>::operator not_eq(const ForwardList &other) const {
    return not(*this == other);
}
template <typename T, typename Alloc>
inline bool DataStructure::ForwardList<T, Alloc>::operator<(const ForwardList &other) const {
    auto thisSize {this->size()};
    auto otherSize {other.size()};
    if(otherSize not_eq thisSize) {
        return thisSize < otherSize;
    }
    return [](const ForwardList &a, const ForwardList &b) -> bool {
        auto endA {a.constEnd()};
        auto endB {b.constEnd()};
        for (auto itA {a.constBegin()}, itB {b.constBegin()}; itA not_eq endA and itB not_eq endB; ++itA, ++itB) {
            if(*itA not_eq *itB) {
                return *itA < *itB;
            }
        }
        return false;
    }(*this, other);
}
template <typename T, typename Alloc>
bool DataStructure::ForwardList<T, Alloc>::operator<=(const ForwardList &other) const {
    return *this == other or *this < other;
}
template <typename T, typename Alloc>
inline bool DataStructure::ForwardList<T, Alloc>::operator>(const ForwardList &other) const {
    return not(*this < other);
}
template <typename T, typename Alloc>
bool DataStructure::ForwardList<T, Alloc>::operator>=(const ForwardList &other) const {
    return *this == other or *this > other;
}
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>::operator bool() const {
    return this->size() not_eq 0;
}
template <typename T, typename Alloc>
#ifdef POP_GET_OBJECT
typename DataStructure::ForwardList<T, Alloc>::valueType
#else
void
#endif
DataStructure::ForwardList<T, Alloc>::pop() {
#ifdef POP_GET_OBJECT
    if(this->first->next == this->last) {
        throw EmptyForwardList("The Forward List is empty!");
    }
    auto returnNumber {this->first->next->data};
#endif
    this->eraseAfter(0);
#ifdef POP_GET_NUMBER
    return returnNumber;
#endif
}
template <typename T, typename Alloc>
void DataStructure::ForwardList<T, Alloc>::push(const valueType &value) {
    this->insertAfter(value, 0);
}
template <typename T, typename Alloc>
typename DataStructure::ForwardList<T, Alloc>::valueType DataStructure::ForwardList<T, Alloc>::front() const {
    if(this->first->next == this->last) {
        throw EmptyForwardList("The Forward List is empty!");
    }
    return this->first->next->data;
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::iterator
DataStructure::ForwardList<T, Alloc>::insertAfter(constReference value, differenceType position, sizeType size) {
    if(position > this->size() or position < 0) {
        throw OutOfRange("The position is out of range!");
    }
    auto cursor {this->first};
    for(auto i {0}; i < position; ++i) {
        cursor = cursor->next;
    }
    auto returnNode {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    auto newNodeCursor {returnNode};
    while(--size) {
        newNodeCursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
        newNodeCursor->data = value;
        newNodeCursor = newNodeCursor->next;
    }
    newNodeCursor->data = value;
    newNodeCursor->next = cursor->next;
    cursor->next = returnNode;
    return iterator(returnNode);
}
template <typename T, typename Alloc>
void DataStructure::ForwardList<T, Alloc>::
        insertAfter(constReference value, constIterator position, sizeType size) {
    differenceType index {1};
    auto cursorIterator {this->constBegin()};
    while(cursorIterator not_eq position) {
        ++index;
        ++cursorIterator;
    }
    this->insertAfter(value, index, size);
}
template <typename T, typename Alloc>
template <typename ForwardIterator>
inline void DataStructure::ForwardList<T, Alloc>::
        insertAfter(constIterator position, ForwardIterator begin, ForwardIterator end) {
    if(position == this->constEnd()) {
        throw OutOfRange("The position is out of range!");
    }
    if(begin == end) {
        return;
    }
    auto cursor {this->first->next};
    auto cursorIterator {this->constBegin()};
    while(cursorIterator not_eq position) {
        cursor = cursor->next;
        ++cursorIterator;
    }
    auto newNode {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    auto save {newNode};
    while(true) {
        newNode->next = reinterpret_cast<node>(Alloc::operator new (sizeof(node)));
        newNode->data = *begin++;
        newNode = newNode->next;
        auto next {begin};
        ++next;
        if(next == end) {
            break;
        }
    }
    newNode->data = *begin;
    newNode->next = cursor->next;
    cursor->next = save;
}
template <typename T, typename Alloc>
void DataStructure::ForwardList<T, Alloc>::insertAfter(constIterator it, std::initializer_list<valueType> list) {
    this->insertAfter(it, list.begin(), list.end());
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::iterator
DataStructure::ForwardList<T, Alloc>::eraseAfter(differenceType index, sizeType size) {
    if(index >= this->size() or index < 0) {
        throw OutOfRange("The index is out of range!");
    }
    auto cursor {this->first};
    for(auto i {0}; i < index; ++i) {
        cursor = cursor->next;
    }
    auto deleteNode {cursor->next};
    auto returnNode {deleteNode};
    while(size--) {
        returnNode = deleteNode->next;
        Alloc::operator delete (deleteNode);
        deleteNode = returnNode;
    }
    cursor->next = returnNode;
    return iterator(returnNode);
}
template <typename T, typename Alloc>
void DataStructure::ForwardList<T, Alloc>::eraseAfter(constIterator position) {
    if(position == this->constEnd()) {
        return;
    }
    auto cursor {this->constBegin()};
    differenceType index {0};
    while(cursor not_eq position) {
        ++index;
        ++cursor;
    }
    this->eraseAfter(index);
}
template <typename T, typename Alloc>
void DataStructure::ForwardList<T, Alloc>::eraseAfter(constIterator begin, constIterator end) {
    if(begin == this->constEnd() or begin == end) {
        return;
    }
    auto cursor {this->constBegin()};
    differenceType index {0};
    while(cursor not_eq begin) {
        ++index;
        ++cursor;
    }
    sizeType size {0};
    while(cursor not_eq end) {
        ++size;
        ++cursor;
    }
    this->eraseAfter(index, size);
}
template <typename T, typename Alloc>
template <typename ...Args>
void DataStructure::ForwardList<T, Alloc>::emplaceFront(Args &&...args) {
    auto newNode {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    newNode->next = this->first->next;
    new (&newNode->data) valueType(std::forward<Args>(args)...);
    this->first->next = newNode;
}
template <typename T, typename Alloc>
template <typename ...Args>
typename DataStructure::ForwardList<T, Alloc>::iterator
DataStructure::ForwardList<T, Alloc>::emplaceAfter(differenceType position, Args &&...args) {
    if(position == 0) {
        this->emplaceFront(std::forward<Args>(args)...);
        return iterator(this->first->next);
    }
    //return this->insertAfter(valueType(std::forward<Args>(args)...), position);
    auto cursor {this->first};
    for(auto i {0}; i < position; ++i) {
        cursor = cursor->next;
    }
    auto returnNode {reinterpret_cast<node>(Alloc::operator new (sizeof(node)))};
    new (&returnNode->data) valueType(std::forward<Args>(args)...);
    returnNode->next = cursor->next;
    cursor->next = returnNode;
    return iterator(returnNode);
}
template <typename T, typename Alloc>
inline void DataStructure::ForwardList<T, Alloc>::clear() {
    if(this->empty()) {
        return;
    }
    this->eraseAfter(this->constBegin(), this->constEnd());
}
template <typename T, typename Alloc>
inline bool DataStructure::ForwardList<T, Alloc>::empty() const {
    return this->first->next == this->last;
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::sizeType
DataStructure::ForwardList<T, Alloc>::size() const {
    sizeType size {0};
    auto cursor {this->first};
    while((cursor = cursor->next) not_eq this->last) {
        ++size;
    }
    return size;
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::iterator
DataStructure::ForwardList<T, Alloc>::begin() const {
    return iterator(this->first->next);
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::iterator
DataStructure::ForwardList<T, Alloc>::end() const {
    return iterator(this->last);
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::constIterator
DataStructure::ForwardList<T, Alloc>::constBegin() const {
    return this->begin();
}
template <typename T, typename Alloc>
inline typename DataStructure::ForwardList<T, Alloc>::constIterator
DataStructure::ForwardList<T, Alloc>::constEnd() const {
    return this->end();
}
#ifdef OTHER_FUNCTION
template <typename T, typename Alloc>
DataStructure::ForwardList<T, Alloc>
DataStructure::ForwardList<T, Alloc>::get(differenceType index, sizeType size) const {
    if(index + size >= this->size()) {
        throw OutOfRange("The last index is out of range!");
    }
    auto begin {this->constBegin()};
    while(index--) {
        ++begin;
    }
    auto end {begin};
    while(size--) {
        ++end;
    }
    return ForwardList(begin, end);
}
template <typename T, typename Alloc>
typename DataStructure::ForwardList<T, Alloc>::iterator
DataStructure::ForwardList<T, Alloc>::beforeBegin() const {
    return iterator(this->first);
}
template <typename T, typename Alloc>
typename DataStructure::ForwardList<T, Alloc>::constIterator
DataStructure::ForwardList<T, Alloc>::constBeforeBegin() const {
    return iterator(this->first);
}
#endif

#endif //DATA_STRUCTURE_FORWARD_LIST_HPP
