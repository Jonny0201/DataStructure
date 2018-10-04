#ifndef DATA_STRUCTURE_VECTOR_HPP
#define DATA_STRUCTURE_VECTOR_HPP

#include "../Allocator.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>>
    class Vector final {
    public:
        class Iterator;
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
        using iterator = Iterator;
        using constIterator = const Iterator;
    private:
        allocator alloc;
    private:
        void checkAllocator(sizeType);
        pointer insertAuxiliary(differenceType, sizeType);
    private:
        template <typename InputIterator>
        static typename DataStructure::__DataStructure_IteratorTraits<InputIterator, static_cast<bool>(
                        typename DataStructure::__DataStructure_typeTraits<InputIterator>::is_POD_type()
                )>::differenceType
        iteratorDifference(InputIterator, InputIterator) noexcept;
    public:
        Vector();
        explicit Vector(const allocator &);
        explicit Vector(allocator &&) noexcept;
        explicit Vector(sizeType, const allocator & = allocator());
        Vector(sizeType, constReference, const allocator & = allocator());
        template <typename InputIterator,
                    typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        Vector(typename __DataStructure_isInputIterator<InputIterator>::__result,
                    InputIterator, const allocator & = allocator()
              );
        Vector(std::initializer_list<valueType>, const allocator & = allocator());
        Vector(const Vector &) = default;
        Vector(const Vector &, const allocator &);
        Vector(Vector &&) noexcept = default;
        Vector(Vector &&, const allocator &);
        ~Vector() = default;
    public:
        Vector &operator=(const Vector &) = default;
        Vector &operator=(Vector &&) noexcept = default;
        Vector &operator=(std::initializer_list<valueType>);
        reference operator[](differenceType) &;
        constReference operator[](differenceType) const &;
        bool operator==(const Vector &) const;
        bool operator not_eq(const Vector &) const;
        bool operator<(const Vector &) const;
        bool operator<=(const Vector &) const;
        bool operator>(const Vector &) const;
        bool operator>=(const Vector &) const;
        Vector &operator+();
        Vector &operator-();
        explicit operator bool() const noexcept;
        explicit operator pointer() const & noexcept;
    public:
        void assign(sizeType, constReference = valueType(), const allocator & = allocator());
        template <typename InputIterator,
                    typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        void assign(typename __DataStructure_isInputIterator<InputIterator>::__result,
                    InputIterator, const allocator & = allocator()
        );
        void assign(std::initializer_list<valueType>, const allocator & = allocator());
        valueType at(differenceType) const;
        valueType front() const;
        valueType back() const;
        pointer data() & noexcept;
        constPointer data() const & noexcept;
        iterator begin() & noexcept;
        constIterator constBegin() const & noexcept;
        iterator end() & noexcept;
        constIterator constEnd() const & noexcept;
        bool empty() const noexcept;
        sizeType size() const noexcept;
        sizeType capacity() const noexcept;
        sizeType reserve() const noexcept;
        iterator resize(sizeType);
        iterator shrinkToFit();
        void clear() noexcept(
                static_cast<bool>(typename __DataStructure_typeTraits<valueType>::hasTrivialDestructor())
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
        iterator erase(constIterator, sizeType = 1);
        iterator erase(differenceType, sizeType = 1);
        iterator erase(constIterator, constIterator);
        void pushBack(constReference);
        void pushBack(rightValueReference);
        void pushFront(constReference);
        void pushFront(rightValueReference);
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
        template <typename ...Args>
        iterator emplace(constIterator, Args &&...);
        template <typename ...Args>
        iterator emplace(differenceType, Args &&...);
        template <typename ...Args>
        void emplaceBack(Args &&...);
        template <typename ...Args>
        void emplaceFront(Args &&...);
        void swap(Vector &) noexcept;
        Vector get(differenceType, sizeType) const;
        allocator getAllocator() const &;
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR
    public:
        allocator &getAllocator() & noexcept;
#endif
    };
    template <typename T>
    void swap(Vector<T> &, Vector<T> &) noexcept;
}

template <typename T, typename Allocator>
class DataStructure::Vector<T, Allocator>::Iterator final {
public:
    using sizeType = typename Vector<T, Allocator>::sizeType;
    using differenceType = typename Vector<T, Allocator>::differenceType;
    using valueType = typename Vector<T, Allocator>::valueType;
    using reference = typename Vector<T, Allocator>::reference;
    using constReference = typename Vector<T, Allocator>::constReference;
    using rightValueReference = typename Vector<T, Allocator>::rightValueReference;
    using pointer = typename Vector<T, Allocator>::pointer;
    using constPointer = typename Vector<T, Allocator>::constPointer;
    using iteratorTag = RandomAccessIterator;
private:
    pointer iterator;
public:
    constexpr Iterator() : iterator {nullptr} {}
    explicit Iterator(pointer iterator) : iterator {iterator} {}
    Iterator(const Iterator &) = default;
    Iterator(Iterator &&) noexcept = default;
    ~Iterator() = default;
public:
    Iterator &operator=(const Iterator &) = default;
    Iterator &operator=(Iterator &&) noexcept = default;
    reference operator*() noexcept {
        return *this->iterator;
    }
    pointer operator->() noexcept {
        return &**this;
    }
    reference operator[](differenceType index) {
        return *(iterator + index);
    }
    Iterator &operator+=(differenceType index) noexcept {
        this->iterator += index;
        return *this;
    }
    Iterator &operator-=(differenceType index) noexcept {
        return *this += -index;
    }
    Iterator &operator++() noexcept {
        ++this->iterator;
        return *this;
    }
    Iterator &operator--() noexcept {
        --this->iterator;
        return *this;
    }
    Iterator operator++(int) noexcept {
        auto temp {*this};
        ++*this;
        return temp;
    }
    Iterator operator--(int) noexcept {
        auto temp {*this};
        --*this;
        return temp;
    }
    Iterator operator+(differenceType n) const noexcept {
        auto temp {*this};
        temp += n;
        return temp;
    }
    Iterator operator-(differenceType n) const noexcept {
        return this->operator+(-n);
    }
    friend differenceType operator-(const Iterator &left, const Iterator &right) noexcept {
        return left.iterator - right.iterator;
    }
    bool operator==(const Iterator &rhs) const noexcept {
        return this->iterator == rhs.iterator;
    }
    bool operator not_eq (const Iterator &rhs) const noexcept {
        return not(*this == rhs);
    }
    bool operator<(const Iterator &rhs) const noexcept {
        return this->iterator < rhs.iterator;
    }
    bool operator<=(const Iterator &rhs) const noexcept {
        return *this < rhs or *this == rhs;
    }
    bool operator>(const Iterator &rhs) const noexcept {
        return not(*this <= rhs);
    }
    bool operator>=(const Iterator &rhs) const noexcept {
        return not(*this < rhs);
    }
};

template <typename T, typename Allocator>
inline void DataStructure::Vector<T, Allocator>::checkAllocator(sizeType size) {
    while(this->alloc.reserve() < size) {
        this->alloc.allocate(this->alloc.capacity() * 2);
    }
}
template <typename T, typename Allocator>
inline typename DataStructure::Vector<T, Allocator>::pointer
DataStructure::Vector<T, Allocator>::insertAuxiliary(differenceType index, sizeType size) {
    this->checkAllocator(size);
    const auto insertPosition {this->alloc.begin() + index};
    const auto last {this->alloc.getCursor() + size};
    auto cursor {const_cast<pointer>(last - 1)};
    auto moveCursor {cursor - size};
    while(moveCursor - insertPosition >= 0) {
        this->alloc.construct(cursor--, move(*moveCursor));
        this->alloc.destroy(moveCursor--);
    }
    this->alloc.getCursor() = last;
    return insertPosition;
};
template <typename T, typename Allocator>
template <typename InputIterator>
inline typename DataStructure::__DataStructure_IteratorTraits<InputIterator, static_cast<bool>(
                    typename DataStructure::__DataStructure_typeTraits<InputIterator>::is_POD_type()
            )>::differenceType
DataStructure::Vector<T, Allocator>::iteratorDifference(InputIterator first, InputIterator last) noexcept {
    typename DataStructure::__DataStructure_IteratorTraits<InputIterator, static_cast<bool>(
                    typename DataStructure::__DataStructure_typeTraits<InputIterator>::is_POD_type()
            )>::differenceType count {0};
    while(not(first == last)) {
        ++first;
        ++count;
    }
    return count;
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector() : alloc() {
    this->alloc.allocate();
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(const allocator &alloc) : alloc {alloc} {}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(allocator &&alloc) noexcept : alloc {std::move(alloc)} {}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(sizeType size, const allocator &alloc) :
        Vector(size, valueType(), alloc) {}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(sizeType size, constReference value, const allocator &alloc) :
        alloc {alloc} {
    this->checkAllocator(size);
    while(size--) {
        this->alloc.construct(this->alloc.getCursor(), value);
    }
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
DataStructure::Vector<T, Allocator>::Vector(
        typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last, const allocator &alloc
) : alloc(alloc) {
    this->checkAllocator(static_cast<sizeType>(Vector::iteratorDifference(first, last)));
    while(first not_eq last) {
        this->alloc.construct(this->alloc.getCursor(), static_cast<valueType>(*first++));
    }
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(std::initializer_list<valueType> list, const allocator &alloc) :
       Vector(list.begin(), list.end(), alloc) {}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(const Vector &rhs, const allocator &alloc) :
        Vector(rhs.begin(), rhs.end(), alloc) {}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::Vector(Vector &&rhs, const allocator &alloc) : alloc {alloc} {
    this->checkAllocator(rhs.size());
    for(auto &c : rhs) {
        alloc.construct(alloc.getCursor(), std::move(c));
    }
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator> &
DataStructure::Vector<T, Allocator>::operator=(std::initializer_list<valueType> list) {
    *this = Vector(list);
    return *this;
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::reference
DataStructure::Vector<T, Allocator>::operator[](differenceType index) & {
    return index >= 0 ? *(alloc.begin() + index) : *(alloc.getCursor() + index);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::constReference
DataStructure::Vector<T, Allocator>::operator[](differenceType index) const & {
    return const_cast<constReference>(const_cast<Vector *const>(this)->operator[](index));
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::operator==(const Vector &rhs) const {
    const auto size {this->size()};
    return size == rhs.size() and [size](const Vector &lhs, const Vector &rhs) -> bool {
        for(auto i {0}; i < size; ++i) {
            if(lhs[i] == rhs[i]) {
                continue;
            }
            return false;
        }
        return true;
    }(*this, rhs);
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::operator not_eq(const Vector &rhs) const {
    return not(*this == rhs);
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::operator<(const Vector &rhs) const {
    const auto lhsSize {this->size()};
    const auto rhsSize {rhs.size()};
    if(lhsSize <= rhsSize) {
        for(auto i {0}; i < lhsSize; ++i) {
            if((*this)[i] == rhs[i]) {
                continue;
            }
            return (*this)[i] < rhs[i];
        }
        return true;
    }
    for(auto i {0}; i < rhsSize; ++i) {
        if((*this)[i] == rhs[i]) {
            continue;
        }
        return (*this)[i] < rhs[i];
    }
    return false;
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::operator<=(const Vector &rhs) const {
    return *this < rhs or *this == rhs;
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::operator>(const Vector &rhs) const {
    return not(*this <= rhs);
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::operator>=(const Vector &rhs) const {
    return not(*this < rhs);
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator> &DataStructure::Vector<T, Allocator>::operator+() {
    for(auto &c : *this) {
        c = +c;
    }
    return *this;
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator> &DataStructure::Vector<T, Allocator>::operator-() {
    for(auto &c : *this) {
        c = -c;
    }
    return *this;
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::operator bool() const noexcept {
    return not this->alloc.empty();
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>::operator pointer() const & noexcept {
    return const_cast<pointer>(this->alloc.begin());
}
template <typename T, typename Allocator>
void
DataStructure::Vector<T, Allocator>::assign(sizeType size, constReference value, const allocator &alloc) {
    this->alloc = alloc;
    this->checkAllocator(size);
    while(size--) {
        this->alloc.construct(this->alloc.getCursor(), value);
    }
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
void
DataStructure::Vector<T, Allocator>::assign(
        typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last, const allocator &alloc
) {
    this->alloc = alloc;
    this->checkAllocator(static_cast<sizeType>(Vector::iteratorDifference(first, last)));
    while(first not_eq last) {
        this->alloc.construct(this->alloc.getCursor(), static_cast<valueType>(*first++));
    }
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::assign(
        std::initializer_list<valueType> list, const allocator &alloc
) {
    this->assign(list.begin(), list.end(), alloc);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::valueType
DataStructure::Vector<T, Allocator>::at(differenceType index) const {
    return (*this)[index];
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::valueType
DataStructure::Vector<T, Allocator>::front() const {
    return *this->alloc.begin();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::valueType
DataStructure::Vector<T, Allocator>::back() const {
    return *(this->alloc.getCursor() - 1);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::pointer
DataStructure::Vector<T, Allocator>::data() & noexcept {
    return this->pointer();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::constPointer
DataStructure::Vector<T, Allocator>::data() const & noexcept {
    return static_cast<pointer>(*this);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::begin() & noexcept {
    return iterator(this->alloc.begin());
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::constIterator
DataStructure::Vector<T, Allocator>::constBegin() const & noexcept {
    return static_cast<Vector *>(*this)->begin();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::end() & noexcept {
    return iterator(this->alloc.getCursor());
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::constIterator
DataStructure::Vector<T, Allocator>::constEnd() const & noexcept {
    return static_cast<Vector *>(*this)->end();
}
template <typename T, typename Allocator>
bool DataStructure::Vector<T, Allocator>::empty() const noexcept {
    return this->alloc.empty();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::sizeType
DataStructure::Vector<T, Allocator>::size() const noexcept {
    return this->alloc.size();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::sizeType
DataStructure::Vector<T, Allocator>::capacity() const noexcept {
    return this->alloc.capacity();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::sizeType
DataStructure::Vector<T, Allocator>::reserve() const noexcept {
    return this->alloc.reserve();
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::resize(sizeType size) {
    return iterator(this->alloc.resize(size));
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator DataStructure::Vector<T, Allocator>::shrinkToFit() {
    return iterator(this->alloc.shrinkToFit());
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::clear()
        noexcept(__DataStructure_typeTraits<valueType>::hasTrivialDestructor()()) {
    this->alloc.destroy(this->alloc.begin(), this->alloc.getCursor());
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(differenceType index, constReference value, sizeType size) {
    if(not size) {
        return iterator(this->alloc.begin() + index);
    }
    if(index == this->size()) {
        while(size--) {
            this->pushBack(value);
        }
        return iterator(this->alloc.begin() + index);
    }
    auto insertPosition {this->insertAuxiliary(index, size)};
    auto cursor {insertPosition};
    while(size--) {
        this->alloc.construct(cursor++, value);
    }
    return iterator(insertPosition);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(differenceType index, rightValueReference value) {
    if(index == this->size()) {
        this->pushBack(value);
        return iterator(this->alloc.begin() + index);
    }
    auto insertPosition {this->insertAuxiliary(index, 1)};
    auto cursor {insertPosition};
    this->alloc.construct(cursor, value);
    return iterator(insertPosition);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(constIterator position, constReference value, sizeType size) {
    return this->insert(position - iterator(this->alloc.begin()), value, size);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(constIterator position, rightValueReference value) {
    return this->insert(position - iterator(this->alloc.begin()), value);
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(
        differenceType index, typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last
) {
    if(first == last) {
        return iterator(this->alloc.begin() + index);
    }
    if(index == this->size) {
        while(first not_eq last) {
            this->pushBack(static_cast<valueType>(*first++));
        }
        return iterator(this->alloc.begin() + index);
    }
    auto size {static_cast<sizeType>(Vector::iteratorDifference(first, last))};
    auto insertPosition {this->insertAuxiliary(index, size)};
    auto cursor {insertPosition};
    while(--size) {
        this->Alloc.construct(cursor++, static_cast<valueType>(*first++));
    }
    return iterator(insertPosition);
}
template <typename T, typename Allocator>
template <typename InputIterator,
        typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(
        constIterator position, typename __DataStructure_isInputIterator<InputIterator>::__result first,
        InputIterator last
) {
    return this->insert(position - iterator(this->alloc.begin()), first, last);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(differenceType index, std::initializer_list<valueType> list) {
    return this->insert(index, list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::insert(constIterator position, std::initializer_list<valueType> list) {
    return this->insert(position, list.begin(), list.end());
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::erase(differenceType index, sizeType size) {
    auto erasePosition {this->alloc.begin() + index};
    if(not size) {
        return iterator(erasePosition);
    }
    if(index + size == this->size()) {
        while(size--) {
            this->popBack();
        }
        return iterator(erasePosition);
    }
    const auto returnPosition {erasePosition};
    auto cursor {erasePosition + size};
    this->alloc.destroy(erasePosition, cursor);
    auto &allocCursor {this->alloc.getCursor()};
    while(cursor < allocCursor) {
        this->alloc.construct(erasePosition++, move(*cursor));
        this->alloc.destroy(cursor++);
    }
    allocCursor = erasePosition;
    return iterator(returnPosition);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::erase(constIterator position, sizeType size) {
    return this->erase(position - iterator(this->alloc.begin()), size);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::erase(constIterator first, constIterator last) {
    return this->erase(first, last - first);
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::pushBack(constReference value) {
    this->alloc.construct(this->alloc.getCursor(), value);
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::pushBack(rightValueReference value) {
    this->alloc.construct(this->alloc.getCursor(), value);
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::pushFront(constReference value) {
    this->insert(0, value);
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::pushFront(rightValueReference value) {
    this->insert(0, value);
}
template <typename T, typename Allocator>
#ifdef POP_GET_OBJECT
typename DataStructure::Vector<T, Allocator>::valueType
#else
void
#endif
DataStructure::Vector<T, Allocator>::popBack() {
#ifdef POP_GET_OBJECT
    auto value {move(*(this->alloc.getCursor() - 1))};
#endif
    this->alloc.destroy(this->alloc.getCursor() - 1);
#ifdef POP_GET_OBJECT
    return value
#endif
}
template <typename T, typename Allocator>
#ifdef POP_GET_OBJECT
typename DataStructure::Vector<T, Allocator>::valueType
#else
void
#endif
DataStructure::Vector<T, Allocator>::popFront() {
#ifdef POP_GET_OBJECT
    auto value {move((*this)[0])};
#endif
    this->erase(0);
#ifdef POP_GET_OBJECT
    return value;
#endif
}
template <typename T, typename Allocator>
template <typename ...Args>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::emplace(differenceType index, Args &&...args) {
    return this->insert(index, valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
template <typename ...Args>
typename DataStructure::Vector<T, Allocator>::iterator
DataStructure::Vector<T, Allocator>::emplace(constIterator position, Args &&...args) {
    return this->insert(position, valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
template <typename ...Args>
void DataStructure::Vector<T, Allocator>::emplaceBack(Args &&...args) {
    this->pushBack(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
template <typename ...Args>
void DataStructure::Vector<T, Allocator>::emplaceFront(Args &&...args) {
    this->pushFront(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator>
void DataStructure::Vector<T, Allocator>::swap(Vector &rhs) noexcept {
    this->alloc.swap(rhs.alloc);
}
template <typename T, typename Allocator>
DataStructure::Vector<T, Allocator>
DataStructure::Vector<T, Allocator>::get(differenceType index, sizeType size) const {
    const auto start {this->begin() + index};
    return Vector(start, start + size);
}
template <typename T, typename Allocator>
typename DataStructure::Vector<T, Allocator>::allocator
DataStructure::Vector<T, Allocator>::getAllocator() const & {
    return this->alloc;
}
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR
typename DataStructure::Vector<T, Allocator>::allocator &
DataStructure::Vector<T, Allocator>::getAllocator() & noexcept {
    return this->alloc;
}
#endif

#endif //DATA_STRUCTURE_VECTOR_HPP
