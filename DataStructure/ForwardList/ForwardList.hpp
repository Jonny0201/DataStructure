#ifndef DATA_STRUCTURE_FORWARD_LIST_HPP
#define DATA_STRUCTURE_FORWARD_LIST_HPP

#include "../Allocator.hpp"
#include "../Iterator.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>>
    class ForwardList final {
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
        using nodeType = __DataStructure_ForwardNode<valueType, reference, pointer>;
        using constNodeType = __DataStructure_ForwardNode<valueType, constReference, constPointer>;
    public:
        using iterator = __DataStructure_ForwardListIterator<nodeType>;
        using constIterator = __DataStructure_ForwardListIterator<constNodeType>;
    private:
        using node = nodeType *;
    private:
        node first;
    private:
        static node getNewNode();
    private:
        void free() noexcept(
                static_cast<bool>(
                        typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
                )
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
        ForwardList();
        explicit ForwardList(sizeType);
        ForwardList(sizeType, constReference);
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        ForwardList(typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator);
        ForwardList(std::initializer_list<valueType>);
        ForwardList(const ForwardList &);
        ForwardList(ForwardList &&) noexcept;
        ~ForwardList();
    public:
        ForwardList &operator=(const ForwardList &);
        ForwardList &operator=(ForwardList &&) noexcept;
        ForwardList &operator=(std::initializer_list<valueType>);
        bool operator==(const ForwardList &) const;
        bool operator!=(const ForwardList &) const;
        bool operator<(const ForwardList &) const;
        bool operator<=(const ForwardList &) const;
        bool operator>(const ForwardList &) const;
        bool operator>=(const ForwardList &) const;
        explicit operator bool() const noexcept;
        ForwardList operator+() const;
        ForwardList operator-() const;
    public:
        void assign(sizeType, constReference);
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        void assign(typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator);
        void assign(std::initializer_list<valueType>);
        valueType front() const noexcept;
        iterator begin() const noexcept;
        constIterator cbegin() const noexcept;
        constexpr iterator end() const noexcept;
        constexpr constIterator cend() const noexcept;
        iterator beforeBegin() const noexcept;
        constIterator beforeCBegin() const noexcept;
        bool empty() const noexcept;
        sizeType size() const noexcept;
        void clear() noexcept(
                static_cast<bool>(
                        typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
                )
        );
        iterator insertAfter(differenceType, constReference, sizeType = 1);
        iterator insertAfter(constIterator, constReference, sizeType = 1);
        iterator insertAfter(differenceType, rightValueReference);
        iterator insertAfter(constIterator, rightValueReference);
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        iterator insertAfter(differenceType,
                                 typename __DataStructure_isInputIterator<InputIterator>::__result,
                                 InputIterator
                            );
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        iterator insertAfter(constIterator,
                                 typename __DataStructure_isInputIterator<InputIterator>::__result,
                                 InputIterator
                            );
        iterator insertAfter(differenceType, std::initializer_list<valueType>);
        iterator insertAfter(constIterator, std::initializer_list<valueType>);
        iterator eraseAfter(differenceType, sizeType = 1) noexcept(
                static_cast<bool>(
                        typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
                )
        );
        iterator eraseAfter(constIterator, sizeType = 1) noexcept(
                static_cast<bool>(
                        typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
                )
        );
        iterator eraseAfter(constIterator, constIterator) noexcept(
                static_cast<bool>(
                        typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
                )
        );
        template <typename ...Args>
        iterator emplaceAfter(differenceType, Args &&...);
        template <typename ...Args>
        iterator emplaceAfter(constIterator, Args &&...);
        template <typename ...Args>
        void emplaceFront(Args &&...);
        void pushFront(constReference);
        void pushFront(rightValueReference);
#ifdef POP_GET_OBJECT
        valueType
#else
        void
#endif
        popFront() noexcept(
                static_cast<bool>(
                        typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
                )
        );
        void swap(ForwardList &) noexcept;
#ifdef DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST
        node &getFirst() noexcept;
#endif
    };
    template <typename T, typename Allocator>
    void swap(ForwardList<T, Allocator> &, ForwardList<T, Allocator> &) noexcept;
}

template <typename T, typename Allocator>
void DataStructure::swap(ForwardList<T, Allocator> &lhs, ForwardList<T, Allocator> &rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T, typename Allocator>
inline typename DataStructure::ForwardList<T, Allocator>::node
DataStructure::ForwardList<T, Allocator>::getNewNode() {
    return reinterpret_cast<node>(allocator::operator new (sizeof(nodeType)));
}
template <typename T, typename Allocator>
inline void DataStructure::ForwardList<T, Allocator>::free() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    if(not this->first) {
        return;
    }
    auto cursor {this->first->next};
    while(cursor) {
        auto next {cursor->next};
        allocator::destroy(&cursor->data);
        delete cursor;
        cursor = next;
    }
}
template <typename T, typename Allocator>
inline void DataStructure::ForwardList<T, Allocator>::setLink(
        sizeType size, constReference value, node first
) {
    auto newNode {ForwardList::getNewNode()};
    const auto backup {newNode};
    while(--size) {
        try {
            new (&newNode->data) valueType(value);
        }catch(...) {
            while(backup not_eq newNode) {
                auto next {backup->next};
                delete backup;
                backup = next;
            }
            allocator::operator delete (newNode);
            throw;
        }
        newNode->next = ForwardList::getNewNode();
        newNode = newNode->next;
    }
    new (&newNode->data) valueType(value);
    newNode->next = first->next;
    first->next = backup;
}
template <typename T, typename Allocator>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
         >
inline void DataStructure::ForwardList<T, Allocator>::setLink(
        typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last, node firstNode
) {
    auto newNode {ForwardList::getNewNode()};
    const auto backup {newNode};
    auto size {IteratorDifference<InputIterator>()(first, last)};
    while(--size) {
        try {
            new (&newNode->data) valueType(static_cast<valueType>(*first++));
        }catch(...) {
            while(backup not_eq newNode) {
                auto next {backup->next};
                delete backup;
                backup = next;
            }
            allocator::operator delete (newNode);
            throw;
        }
        newNode->next = ForwardList::getNewNode();
        newNode = newNode->next;
    }
    new (&newNode->data) valueType(static_cast<valueType>(*first));
    newNode->next = firstNode->next;
    firstNode->next = backup;
}
template <typename T, typename Allocator>
inline void DataStructure::ForwardList<T, Allocator>::resetFirst() noexcept {
    this->first->next = nullptr;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::ForwardList() :first {ForwardList::getNewNode()} {
    this->first->next = nullptr;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::ForwardList(sizeType size, constReference value) :
        ForwardList(){
    if(not size) {
        return;
    }
    this->setLink(size, value, this->first);
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::ForwardList(sizeType size) : ForwardList(size, valueType()) {}
template <typename T, typename Allocator>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
         >
DataStructure::ForwardList<T, Allocator>::ForwardList(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) : ForwardList() {
    if(not IteratorDifference<InputIterator>()(first, last)) {
        return;
    }
    this->setLink(first, last, this->first);
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::ForwardList(std::initializer_list<valueType> list) :
        ForwardList(list.begin(), list.end()) {}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::ForwardList(const ForwardList &rhs) :
        ForwardList(rhs.cbegin(), rhs.cend()) {}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::ForwardList(ForwardList &&rhs) noexcept : ForwardList() {
    this->first->next = rhs.first->next;
    rhs.first->next = nullptr;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::~ForwardList() {
    this->free();
    allocator::operator delete (this->first);
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator> &
DataStructure::ForwardList<T, Allocator>::operator=(const ForwardList &rhs) {
    if(&rhs == this) {
        return *this;
    }
    this->free();
    this->resetFirst();
    this->setLink(rhs.cbegin(), rhs.cend(), this->first);
    return *this;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator> &
DataStructure::ForwardList<T, Allocator>::operator=(ForwardList &&rhs) noexcept {
    if(&rhs == this) {
        return *this;
    }
    this->free();
    this->first->next = rhs.first->next;
    rhs.first->next = nullptr;
    return *this;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator> &
DataStructure::ForwardList<T, Allocator>::operator=(std::initializer_list<valueType> list) {
    this->free();
    this->resetFirst();
    this->setLink(list.begin(), list.end(), this->first);
    return *this;
}
template <typename T, typename Allocator>
bool DataStructure::ForwardList<T, Allocator>::operator==(const ForwardList &rhs) const {
    return this->size() == rhs.size() and [](const ForwardList &lhs, const ForwardList &rhs) -> bool {
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
bool DataStructure::ForwardList<T, Allocator>::operator!=(const ForwardList &rhs) const {
    return not(*this == rhs);
}
template <typename T, typename Allocator>
bool DataStructure::ForwardList<T, Allocator>::operator<(const ForwardList &rhs) const {
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
bool DataStructure::ForwardList<T, Allocator>::operator<=(const ForwardList &rhs) const {
    return *this < rhs or *this == rhs;
}
template <typename T, typename Allocator>
bool DataStructure::ForwardList<T, Allocator>::operator>(const ForwardList &rhs) const {
    return not(*this <= rhs);
}
template <typename T, typename Allocator>
bool DataStructure::ForwardList<T, Allocator>::operator>=(const ForwardList &rhs) const {
    return not(*this < rhs);
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator>::operator bool() const noexcept {
    return this->first->next;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator> DataStructure::ForwardList<T, Allocator>::operator+() const {
    auto temp {*this};
    for(auto &c : temp) {
        c = +c;
    }
    return temp;
}
template <typename T, typename Allocator>
DataStructure::ForwardList<T, Allocator> DataStructure::ForwardList<T, Allocator>::operator-() const {
    auto temp {*this};
    for(auto &c : temp) {
        c = -c;
    }
    return temp;
}
template <typename T, typename Allocator>
void DataStructure::ForwardList<T, Allocator>::assign(sizeType size, constReference value) {
    auto cursor {this->first};
    while(cursor->next and size) {
        cursor = cursor->next;
        allocator::destroy(&cursor->data);
        new (&cursor->data) valueType(value);
        --size;
    }
    if(size) {
        this->setLink(size, value, cursor);
    }
}
template <typename T, typename Allocator>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
         >
void DataStructure::ForwardList<T, Allocator>::assign(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    auto cursor {this->first};
    auto size {IteratorDifference<InputIterator>()(first, last)};
    while(cursor->next and size) {
        cursor = cursor->next;
        allocator::destroy(&cursor->data);
        new (&cursor->data) valueType(static_cast<valueType>(*first++));
        --size;
    }
    if(size) {
        this->setLink(first, last, cursor);
    }
}
template <typename T, typename Allocator>
void DataStructure::ForwardList<T, Allocator>::assign(std::initializer_list<valueType> list) {
    this->assign(list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::valueType
DataStructure::ForwardList<T, Allocator>::front() const noexcept {
    return this->first->next->data;
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::begin() const noexcept {
    return iterator(this->first->next);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::constIterator
DataStructure::ForwardList<T, Allocator>::cbegin() const noexcept {
    return constIterator(reinterpret_cast<constNodeType *>(this->first->next));
}
template <typename T, typename Allocator>
constexpr typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::end() const noexcept {
    return iterator();
}
template <typename T, typename Allocator>
constexpr typename DataStructure::ForwardList<T, Allocator>::constIterator
DataStructure::ForwardList<T, Allocator>::cend() const noexcept {
    return constIterator();
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::beforeBegin() const noexcept {
    return iterator(this->first);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::constIterator
DataStructure::ForwardList<T, Allocator>::beforeCBegin() const noexcept {
    return constIterator(reinterpret_cast<constNodeType *>(this->first));
}
template <typename T, typename Allocator>
bool DataStructure::ForwardList<T, Allocator>::empty() const noexcept {
    return not this->operator bool();
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::sizeType
DataStructure::ForwardList<T, Allocator>::size() const noexcept {
    auto cursor {this->first->next};
    sizeType count {0};
    while(cursor) {
        ++count;
        cursor = cursor->next;
    }
    return count;
}
template <typename T, typename Allocator>
void DataStructure::ForwardList<T, Allocator>::clear() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    this->free();
    this->resetFirst();
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(
        differenceType index, constReference value, sizeType size
) {
    auto cursor {this->first->next};
    while(index--) {
        cursor = cursor->next;
    }
    this->setLink(size, value, cursor);
    return iterator(cursor->next);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(
        constIterator position, constReference value, sizeType size
) {
    return this->insertAfter(IteratorDifference<constIterator>()(this->cbegin(), position), value, size);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(differenceType index, rightValueReference value) {
    auto cursor {this->first->next};
    while(index--) {
        cursor = cursor->next;
    }
    auto newNode {ForwardList::getNewNode()};
    new (&newNode->data) valueType(move(value));
    newNode->next = cursor->next;
    cursor->next = newNode;
    return iterator(newNode);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(
        constIterator position, rightValueReference value
) {
    return this->insertAfter(IteratorDifference<constIterator>()(this->cbegin(), position), move(value));
}
template <typename T, typename Allocator>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(differenceType index,
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    auto cursor {this->first->next};
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
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(constIterator position,
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    return this->insertAfter(
                IteratorDifference<constIterator>()(this->cbegin(), position), first, last
           );
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(
        differenceType index, std::initializer_list<valueType> list
) {
    return this->insertAfter(index, list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::insertAfter(
        constIterator position, std::initializer_list<valueType> list
) {
    return this->insertAfter(
                IteratorDifference<constIterator>()(this->cbegin(), position), list.begin(), list.end()
           );
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::eraseAfter(differenceType index, sizeType size) noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    auto cursor {this->first->next};
    while(index--) {
        cursor = cursor->next;
    }
    auto eraseCursor {cursor->next};
    while(size--) {
        auto next {eraseCursor->next};
        delete eraseCursor;
        eraseCursor = next;
    }
    cursor->next = eraseCursor;
    return iterator(eraseCursor->next);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::eraseAfter(constIterator position, sizeType size) noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    return this->eraseAfter(IteratorDifference<constIterator>()(this->cbegin(), position), size);
}
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::eraseAfter(constIterator first, constIterator last) noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    return this->eraseAfter(
            IteratorDifference<constIterator>()(this->cbegin(), first),
            IteratorDifference<constIterator>()(first, last)
           );
}
template <typename T, typename Allocator>
template <typename ...Args>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::emplaceAfter(differenceType index, Args &&...args) {
    return this->insertAfter(index, valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
template <typename ...Args>
typename DataStructure::ForwardList<T, Allocator>::iterator
DataStructure::ForwardList<T, Allocator>::emplaceAfter(constIterator position, Args &&...args) {
    return this->insertAfter(IteratorDifference<constIterator>()(this->cbegin, position),
                valueType(std::forward<Args>(args)...)
           );
}
template <typename T, typename Allocator>
template <typename ...Args>
void DataStructure::ForwardList<T, Allocator>::emplaceFront(Args &&...args) {
    this->pushFront(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
void DataStructure::ForwardList<T, Allocator>::pushFront(constReference value) {
    auto newNode {ForwardList::getNewNode()};
    newNode->next = this->first->next;
    this->first->next = newNode;
    new (&newNode->data) valueType(value);
}
template <typename T, typename Allocator>
void DataStructure::ForwardList<T, Allocator>::pushFront(rightValueReference value) {
    auto newNode {ForwardList::getNewNode()};
    newNode->next = this->first->next;
    this->first->next = newNode;
    new (&newNode->data) valueType(move(value));
}
template <typename T, typename Allocator>
#ifdef POP_GET_OBJECT
typename DataStructure::ForwardList<T, Allocator>::valueType
#else
void
#endif
DataStructure::ForwardList<T, Allocator>::popFront() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    auto popNode {this->first->next};
#ifdef POP_GET_OBJECT
    auto value {move(popNode->data)};
#endif
    this->first->next = popNode->next;
    allocator::destroy(&popNode->data);
    delete popNode;
#ifdef POP_GET_OBJECT
    return value;
#endif
}
template <typename T, typename Allocator>
void DataStructure::ForwardList<T, Allocator>::swap(ForwardList &rhs) noexcept {
    using std::swap;
    swap(this->first, rhs.first);
}

#ifdef DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST
template <typename T, typename Allocator>
typename DataStructure::ForwardList<T, Allocator>::node
&DataStructure::ForwardList<T, Allocator>::getFirst() noexcept {
    return this->first;
}
#endif

#endif //DATA_STRUCTURE_FORWARD_LIST_HPP
