#ifndef DATA_STRUCTURE_LIST_HPP
#define DATA_STRUCTURE_LIST_HPP

#include "../Allocator.hpp"
#include "../Iterator.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>>
    class List final {
    public:
        using allocator = Alloc;
        using sizeType = typename allocator::sizeType;
        using differenceType = typename allocator::differenceType;
        using valueType = typename allocator::valueType;
        using reference = typename allocator::reference;
        using constReference = typename allocator::constReference;
        using rightValueReference = typename allocator::rightValueReference;
        using pointer = typename allocator::pointer;
        using constPointer = typename allocator::constPointer;
    private:
        using nodeType = __DataStructure_BidirectionalNode<valueType, reference, pointer>;
        using constNodeType = __DataStructure_BidirectionalNode<valueType, constReference, constPointer>;
    public:
        using iterator = __DataStructure_ListIterator<nodeType>;
        using constIterator = __DataStructure_ListIterator<constNodeType>;
        using reverseIterator = __DataStructure_ListReverseIterator<nodeType>;
        using constReverseIterator = __DataStructure_ListReverseIterator<constNodeType>;
    private:
        using node = nodeType *;
    private:
        node first;
    private:
        static node getNewNode();
    private:
        void free() noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
        void setLink(sizeType, constReference, node);
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        void setLink(typename __DataStructure_isInputIterator<InputIterator>::__result,
                            InputIterator, node
                     );
        void resetFirst() noexcept;
    public:
        List();
        explicit List(sizeType);
        List(sizeType, constReference);
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        List(typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator);
        List(std::initializer_list<valueType>);
        List(const List &);
        List(List &&) noexcept;
        ~List();
    public:
        List &operator=(const List &);
        List &operator=(List &&) noexcept;
        List &operator=(std::initializer_list<valueType>);
        bool operator==(const List &) const;
        bool operator!=(const List &) const;
        bool operator<(const List &) const;
        bool operator<=(const List &) const;
        bool operator>(const List &) const;
        bool operator>=(const List &) const;
        explicit operator bool() const noexcept;
        List operator+() const;
        List operator-() const;
    public:
        void assign(sizeType, constReference = valueType());
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        void assign(typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator);
        void assign(std::initializer_list<valueType>);
        valueType front() const;
        valueType back() const;
        iterator begin() const noexcept;
        constIterator cbegin() const noexcept;
        reverseIterator rbegin() const noexcept;
        constReverseIterator crbegin() const noexcept;
        iterator end() const noexcept;
        constIterator cend() const noexcept;
        reverseIterator rend() const noexcept;
        constReverseIterator crend() const noexcept;
        bool empty() const noexcept;
        sizeType size() const noexcept;
        void clear() noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
        iterator insert(differenceType, constReference, sizeType = 1);
        iterator insert(differenceType, rightValueReference);
        iterator insert(constIterator, constReference, sizeType = 1);
        iterator insert(constIterator, rightValueReference);
        template <typename InputIterator,
                typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
        >
        iterator insert(constIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator
        );
        template <typename InputIterator,
                typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
        >
        iterator insert(differenceType,
                        typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator
        );
        iterator insert(constIterator, std::initializer_list<valueType>);
        iterator insert(differenceType, std::initializer_list<valueType>);
        iterator erase(constIterator, sizeType = 1) noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
        iterator erase(differenceType, sizeType = 1) noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
        iterator erase(constIterator, constIterator) noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
        void pushBack(constReference);
        void pushBack(rightValueReference);
        void pushFront(constReference);
        void pushFront(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        popFront() noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        popBack() noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
        template <typename ...Args>
        iterator emplace(constIterator, Args &&...);
        template <typename ...Args>
        iterator emplace(differenceType, Args &&...);
        template <typename ...Args>
        void emplaceBack(Args &&...);
        template <typename ...Args>
        void emplaceFront(Args &&...);
        void swap(List &) noexcept;
#ifdef DEBUG_DATA_STRUCTURE_FOR_LIST
        node &getFirst() noexcept;
#endif
    };
    template <typename T, typename Alloc>
    void swap(List<T, Alloc> &, List<T, Alloc> &) noexcept;
}

template <typename T, typename Allocator>
void DataStructure::swap(List<T, Allocator> &lhs, List<T, Allocator> &rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T, typename Allocator>
inline typename DataStructure::List<T, Allocator>::node DataStructure::List<T, Allocator>::getNewNode() {
    return reinterpret_cast<node>(allocator::operator new (sizeof(nodeType)));
}
template <typename T, typename Allocator>
inline void DataStructure::List<T, Allocator>::free() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    if(not this->first) {
        return;
    }
    auto cursor {this->first->next};
    while(cursor not_eq this->first) {
        auto temp {cursor};
        cursor = cursor->next;
        allocator::operator delete (temp);
    }
}
template <typename T, typename Allocator>
inline void DataStructure::List<T, Allocator>::setLink(sizeType size, constReference value, node first) {
    auto newNode {List::getNewNode()};
    newNode->previous = first;
    const auto backup {newNode};
    while(--size) {
        new (&newNode->data) valueType(value);
        newNode->next = List::getNewNode();
        newNode->next->previous = newNode;
        newNode = newNode->next;
    }
    new (&newNode->data) valueType(value);
    newNode->next = first->next;
    first->next->previous = newNode;
    first->next = backup;
}
template <typename T, typename Allocator>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
         >
inline void DataStructure::List<T, Allocator>::setLink(
        typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last, node firstNode
) {
    auto newNode {List::getNewNode()};
    newNode->previous = firstNode;
    const auto backup {newNode};
    --last;
    while(first not_eq last) {
        new (&newNode->data) valueType(*first++);
        newNode->next = List::getNewNode();
        newNode->next->previous = newNode;
        newNode = newNode->next;
    }
    new (&newNode->data) valueType(*last);
    newNode->next = firstNode->next;
    firstNode->next->previous = newNode;
    firstNode->next = backup;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::List() :
        first {List::getNewNode()} {
    this->first->next = this->first;
    this->first->previous = this->first;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::List(sizeType size, constReference value) : List() {
    if(not size) {
        return;
    }
    this->setLink(size, value, this->first);
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::List(sizeType size) : List(size, valueType()) {}
template <typename T, typename Allocator>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
         >
DataStructure::List<T, Allocator>::List(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) : List() {
    if(not IteratorDifference<InputIterator>()(first, last)) {
        return;
    }
    this->setLink(first, last, this->first);
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::List(std::initializer_list<valueType> list) : List(list.begin(), list.end()) {}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::List(const List &rhs) : List(rhs.cbegin(), rhs.cend()) {}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::List(List &&rhs) noexcept : first {rhs.first} {
    rhs.first = nullptr;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::~List() {
    this->free();
    allocator::operator delete (this->first);
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator> &DataStructure::List<T, Allocator>::operator=(const List &rhs) {
    if(&rhs == this) {
        return *this;
    }
    this->free();
    this->first->next = this->first;
    this->first->previous = this->first;
    this->setLink(rhs.cbegin(), rhs.cend(), this->first);
    return *this;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator> &DataStructure::List<T, Allocator>::operator=(List &&rhs) noexcept {
    if(&rhs == this) {
        return *this;
    }
    this->free();
    this->first = rhs.first;
    rhs.first = nullptr;
    return *this;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator> &
DataStructure::List<T, Allocator>::operator=(std::initializer_list<valueType> list) {
    *this = List(list.begin(), list.end());
    return *this;
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::operator==(const List &rhs) const {
    return this->size() == rhs.size() and [](const List &lhs, const List &rhs) -> bool {
        auto lhsEnd {lhs.cend()};
        for(auto rhsIt {rhs.cbegin()}, lhsIt {lhs.cbegin()}; lhsIt not_eq lhsEnd; ++rhsIt, ++lhsIt) {
            if(*lhsIt == *rhsIt) {
                continue;
            }
            return false;
        }
        return true;
    }(*this, rhs);
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::operator!=(const List &rhs) const {
    return not(*this == rhs);
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::operator<(const List &rhs) const {
    const auto lhsSize {this->size()};
    const auto rhsSize {rhs.size()};
    if(lhsSize <= rhsSize) {
        auto lhsEnd {this->cend()};
        for(auto rhsIt {rhs.cbegin()}, lhsIt {this->cbegin()}; lhsIt not_eq lhsEnd; ++rhsIt, ++lhsIt) {
            if(*lhsIt == *rhsIt) {
                continue;
            }
            return *lhsIt < *rhsIt;
        }
        return true;
    }
    auto rhsEnd {rhs.cend()};
    for(auto rhsIt {rhs.cbegin()}, lhsIt {this->cbegin()}; rhsIt not_eq rhsEnd; ++rhsIt, ++lhsIt) {
        if(*lhsIt == *rhsIt) {
            continue;
        }
        return *lhsIt < *rhsIt;
    }
    return false;
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::operator<=(const List &rhs) const {
    return *this < rhs or *this == rhs;
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::operator>(const List &rhs) const {
    return not(*this <= rhs);
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::operator>=(const List &rhs) const {
    return not(*this < rhs);
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator>::operator bool() const noexcept {
    return this->first->next == this->first;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator> DataStructure::List<T, Allocator>::operator+() const {
    auto temp {*this};
    for(auto &c : temp) {
        c = +c;
    }
    return temp;
}
template <typename T, typename Allocator>
DataStructure::List<T, Allocator> DataStructure::List<T, Allocator>::operator-() const {
    auto temp {*this};
    for(auto &c : temp) {
        c = -c;
    }
    return temp;
}
template <typename T, typename Allocator>
inline void DataStructure::List<T, Allocator>::resetFirst() noexcept {
    this->first->next = this->first;
    this->first->previous = this->first;
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::assign(sizeType size, constReference value) {
    this->free();
    this->resetFirst();
    this->setLink(size, value, this->first);
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
void DataStructure::List<T, Allocator>::assign(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    this->free();
    this->resetFirst();
    this->setLink(first, last, this->first);
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::assign(std::initializer_list<valueType> list) {
    this->assign(list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::valueType DataStructure::List<T, Allocator>::front() const {
    return this->first->next->data;
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::valueType DataStructure::List<T, Allocator>::back() const {
    return this->first->previous->data;
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::begin() const noexcept {
    return iterator(this->first->next);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::end() const noexcept {
    return iterator(this->first);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::constIterator
DataStructure::List<T, Allocator>::cbegin() const noexcept {
    return constIterator(reinterpret_cast<constNodeType *>(this->first->next));
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::constIterator
DataStructure::List<T, Allocator>::cend() const noexcept {
    return constIterator(reinterpret_cast<constNodeType *>(this->first));
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::reverseIterator
DataStructure::List<T, Allocator>::rbegin() const noexcept {
    return reverseIterator(this->first->previous);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::reverseIterator
DataStructure::List<T, Allocator>::rend() const noexcept {
    return reverseIterator(this->first);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::constReverseIterator
DataStructure::List<T, Allocator>::crbegin() const noexcept {
    return constReverseIterator(reinterpret_cast<constNodeType *>(this->first->previous));
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::constReverseIterator
DataStructure::List<T, Allocator>::crend() const noexcept {
    return constReverseIterator(reinterpret_cast<constNodeType *>(this->first));
}
template <typename T, typename Allocator>
bool DataStructure::List<T, Allocator>::empty() const noexcept {
    return this->operator bool();
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::sizeType DataStructure::List<T, Allocator>::size() const noexcept {
    sizeType count {0};
    auto cursor {this->first};
    while(cursor->next not_eq this->first) {
        ++count;
        cursor = cursor->next;
    }
    return count;
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::clear() noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    this->free();
    this->resetFirst();
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(differenceType index, constReference value, sizeType size) {
    auto cursor {this->first};
    while(index--) {
        cursor = cursor->next;
    }
    this->setLink(size, value, cursor);
    return iterator(cursor->next);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(constIterator position, constReference value, sizeType size) {
    return this->insert(IteratorDifference<iterator>()(this->cbegin(), position), value, size);
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(
        differenceType index,
        typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last
) {
    auto cursor {this->first};
    while(index--) {
        cursor = cursor->next;
    }
    this->setLink(first, last, cursor);
    return iterator(cursor->next);
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(constIterator position,
        typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last
) {
    return this->insert(IteratorDifference<iterator>()(this->cbegin(), position), first, last);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(differenceType index, rightValueReference value) {
    auto cursor {this->first};
    while(index--) {
        cursor = cursor->next;
    }
    auto newNode {List::getNewNode()};
    new (&newNode->data) valueType(value);
    newNode->next = cursor->next;
    newNode->previous = cursor;
    cursor->next->previous = newNode;
    cursor->next = newNode;
    return iterator(newNode);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(constIterator position, rightValueReference value) {
    return this->insert(IteratorDifference<constIterator>()(this->cbegin(), position), value);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(differenceType index, std::initializer_list<valueType> list) {
    return this->insert(index, list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::insert(constIterator position, std::initializer_list<valueType> list) {
    return this->insert(IteratorDifference<constIterator>()(this->cbegin(), position), list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::erase(differenceType index, sizeType size) noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    auto cursor {this->first};
    while(--index) {
        cursor = cursor->next;
    }
    auto eraseCursor {cursor->next};
    while(size--) {
        auto next {eraseCursor->next};
        delete eraseCursor;
        eraseCursor = next;
    }
    eraseCursor->previous = cursor;
    cursor->next = eraseCursor;
    return iterator(cursor);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::erase(constIterator position, sizeType size) noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    return this->erase(IteratorDifference<constIterator>()(this->cbegin(), position), size);
}
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::erase(constIterator first, constIterator last) noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    IteratorDifference<constIterator> iteratorDifference;
    return this->erase(iteratorDifference(this->cbegin(), first), iteratorDifference(first, last));
}
template <typename T, typename Allocator>
template <typename ...Args>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::emplace(differenceType index, Args &&...args) {
    return insert(index, valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
template <typename ...Args>
typename DataStructure::List<T, Allocator>::iterator
DataStructure::List<T, Allocator>::emplace(constIterator position, Args &&...args) {
    return insert(IteratorDifference<constIterator>()(this->cbegin(), position),
                    valueType(std::forward<Args>(args)...)
                 );
}
template <typename T, typename Allocator>
template <typename ...Args>
void DataStructure::List<T, Allocator>::emplaceFront(Args &&...args) {
    this->pushFront(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
template <typename ...Args>
void DataStructure::List<T, Allocator>::emplaceBack(Args &&...args) {
    this->pushBack(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::swap(List &rhs) noexcept {
    using std::swap;
    swap(this->first, rhs.first);
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::pushFront(constReference value) {
    auto newNode {List::getNewNode()};
    newNode->previous = this->first;
    newNode->next = this->first->next;
    this->first->next->previous = newNode;
    this->first->next = newNode;
    new (&newNode->data) valueType(value);
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::pushFront(rightValueReference value) {
    auto newNode {List::getNewNode()};
    newNode->previous = this->first;
    newNode->next = this->first->next;
    this->first->next->previous = newNode;
    this->first->next = newNode;
    new (&newNode->data) valueType(value);
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::pushBack(constReference value) {
    auto newNode {List::getNewNode()};
    newNode->next = this->first;
    newNode->previous = this->first->previous;
    this->first->previous->next = newNode;
    this->first->previous = newNode;
    new (&newNode->data) valueType(value);
}
template <typename T, typename Allocator>
void DataStructure::List<T, Allocator>::pushBack(rightValueReference value) {
    auto newNode {List::getNewNode()};
    newNode->next = this->first;
    newNode->previous = this->first->previous;
    this->first->previous->next = newNode;
    this->first->previous = newNode;
    new (&newNode->data) valueType(value);
}
template <typename T, typename Allocator>
#ifdef POP_GET_OBJECT
typename DataStructure::List<T, Allocator>::valueType
#else
void
#endif
DataStructure::List<T, Allocator>::popBack() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    auto pop {this->first->previous};
    this->first->previous = pop->previous;
    pop->previous->next = this->first;
#ifdef POP_GET_OBJECT
    auto value {move(pop->data)};
#endif
    delete pop;
#ifdef POP_GET_OBJECT
    return value;
#endif
}
template <typename T, typename Allocator>
#ifdef POP_GET_OBJECT
typename DataStructure::List<T, Allocator>::valueType
#else
void
#endif
DataStructure::List<T, Allocator>::popFront() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    auto pop {this->first->next};
    pop->next->previous = this->first;
    this->first->next = pop->next;
#ifdef POP_GET_OBJECT
    auto value {move(pop->data)};
#endif
    delete pop;
#ifdef POP_GET_OBJECT
    return value;
#endif
}

#ifdef DEBUG_DATA_STRUCTURE_FOR_LIST
template <typename T, typename Allocator>
typename DataStructure::List<T, Allocator>::node &DataStructure::List<T, Allocator>::getFirst() noexcept {
    return this->first;
}
#endif

#endif //DATA_STRUCTURE_LIST_HPP
