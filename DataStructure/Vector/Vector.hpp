#ifndef DATA_STRUCTURE_REVECTOR_HPP
#define DATA_STRUCTURE_REVECTOR_HPP

#include "Base.hpp"
#include "Exception.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>>
    class Vector final : private ArrayBase<T, Alloc> {
    private:
        class OutOfRange;
        class EmptyVector;
    public:
        class Iterator final : public RandomAccessIterator {
        public:
            using valueType = T;
            using reference = T &;
            using pointer = T *;
            using constPointer = const T *;
            using constReference = const T &;
            using differenceType = long;
            using sizeType = unsigned long;
        private:
            pointer iterator;
        public:
            Iterator() = delete;
            explicit Iterator(pointer iterator) : iterator(iterator) {}
            Iterator(const Iterator &other) : iterator(other.iterator) {}
            Iterator(Iterator &&other) noexcept : iterator(other.iterator){
                other.iterator = nullptr;
            }
            Iterator &operator=(const Iterator &other) {
                if(this == &other) {
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
            ~Iterator() {
                this->iterator = nullptr;
            }
            reference operator*() {
                return *this->iterator;
            }
            pointer operator->() {
                return this->iterator;
            }
            Iterator &operator++() {
                ++this->iterator;
                return *this;
            }
            Iterator operator++(int) {
                Iterator temp {*this};
                ++*this;
                return temp;
            }
            Iterator &operator--() {
                --this->iterator;
                return *this;
            }
            Iterator operator--(int) {
                Iterator temp {*this};
                --*this;
                return temp;
            }
            bool operator==(const Iterator &other) const {
                return this->iterator == other.iterator;
            }
            bool operator not_eq(const Iterator &other) const {
                return not(*this == other);
            }
            bool operator<(const Iterator &other) const {
                return this->iterator - other.iterator < 0;
            }
            bool operator<=(const Iterator &other) const {
                return *this < other or *this == other;
            }
            bool operator>(const Iterator &other) const {
                return not(*this < other);
            }
            bool operator>=(const Iterator &other) const {
                return *this > other or *this == other;
            }
            Iterator operator+(differenceType n) const {
                auto it {Iterator(this->iterator + n)};
                return it;
            }
            Iterator operator-(differenceType n) const {
                auto it {Iterator(this->iterator - n)};
                return it;
            }
            /*differenceType operator-(const Iterator &other) const {
                return this->iterator - other;
            }*/
            friend differenceType operator-(const Iterator &a, const Iterator &b) {
                return a.iterator - b.iterator;
            }
            reference operator[](differenceType n) {
                return this->iterator[n];
            }
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR_ITERATOR
            T *getIterator() {
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
        pointer backup(differenceType, iteratorReference, sizeType &);
        iterator getIterator(bool, __DataStructure_trueType) const;
        auto getIterator(bool, __DataStructure_falseType) const ->
            decltype(static_cast<Vector<T, Alloc> *>(nullptr)->array.getEnd());
#ifdef OTHER_FUNCTION
        bool findExpand(constReference) const;
        template <typename ...Args>
        bool findExpand(constReference, const Args &...) const;
#endif
    public:
        Vector();
        Vector(sizeType, constReference);
        explicit Vector(sizeType);
        Vector(iterator, iterator);
        Vector(pointer , pointer);
        Vector(std::initializer_list<valueType>);
        explicit Vector(const Alloc &);
        Vector(const Vector &);
        Vector(Vector &&) noexcept;
        ~Vector() = default;
        Vector &operator=(const Vector &);
        Vector &operator=(Vector &&) noexcept;
        reference operator[](differenceType) const &;
        bool operator==(const Vector &) const;
        bool operator not_eq(const Vector &) const;
        bool operator<(const Vector &) const;
        bool operator>(const Vector &) const;
        bool operator<=(const Vector &) const;
        bool operator>=(const Vector &) const;
        explicit operator bool() const;
        Vector &operator+();
        Vector &operator-();
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
        void pushFront(constReference);
        valueType at(differenceType) const;
        bool empty() const;
        void clear();
        sizeType size() const;
        valueType front() const;
        valueType back() const;
        iterator insert(constReference, differenceType, sizeType = 1);
        iterator insert(constReference, constIterator, sizeType = 1);
        template <typename ForwardIterator>
        iterator insert(constIterator, ForwardIterator, ForwardIterator);
        iterator insert(constIterator, std::initializer_list<valueType>);
        template <typename ...Args>
        iterator emplace(differenceType, Args &&...) noexcept;
        template <typename ...Args>
        iterator emplaceBack(Args &&...) noexcept;
        template <typename ...Args>
        iterator emplaceFront(Args &&...) noexcept;
        iterator erase(differenceType, sizeType = 1);
        iterator erase(constIterator);
        iterator erase(constIterator, constIterator);
        auto begin() const ->
            decltype(static_cast<Vector<T, Alloc> *>(nullptr)->getIterator(
                false, typename __DataStructure_isPointer<
                    decltype(static_cast<Vector<T, Alloc> *>(nullptr)->array.getFirst())
                >::result())
            );
        auto end() const ->
            decltype(static_cast<Vector<T, Alloc> *>(nullptr)->getIterator(
                true, typename __DataStructure_isPointer<
                    decltype(static_cast<Vector<T, Alloc> *>(nullptr)->array.getCursor())
                >::result())
            );
        auto constBegin() const -> const decltype(static_cast<Vector<T, Alloc> *>(nullptr)->begin());
        auto constEnd() const -> const decltype(static_cast<Vector<T, Alloc> *>(nullptr)->end());
#ifdef OTHER_FUNCTION
        public:
        iterator find(constReference) const;
        template <typename ...Args>
        bool find(constReference, const Args &...) const;
        Vector get(differenceType, sizeType) const;
        void resize(sizeType);
        void shrinkToFit();
        sizeType reserve() const;
        sizeType capacity() const;
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR
        public:
        allocator *&getAllocator();
        auto &getFirst() -> decltype(this->array.getFirst());
        auto &getCursor() -> decltype(this->array.getCursor());
        auto &getEnd() -> decltype(this->array.getEnd());
        sizeType &getAllocateSize();
#endif
    };
}
template <typename T, typename Alloc>
class DataStructure::Vector<T, Alloc>::OutOfRange : public DataStructure::LogicException {
public:
    explicit OutOfRange(const char *error) : LogicException(error) {}
    explicit OutOfRange(const std::string &error) : LogicException(error) {}
};
template <typename T, typename Alloc>
class DataStructure::Vector<T, Alloc>::EmptyVector : public DataStructure::RuntimeException {
public:
    explicit EmptyVector(const char *error) : RuntimeException(error) {}
    explicit EmptyVector(const std::string &error) : RuntimeException(error) {}
};

template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::pointer
DataStructure::Vector<T, Alloc>::backup(differenceType index, iteratorReference start, sizeType &backupSize) {
    start = iterator(this->array.getFirst() + index);
    iterator end {this->array.getCursor()};
    backupSize = static_cast<sizeType>(end - start);
    auto backupArray {reinterpret_cast<pointer>(::operator new (sizeof(valueType) * backupSize))};
    for(auto i {0}; start not_eq end; ++i) {
        backupArray[i] = *start++;
    }
    for(auto i {0}; i < backupSize; ++i) {
        this->array.destroy(this->array.getCursor() - 1);
    }
    return backupArray;
}
template <typename T, typename Alloc>
inline typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::getIterator(bool isCursor, __DataStructure_trueType) const {
    if(isCursor) {
        return iterator(this->array.getCursor());
    }
    return iterator(this->array.getFirst());
}
template <typename T, typename Alloc>
inline auto DataStructure::Vector<T, Alloc>::getIterator(bool isCursor, __DataStructure_falseType) const ->
        decltype(static_cast<Vector<T, Alloc> *>(nullptr)->array.getEnd()) {
    if(isCursor) {
        return this->array.getCursor();
    }
    return this->array.getFirst();
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector() : ArrayBase<T, Alloc>() {
    this->construct();
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(sizeType size) : ArrayBase<T, Alloc>() {
    this->construct();
    this->checkSize(size);
    using t = typename DataStructure::removeReference<valueType>::type;
    for(auto i {0}; i < size; ++i) {
        this->array.construct(this->array.getCursor(), t());
    }
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(sizeType size, constReference value) : ArrayBase<T, Alloc>() {
    this->construct();
    this->checkSize(size);
    for(auto i {0}; i < size; ++i) {
        this->array.construct(this->array.getCursor(), value);
    }
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(iterator begin, iterator end) : ArrayBase<T, Alloc>() {
    this->construct();
    auto size {end - begin};
    if(size < 0) {
        throw OutOfRange("The begin-iterator is a bad-iterator!");
    }
    this->checkSize(static_cast<sizeType>(size));
    while(begin not_eq end) {
        this->array.construct(this->array.getCursor(), *begin++);
    }
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(pointer begin, pointer end) :
        Vector(iterator(begin), iterator(end)) {

}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(std::initializer_list<valueType> initializerList) : ArrayBase<T, Alloc>() {
    this->construct();
    auto begin {initializerList.begin()};
    auto end {initializerList.end()};
    auto size {end - begin};
    this->checkSize(size);
    while(begin not_eq end) {
        this->array.construct(this->array.getCursor(), *begin++);
    }
};
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(const Vector &other) : ArrayBase<T, Alloc>(other) {

}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(Vector &&other) noexcept : ArrayBase<T, Alloc>(std::move(other)) {

}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::Vector(const Alloc &alloc) {
    this->array = alloc;
    this->allocateSize = static_cast<sizeType>(alloc.getEnd() - alloc.getFirst());
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc> &DataStructure::Vector<T, Alloc>::operator=(const Vector &other) {
    if(&other == this) {
        return *this;
    }
    this->allocateSize = other.allocateSize;
    this->construct();
    this->copy(other);
    return *this;
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc> &DataStructure::Vector<T, Alloc>::operator=(Vector &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->allocateSize = std::move(other.allocateSize);
    this->array = std::move(other.array);
    other.allocateSize = 0;
    other.array = Allocator<T>();
    return *this;
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::reference
DataStructure::Vector<T, Alloc>::operator[](differenceType index) const & {
    if(index >= this->size() or index < 0) {
        throw OutOfRange("Error, The vector index is out of range!");
    }
    return *(this->array.getFirst() + index);
}
template <typename T, typename Alloc>
inline bool DataStructure::Vector<T, Alloc>::operator==(const Vector &other) const {
    auto size {this->size()};
    return size == other.size() and [size](const Vector &a, const Vector &b) -> bool {
        for(auto i {0}; i < size; ++i) {
            if(not(a[i] == b[i])) {
                return false;
            }
        }
        return true;
    }(*this, other);
}
template <typename T, typename Alloc>
bool DataStructure::Vector<T, Alloc>::operator not_eq(const Vector &other) const {
    return not(*this == other);
}
template <typename T, typename Alloc>
inline bool DataStructure::Vector<T, Alloc>::operator<(const Vector &other) const {
    auto thisSize {this->size()};
    auto otherSize {other.size()};
    if(otherSize not_eq thisSize) {
        return thisSize < otherSize;
    }
    return [](const Vector &a, const Vector &b) -> bool {
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
inline bool DataStructure::Vector<T, Alloc>::operator<=(const Vector &other) const {
    return *this < other or *this == other;
}
template <typename T, typename Alloc>
bool DataStructure::Vector<T, Alloc>::operator>(const Vector &other) const {
    return not(*this < other) and not(*this == other);
}
template <typename T, typename Alloc>
bool DataStructure::Vector<T, Alloc>::operator>=(const Vector &other) const {
    return not(*this <= other);
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc>::operator bool() const {
    return not(this->empty());
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc> &DataStructure::Vector<T, Alloc>::operator+() {
    return *this;
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc> &DataStructure::Vector<T, Alloc>::operator-() {
    auto end {this->end()};
    for(auto it {this->begin()}; it not_eq end; ++it) {
        *it = -*it;
    }
    return *this;
}
template <typename T, typename Alloc>
#ifdef POP_GET_OBJECT
typename DataStructure::Vector<T, Alloc>::valueType
#else
void
#endif
DataStructure::Vector<T, Alloc>::popFront() {
#ifdef POP_GET_OBJECT
    if(not this->size()) {
        throw EmptyForwardList("The Forward List is empty!");
    }
    auto returnNumber {(*this)[0]};
#endif
    this->erase(0);
#ifdef POP_GET_OBJECT
    return returnNumber;
#endif
}
template <typename T, typename Alloc>
#ifdef POP_GET_OBJECT
typename DataStructure::Vector<T, Alloc>::valueType
#else
void
#endif
DataStructure::Vector<T, Alloc>::popBack() {
#ifdef POP_GET_OBJECT
    if(not this->size()) {
        throw EmptyForwardList("The Forward List is empty!");
    }
    auto returnNumber {(*this)[this->size() - 1]};
#endif
    this->erase(this->size() - 1);
#ifdef POP_GET_OBJECT
    return returnNumber;
#endif
}
template <typename T, typename Alloc>
void DataStructure::Vector<T, Alloc>::pushFront(constReference value) {
    this->insert(value, 0);
}
template <typename T, typename Alloc>
void DataStructure::Vector<T, Alloc>::pushBack(constReference value) {
    this->array.construct(this->array.getCursor(), value);
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::valueType
DataStructure::Vector<T, Alloc>::at(differenceType index) const {
    return (*this)[index];
}
template <typename T, typename Alloc>
inline bool DataStructure::Vector<T, Alloc>::empty() const {
    return this->size() == 0;
}
template <typename T, typename Alloc>
void DataStructure::Vector<T, Alloc>::clear() {
    this->array = Allocator<T>();
    this->construct();
}
template <typename T, typename Alloc>
inline typename DataStructure::Vector<T, Alloc>::sizeType DataStructure::Vector<T, Alloc>::size() const {
    return static_cast<typename DataStructure::Vector<T, Alloc>::sizeType>(
            this->array.getCursor() - this->array.getFirst()
    );
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::valueType DataStructure::Vector<T, Alloc>::front() const {
    return *this->array.getFirst();
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::valueType DataStructure::Vector<T, Alloc>::back() const {
    return *(this->array.getCursor() - 1);
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::insert(constReference value, differenceType index, sizeType number) {
    auto size {this->size()};
    this->checkSize(size + number);
    if(index == size) {
        for(auto i {0}; i < number; ++i) {
            this->array.construct(this->array.getCursor(), value);
        }
        return iterator(this->array.getCursor() - number);
    }
    iterator start(nullptr);
    sizeType backupSize;
    auto backup {this->backup(index, start, backupSize)};
    for(auto i {0}; i < number; ++i) {
        this->array.construct(this->array.getCursor(), value);
    }
    for(auto i {0}; i < backupSize; ++i) {
        this->array.construct(this->array.getCursor(), backup[i]);
    }
    operator delete (backup);
    backup = nullptr;
    return start;
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::insert(constReference value, constIterator position, sizeType number) {
    auto index {position - iterator(this->array.getFirst())};
    return this->insert(value, index, number);
}
template <typename T, typename Alloc>
template <typename ForwardIterator>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::insert(constIterator position, ForwardIterator begin, ForwardIterator end) {
    auto size {0};
    for(auto i {begin}; i not_eq end; ++i) {
        ++size;
    }
    this->checkSize(size + this->size());
    auto index {position - iterator(this->array.getFirst())};
    iterator start(nullptr);
    sizeType backupSize;
    auto backup {this->backup(index, start, backupSize)};
    for(auto i {0}; i < size; ++i) {
        this->array.construct(this->array.getCursor(), *begin++);
    }
    for(auto i {0}; i < backupSize; ++i) {
        this->array.construct(this->array.getCursor(), backup[i]);
    }
    operator delete (backup);
    backup = nullptr;
    return start;
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::insert(constIterator position, std::initializer_list<valueType> list) {
    auto size {list.size()};
    return this->insert(position, list.begin(), list.end());
}
template <typename T, typename Alloc>
template <typename ...Args>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::emplace(differenceType index, Args &&...args) noexcept {
    auto size {this->size()};
    if(index == size) {
        return this->emplaceBack(std::forward<Args>(args)...);
    }
    this->checkSize(size + 1);
    iterator start(nullptr);
    sizeType backupSize;
    auto backup {this->backup(index, start, backupSize)};
    this->array.construct(this->array.getCursor(), std::forward<Args>(args)...);
    for(auto i {0}; i < backupSize; ++i) {
        this->array.construct(this->array.getCursor(), backup[i]);
    }
    operator delete (backup);
    backup = nullptr;
    return start;
}
template <typename T, typename Alloc>
template <typename ...Args>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::emplaceBack(Args &&...args) noexcept {
    this->checkSize(this->size() + 1);
    this->array.construct(this->array.getCursor(), std::forward<Args>(args)...);
    return iterator(this->array.getCursor() - 2);
}
template <typename T, typename Alloc>
template <typename ...Args>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::emplaceFront(Args &&...args) noexcept {
    return this->emplace(0, std::forward<Args>(args)...);
}
template <typename T, typename Alloc>
inline typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::erase(differenceType index, sizeType size) {
    if(this->empty()) {
        throw EmptyVector("The Vector is empty!");
    }
    auto it {this->begin()};
    auto end {this->end() - 1};
    for(auto i {it + index}; i not_eq end; ++i) {
        *i = *(i + 1);
    }
    this->array.destroy(this->array.getCursor() - 1);
    return it + index;
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::erase(constIterator position) {
    auto index {position - this->begin()};
    return this->erase(index);
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::erase(constIterator begin, constIterator end) {
    auto size {end - begin};
    auto index {begin - this->begin()};
    return this->erase(index, static_cast<sizeType>(size));
}
template <typename T, typename Alloc>
inline auto DataStructure::Vector<T, Alloc>::begin() const ->
        decltype(static_cast<Vector<T, Alloc> *>(nullptr)->getIterator(
            false, typename __DataStructure_isPointer<
                decltype(static_cast<Vector<T, Alloc> *>(nullptr)->array.getFirst())
            >::result())
        ) {
    return this->getIterator(false, typename __DataStructure_isPointer<
                                decltype(static_cast<Vector *>(nullptr)->array.getFirst())
                             >::result());
}
template <typename T, typename Alloc>
inline auto DataStructure::Vector<T, Alloc>::end() const ->
        decltype(static_cast<Vector<T, Alloc> *>(nullptr)->getIterator(
            true, typename __DataStructure_isPointer<
                decltype(static_cast<Vector<T, Alloc> *>(nullptr)->array.getCursor())
            >::result())
        ) {
    return this->getIterator(true, typename __DataStructure_isPointer<
                                decltype(static_cast<Vector *>(nullptr)->array.getCursor())
                             >::result());
}
template <typename T, typename Alloc>
inline auto DataStructure::Vector<T, Alloc>::constBegin() const ->
        const decltype(static_cast<Vector<T, Alloc> *>(nullptr)->begin()) {
    return this->begin();
}
template <typename T, typename Alloc>
inline auto DataStructure::Vector<T, Alloc>::constEnd() const ->
        const decltype(static_cast<Vector<T, Alloc> *>(nullptr)->end()) {
    return this->end();
}
#ifdef OTHER_FUNCTION
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::iterator
DataStructure::Vector<T, Alloc>::find(constReference value) const {
    auto end {this->end()};
    for(auto it {this->begin()}; it not_eq end; ++it) {
        if(*it == value) {
            return it;
        }
    }
    return iterator(this->array.getCursor());
}
template <typename T, typename Alloc>
bool DataStructure::Vector<T, Alloc>::findExpand(constReference value) const {
    return this->find(value) not_eq this->end();
}
template <typename T, typename Alloc>
template <typename ...Args>
bool DataStructure::Vector<T, Alloc>::findExpand(constReference value, const Args &...args) const {
    if(this->findExpand(value)) {
        return this->findExpand(args...);
    }
    return false;
}
template <typename T, typename Alloc>
template <typename ...Args>
bool DataStructure::Vector<T, Alloc>::find(constReference value, const Args &...args) const {
    return this->findExpand(value, args...);
}
template <typename T, typename Alloc>
DataStructure::Vector<T, Alloc> DataStructure::Vector<T, Alloc>::get(differenceType index, sizeType size) const {
    auto start {this->constBegin() + index};
    auto end {start + size};
    return Vector(start, end);
}
template <typename T, typename Alloc>
inline void DataStructure::Vector<T, Alloc>::resize(sizeType size) {
    size = (size + Alloc::ALIGN - 1) & ~(Alloc::ALIGN - 1);
    this->array.resize(size);
}
template <typename T, typename Alloc>
inline void DataStructure::Vector<T, Alloc>::shrinkToFit() {
    this->array.shrinkToFit();
}
template <typename T, typename Alloc>
inline typename DataStructure::Vector<T, Alloc>::sizeType DataStructure::Vector<T, Alloc>::reserve() const {
    return this->array().getEnd() - this->array.getCursor();
}
template <typename T, typename Alloc>
inline typename DataStructure::Vector<T, Alloc>::sizeType DataStructure::Vector<T, Alloc>::capacity() const {
    return this->array().getEnd() - this->array.getFirst();
}
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR
template <typename T, typename Alloc>
inline typename DataStructure::Vector<T, Alloc>::allocator *&DataStructure::Vector<T, Alloc>::getAllocator() {
    return this->array;
}
template <typename T, typename Alloc>
inline auto &DataStructure::Vector<T, Alloc>::getFirst() -> decltype(this->array.getFirst()) {
    return this->array.getFirst();
}
template <typename T, typename Alloc>
inline auto &DataStructure::Vector<T, Alloc>::getCursor() -> decltype(this->array.getCursor()) {
    return this->array.getCursor();
}
template <typename T, typename Alloc>
inline auto &DataStructure::Vector<T, Alloc>::getEnd() -> decltype(this->array.getEnd()) {
    return this->array.getEnd();
}
template <typename T, typename Alloc>
typename DataStructure::Vector<T, Alloc>::sizeType &DataStructure::Vector<T, Alloc>::getAllocateSize() {
    return this->allocateSize;
}
#endif

#endif //DATA_STRUCTURE_REVECTOR_HPP
