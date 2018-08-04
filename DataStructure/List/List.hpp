#ifndef DATA_STRUCTURE_LIST_HPP
#define DATA_STRUCTURE_LIST_HPP

#include "Base.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>>
    class List final {
        friend void swap(List<T, Alloc> &a, List<T, Alloc> &b) {
            using std::swap;
            swap(a.first, b.first);
            swap(a.last, b.last);
        }
    private:
        template <typename Type>
        struct Node {
            struct Node *next;
            struct Node *previous;
            Type data;
        };
    private:
        class OutOfRange;
        class EmptyList;
    public:
        class Iterator final : BidirectionalIterator {
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
            explicit Iterator(pointer iterator) : iterator {iterator} {}
            Iterator(const Iterator &other) : iterator {other.iterator} {}
            Iterator(Iterator &&other) noexcept : iterator {other.iterator} {
                other.iterator = nullptr;
            }
            ~Iterator() {
                this->iterator = nullptr;
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
                return this->iterator->data;
            }
            const T &operator*() const {
                return this->iterator->data;
            }
            T *operator->() {
                return &this->iterator->data;
            }
            const T *operator->() const {
                return &this->iterator->data;
            }
            bool operator==(const Iterator &other) const {
                return this->iterator == other.iterator;
            }
            bool operator not_eq(const Iterator &other) const {
                return not(*this == other);
            }
            Iterator &operator++() {
                this->iterator = this->iterator->next;
                return *this;
            }
            Iterator operator++(int) {
                Iterator temp {*this};
                ++*this;
                return temp;
            }
            Iterator &operator--() {
                this->iterator = this->iterator->previous;
                return *this;
            }
            Iterator operator--(int) {
                Iterator temp {*this};
                --*this;
                return temp;
            }
#ifdef DEBUG_DATA_STRUCTURE_FOR_LIST_ITERATOR
            pointer &getIterator() {
                return this->iterator;
            }
#endif
        };
    public:
        using differenceType = long;
        using sizeType = unsigned long;
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
        using node = Node<T> *;
    private:
        node first;
        node last;
    private:
        template <typename ForwardIterator>
        void init(ForwardIterator, ForwardIterator);
        template <typename ForwardIterator>
        void assignGeneric(ForwardIterator, ForwardIterator);
        differenceType getDifference(constIterator);
    public:
        List();
        List(sizeType, constReference);
        explicit List(sizeType);
        List(iterator, iterator);
        List(pointer, pointer);
        List(std::initializer_list<valueType>);
        List(const List &);
        List(List &&) noexcept;
        ~List();
        List &operator=(const List &);
        List &operator=(List &&) noexcept;
        List &operator=(std::initializer_list<valueType>);
        bool operator==(const List &) const;
        bool operator not_eq(const List &) const;
        bool operator<(const List &) const;
        bool operator<=(const List &) const;
        bool operator>(const List &) const;
        bool operator>=(const List &) const;
        explicit operator bool() const;
    public:
        void assign(sizeType, constReference);
        void assign(iterator, iterator);
        void assign(pointer, pointer);
        void assign(std::initializer_list<valueType>);
        valueType front() const;
        valueType back() const;
        bool empty() const;
        sizeType size() const;
        iterator begin() const;
        iterator end() const;
        constIterator constBegin() const;
        constIterator constEnd() const;
        void clear();
        void pushBack(constReference);
        void pushBack(rightValueReference);
        void popBack();
        void pushFront(constReference);
        void pushFront(rightValueReference);
        void popFront();
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
#ifdef OTHER_FUNCTION
    public:
        List get(differenceType, sizeType) const;
        iterator beforeBegin() const;
        constIterator beforeConstBegin() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_LIST
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
class DataStructure::List<T, Alloc>::OutOfRange : public DataStructure::LogicException {
public:
    explicit OutOfRange(const char *error) : LogicException(error) {}
    explicit OutOfRange(const std::string &error) : LogicException(error) {}
};
template <typename T, typename Alloc>
class DataStructure::List<T, Alloc>::EmptyList : public DataStructure::RuntimeException {
public:
    explicit EmptyList(const char *error) : RuntimeException(error) {}
    explicit EmptyList(const std::string &error) : RuntimeException(error) {}
};

template <typename T, typename Alloc>
template <typename ForwardIterator>
inline void DataStructure::List<T, Alloc>::init(ForwardIterator begin, ForwardIterator end) {
    if(begin == end) {
        this->first->next = this->first->previous = this->last;
        this->last->previous = this->last->next = this->first;
        return;
    }
    this->first->previous = this->last;
    this->last->next = this->first;
    auto cursor {this->first->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))};
    while(true) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
        cursor->next->previous = cursor;
        cursor->data = *begin++;
        cursor = cursor->next;
        auto save {begin};
        ++save;
        if(save == end) {
            break;
        }
    }
    cursor->next = this->last;
    cursor->data = *begin;
    this->last->previous = cursor;
}
template <typename T, typename Alloc>
inline typename DataStructure::List<T, Alloc>::differenceType
DataStructure::List<T, Alloc>::getDifference(constIterator position) {
    return [&]() -> differenceType {
        auto begin {this->constBegin()};
        differenceType difference {0};
        while(position not_eq begin) {
            ++begin;
            ++difference;
        }
        return difference;
    }();
}
template <typename T, typename Alloc>
template <typename ForwardIterator>
inline void DataStructure::List<T, Alloc>::
        assignGeneric(ForwardIterator begin, ForwardIterator end) {
    auto cursor {this->first->next};
    while(cursor not_eq this->last and begin not_eq end) {
        cursor->data = *begin++;
        cursor = cursor->next;
    }
    if(cursor not_eq this->last) {
        cursor->previous->next = this->last;
        this->last->previous = cursor->previous;
        while(true) {
            auto next {cursor->next};
            Alloc::operator delete (cursor);
            cursor = next;
            if(cursor == this->last) {
                return;
            }
        }
    }
    if(begin == end) {
        return;
    }
    if(cursor == this->last) {
        cursor = cursor->previous;
    }
    while(begin not_eq end) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
        cursor->next->previous = cursor;
        cursor = cursor->next;
        cursor->data = *begin++;
    }
    cursor->next = this->last;
    this->last->previous = cursor;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List() :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))} {
    this->first->next = this->first->previous = this->last;
    this->last->next = this->last->previous = this->first;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(sizeType size, constReference value) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))} {
    this->first->previous = this->last;
    this->last->next = this->first;
    if(not size) {
        this->first->next = this->last;
        this->last->previous = this->first;
        return;
    }
    auto cursor {this->first->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))};
    cursor->previous = this->first;
    for(auto i {1}; i < size; ++i) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
        cursor->next->previous = cursor;
        cursor->data = value;
        cursor = cursor->next;
    }
    cursor->data = value;
    cursor->next = this->last;
    this->last->previous = cursor;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(sizeType size) : List(size, valueType()) {}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(pointer begin, pointer end) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))} {
    this->init(begin, end);
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(iterator begin, iterator end) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))} {
    this->init(begin, end);
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(std::initializer_list<valueType> list) :
        first {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))},
        last {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))} {
    this->init(list.begin(), list.end());
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(const List &other) :
        List(other.constBegin(), other.constEnd()) {}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::List(List &&other) noexcept :
        List(other.first, other.last) {
    other.first = other.last = nullptr;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::~List() {
    this->clear();
    Alloc::operator delete (this->first);
    Alloc::operator delete (this->last);
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc> &DataStructure::List<T, Alloc>::operator=(const List &other) {
    if(this == &other) {
        return *this;
    }
    this->clear();
    this->init(other.constBegin(), other.constEnd());
    return *this;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc> &DataStructure::List<T, Alloc>::operator=(List &&other) noexcept {
    if(this == &other) {
        return *this;
    }
    this->clear();
    Alloc::operator delete (this->first);
    Alloc::operator delete (this->last);
    this->first = other.first;
    this->last = other.last;
    return *this;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc> &
DataStructure::List<T, Alloc>::operator=(std::initializer_list<valueType> list) {
    this->clear();
    this->init(list.begin(), list.end());
    return *this;
}
template <typename T, typename Alloc>
inline bool DataStructure::List<T, Alloc>::operator==(const List &other) const {
    return this->size() == other.size() and [](const List &a, const List &b) -> bool {
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
bool DataStructure::List<T, Alloc>::operator not_eq(const List &other) const {
    return not(*this == other);
}
template <typename T, typename Alloc>
inline bool DataStructure::List<T, Alloc>::operator<(const List &other) const {
    auto thisSize {this->size()};
    auto otherSize {other.size()};
    if(otherSize not_eq thisSize) {
        return thisSize < otherSize;
    }
    return [](const List &a, const List &b) -> bool {
        auto begin {b.constBegin()};
        for(auto &c : a) {
            if(c not_eq *begin) {
                return c < *begin;
            }
            ++begin;
        }
        return true;
    }(*this, other);
}
template <typename T, typename Alloc>
bool DataStructure::List<T, Alloc>::operator<=(const List &other) const {
    return *this < other or *this == other;
}
template <typename T, typename Alloc>
inline bool DataStructure::List<T, Alloc>::operator>(const List &other) const {
    return not(*this < other);
}
template <typename T, typename Alloc>
bool DataStructure::List<T, Alloc>::operator>=(const List &other) const {
    return *this > other or *this == other;
}
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>::operator bool() const {
    return this->size() not_eq 0;
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::assign(sizeType size, constReference value) {
    auto cursor {this->first->next};
    while(cursor not_eq this->last and size) {
        cursor->data = value;
        cursor = cursor->next;
        --size;
    }
    if(cursor not_eq this->last) {
        cursor->previous->next = this->last;
        this->last->previous = cursor->previous;
        while(true) {
            auto next {cursor->next};
            Alloc::operator delete (cursor);
            cursor = next;
            if(cursor == this->last) {
                return;
            }
        }
    }
    if(not size) {
        return;
    }
    if(cursor == this->last) {
        cursor = cursor->previous;
    }
    for(auto i {0}; i < size; ++i) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
        cursor->next->previous = cursor;
        cursor = cursor->next;
        cursor->data = value;
    }
    cursor->next = this->last;
    this->last->previous = cursor;
}
template <typename T, typename Alloc>
inline void DataStructure::List<T, Alloc>::assign(iterator begin, iterator end) {
    auto cursor {this->first->next};
    while(cursor not_eq this->last and begin not_eq end) {
        cursor->data = *begin++;
        cursor = cursor->next;
    }
    if(cursor not_eq this->last) {
        cursor->previous->next = this->last;
        this->last->previous = cursor->previous;
        while(true) {
            auto next {cursor->next};
            Alloc::operator delete (cursor);
            cursor = next;
            if(cursor == this->last) {
                return;
            }
        }
    }
    if(begin == end) {
        return;
    }
    if(cursor == this->last) {
        cursor = cursor->previous;
    }
    while(begin not_eq end) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
        cursor->next->previous = cursor;
        cursor = cursor->next;
        cursor->data = *begin++;
    }
    cursor->next = this->last;
    this->last->previous = cursor;
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::assign(std::initializer_list<valueType> list) {
    this->assignGeneric(list.begin(), list.end());
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::assign(pointer begin, pointer end) {
    this->assignGeneric(begin, end);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::valueType DataStructure::List<T, Alloc>::front() const {
    return this->first->next->data;
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::valueType DataStructure::List<T, Alloc>::back() const {
    return this->last->previous->data;
}
template <typename T, typename Alloc>
bool DataStructure::List<T, Alloc>::empty() const {
    return this->first->next == this->last;
}
template <typename T, typename Alloc>
inline typename DataStructure::List<T, Alloc>::sizeType
DataStructure::List<T, Alloc>::size() const {
    auto cursor {this->first};
    sizeType size {0};
    while(cursor->next not_eq this->last) {
        ++size;
        cursor = cursor->next;
    }
    return size;
}
template <typename T, typename Alloc>
inline typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::begin() const {
    return iterator(this->first->next);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::constIterator
DataStructure::List<T, Alloc>::constBegin() const {
    return this->begin();
}
template <typename T, typename Alloc>
inline typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::end() const {
    return iterator(this->last);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::constIterator
DataStructure::List<T, Alloc>::constEnd() const {
    return this->end();
}
template <typename T, typename Alloc>
inline void DataStructure::List<T, Alloc>::clear() {
    auto cursor {this->first->next};
    while(cursor not_eq this->last) {
        auto next {cursor->next};
        Alloc::operator delete (cursor);
        cursor = next;
    }
    this->first->next = this->last;
    this->last->previous = this->first;
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::pushBack(constReference value) {
    this->insert(value, this->size());
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::pushBack(rightValueReference value) {
    this->insert(std::move(value), this->size());
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::pushFront(constReference value) {
    this->insert(value, 0);
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::pushFront(rightValueReference value) {
    this->insert(std::move(value), 0);
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::popFront() {
    this->erase(0);
}
template <typename T, typename Alloc>
void DataStructure::List<T, Alloc>::popBack() {
    this->erase(this->size() - 1);
}
template <typename T, typename Alloc>
inline typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::insert(
        constReference value, differenceType position, sizeType size
) {
    if(position > this->size() or position < 0) {
        throw OutOfRange("The position is out of range!");
    }
    if(not size) {
        return [=](differenceType position) -> iterator {
            auto cursor {this->first};
            while(position--) {
                cursor = cursor->next;
            }
            return iterator(cursor);
        }(position);
    }
    auto cursor {this->first};
    while(--position) {
        cursor = cursor->next;
    }
    auto returnNode {cursor};
    auto next {cursor->next};
    while(--size) {
        auto newNode {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))};
        newNode->previous = cursor;
        newNode->data = value;
        cursor->next = newNode;
        cursor = cursor->next;
    }
    cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
    cursor->next->previous = cursor;
    cursor = cursor->next;
    cursor->data = value;
    cursor->next = next;
    next->previous = cursor;
    return iterator(returnNode->next);
}
template <typename T, typename Alloc>
inline typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::insert(
        rightValueReference value, differenceType position, sizeType size
) {
    if(position > this->size() or position < 0) {
        throw OutOfRange("The position is out of range!");
    }
    if(not size) {
        return [=](differenceType position) -> iterator {
            auto cursor {this->first};
            while(position--) {
                cursor = cursor->next;
            }
            return iterator(cursor);
        }(position);
    }
    auto cursor {this->first};
    while(--position) {
        cursor = cursor->next;
    }
    auto returnNode {cursor};
    auto next {cursor->next};
    while(--size) {
        auto newNode {reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)))};
        newNode->previous = cursor;
        newNode->data = value;
        cursor->next = newNode;
        cursor = cursor->next;
    }
    cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
    cursor->next->previous = cursor;
    cursor = cursor->next;
    cursor->data = std::move(value);
    cursor->next = next;
    next->previous = cursor;
    return iterator(returnNode->next);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator DataStructure::List<T, Alloc>::
        insert(constIterator position, constReference value, sizeType size) {
    return this->insert(value, this->getDifference(position), size);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::insert(
        constIterator position, rightValueReference value, sizeType size
) {
    return this->insert(std::move(value), this->getDifference(position), size);
}
template <typename T, typename Alloc>
template <typename ForwardIterator>
inline typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::insert(
        constIterator position, ForwardIterator begin, ForwardIterator end
) {
    auto pos {this->getDifference(position)};
    auto cursor {this->first};
    while(pos--) {
        cursor = cursor->next;
    }
    auto next {cursor->next};
    while(begin not_eq end) {
        cursor->next = reinterpret_cast<node>(Alloc::operator new (sizeof(Node<T>)));
        cursor->next->previous = cursor;
        cursor = cursor->next;
        cursor->data = *begin++;
    }
    cursor->next = next;
    next->previous = cursor;
    iterator returnPosition {position};
    ++returnPosition;
    return std::move(returnPosition);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator DataStructure::List<T, Alloc>::
        insert(constIterator position, std::initializer_list<valueType> list) {
    return this->insert(position, list.begin(), list.end());
}
template <typename T, typename Alloc>
template <typename ...Args>
typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::emplace(constIterator position, Args &&...args) {
    return this->insert(position, typename removeReference<T>::type(args...));
}
template <typename T, typename Alloc>
template <typename ...Args>
void DataStructure::List<T, Alloc>::emplaceFront(Args &&...args) {
    this->insert(this->begin(), typename removeReference<T>::type(args)...);
}
template <typename T, typename Alloc>
template <typename ...Args>
void DataStructure::List<T, Alloc>::emplaceBack(Args &&...args) {
    this->insert(this->end(), typename removeReference<T>::type(args)...);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::erase(differenceType position, sizeType size) {
    auto cursor {this->first};
    while(position--) {
        cursor = cursor->next;
    }
    auto save {cursor};
    cursor = cursor->next;
    while(size--) {
        auto next {cursor->next};
        Alloc::operator delete (cursor);
        cursor = next;
    }
    save->next = cursor;
    cursor->previous = save;
    return iterator(save->next);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::erase(constIterator position, sizeType size) {
    return this->erase(this->getDifference(position), size);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::erase(constIterator begin, constIterator end) {
    return this->erase(this->getDifference(begin),
                [](iterator begin, constIterator &end) -> sizeType {
        sizeType size {0};
        while(begin not_eq end) {
            ++begin;
            ++size;
        }
        return size;
    }(static_cast<iterator>(begin), end));
}
#ifdef OTHER_FUNCTION
template <typename T, typename Alloc>
DataStructure::List<T, Alloc>
DataStructure::List<T, Alloc>::get(differenceType position, sizeType size) const {
    auto begin {this->first};
    while(position--) {
        begin = begin->next;
    }
    auto end {begin};
    while(size--) {
        end = end->next;
    }
    return List(iterator(begin), iterator(end));
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::iterator
DataStructure::List<T, Alloc>::beforeBegin() const {
    return iterator(this->first);
}
template <typename T, typename Alloc>
typename DataStructure::List<T, Alloc>::constIterator
DataStructure::List<T, Alloc>::beforeConstBegin() const {
    return iterator(this->first);
}
#endif

#endif //DATA_STRUCTURE_LIST_HPP
