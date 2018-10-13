#ifndef DATA_STRUCTURE_ALLOCATOR_HPP
#define DATA_STRUCTURE_ALLOCATOR_HPP

#include "Exception.hpp"
#include "TypeTraits.hpp"

namespace DataStructure {
    template <typename T>
    class Allocator {
    private:
        class BadPointer;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = valueType &;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = valueType *;
        using constPointer = const valueType *;
    public:
        using __DataStructure_isForwardAllocator = __DataStructure_trueType;
        using __DataStructure_isReverseAllocator = __DataStructure_falseType;
    private:
        sizeType allocateSize;
        pointer first;
        pointer cursor;
    private:
        static char *chunk;
        static char *chunk_cursor;
    private:
        static void destroy(void *, __DataStructure_falseType);
        static void destroy(void *, __DataStructure_trueType) noexcept;
        static void destroy(void *, void *, __DataStructure_falseType);
        static void destroy(const void *, const void *, __DataStructure_trueType) noexcept;
    public:
        static void *operator new (sizeType);
        static void operator delete (void *) noexcept;
        static void destroy(void *) noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
        static void destroy(void *, const void *) noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
    private:
        void copyRHS(const Allocator &);
        void free(pointer) noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
        void reallocate();
        void check(pointer) const;
    public:
        constexpr Allocator();
        Allocator(const Allocator &);
        Allocator(Allocator &&) noexcept;
        ~Allocator();
    public:
        Allocator &operator=(const Allocator &) &;
        Allocator &operator=(Allocator &&) & noexcept;
        bool operator==(const Allocator &) const;
        bool operator!=(const Allocator &) const;
        bool operator<(const Allocator &) const = delete;
        bool operator<=(const Allocator &) const = delete;
        bool operator>(const Allocator &) const = delete;
        bool operator>=(const Allocator &) const = delete;
        explicit operator bool() const noexcept;
    public:
        pointer allocate(sizeType = 64) &;
        pointer construct(pointer, constReference) & noexcept(
                    static_cast<bool>(
                            typename __DataStructure_TypeTraits<valueType>::hasTrivialDefaultConstructor()
                    )
                );
        pointer construct(pointer, rightValueReference) & noexcept(
                    static_cast<bool>(
                            typename __DataStructure_TypeTraits<valueType>::hasTrivialDefaultConstructor()
                    )
                );
        template <typename ...Args>
        pointer construct(pointer, Args &&...) &;
        pointer destroy(pointer) & noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
        pointer destroy(pointer, constPointer) & noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
        bool full() const & noexcept;
        bool empty() const & noexcept;
        sizeType size() const & noexcept;
        sizeType capacity() const & noexcept;
        sizeType reserve() const & noexcept;
        pointer begin() const & noexcept;
        constPointer getCursor() const & noexcept;
        pointer &getCursor() & noexcept;
        constPointer end() const & noexcept;
        pointer resize(sizeType) &;
        pointer shrinkToFit() &;
        void swap(Allocator &) noexcept;
        pointer clear() & noexcept(
                    static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
                );
#ifdef DEBUG_DATA_STRUCTURE_FOR_ALLOCATOR
    public:
        sizeType &getAllocateSize() & noexcept;
        pointer &getFirst() & noexcept;
        pointer &getCursor() & noexcept;
#endif
    };
    template <typename T>
    void swap(Allocator<T> &, Allocator<T> &) noexcept;
}

template <typename T>
class DataStructure::Allocator<T>::BadPointer : public DataStructure::RuntimeException {
public:
    explicit BadPointer(const char *error) : RuntimeException(error) {}
    explicit BadPointer(const std::string &error) : RuntimeException(error) {}
};

template <typename T>
void DataStructure::swap(Allocator<T> &lhs, Allocator<T> &rhs) noexcept {
    lhs.swap(rhs);
}
template <typename T>
inline void DataStructure::Allocator<T>::destroy(void *p, __DataStructure_falseType) {
    reinterpret_cast<pointer>(p)->valueType();
}
template <typename T>
inline void DataStructure::Allocator<T>::destroy(void *, __DataStructure_trueType) noexcept {}
template <typename T>
inline void
DataStructure::Allocator<T>::destroy(const void *, const void *, __DataStructure_trueType) noexcept {}
template <typename T>
inline void DataStructure::Allocator<T>::destroy(void *first, void *last, __DataStructure_falseType) {
    --reinterpret_cast<pointer>(last);
    reinterpret_cast<pointer>(first)->~valueType();
    while(first not_eq last) {
        reinterpret_cast<pointer>(last)--->~valueType();
    }
}
template <typename T>
inline void DataStructure::Allocator<T>::copyRHS(const Allocator<T> &rhs) {
    for(auto cursor {rhs.first}; cursor not_eq rhs.cursor;) {
        new (this->cursor++) valueType(*cursor++);
    }
}
template <typename T>
inline void DataStructure::Allocator<T>::free(pointer p) noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
    if(not p) {
        return;
    }
    Allocator::destroy(
            p, this->cursor, typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
    );
    Allocator::operator delete (p);
}
template <typename T>
inline void DataStructure::Allocator<T>::reallocate() {
    auto newFirst {reinterpret_cast<pointer>(
                        Allocator::operator new (sizeof(valueType) * this->allocateSize)
                  )};
    auto cursor {this->first};
    for(auto i {0}; cursor not_eq this->cursor;) {
        new (newFirst + i++) valueType(move(*cursor++));
    }
    const auto size {this->cursor - this->first};
    this->free(this->first);
    this->first = newFirst;
    this->cursor = this->first + size;
}
template <typename T>
inline void DataStructure::Allocator<T>::check(pointer p) const {
    if(p - this->first < 0 or p - this->end() >= 0) {
        throw BadPointer("The pointer is not allocated by Allocator!");
    }
}
template <typename T>
inline void *DataStructure::Allocator<T>::operator new (sizeType size) {
    return ::operator new (size);
}
template <typename T>
inline void DataStructure::Allocator<T>::operator delete (void *p) noexcept {
    ::operator delete (p);
}
template <typename T>
void DataStructure::Allocator<T>::destroy(void *p) noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
    Allocator::destroy(p, typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor());
}
template <typename T>
void DataStructure::Allocator<T>::destroy(void *first, const void *last) noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
    Allocator::destroy(first, last, typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor());
}
template <typename T>
constexpr DataStructure::Allocator<T>::Allocator() : allocateSize {0}, first {nullptr},
        cursor {nullptr} {}
template <typename T>
DataStructure::Allocator<T>::Allocator(const Allocator<T> &rhs) : allocateSize {rhs.allocateSize},
        first {reinterpret_cast<pointer>(Allocator::operator new (sizeof(valueType) * this->allocateSize))},
        cursor {this->first} {
    this->copyRHS(rhs);
}
template <typename T>
DataStructure::Allocator<T>::Allocator(Allocator<T> &&rhs) noexcept : allocateSize {rhs.allocateSize},
        first {rhs.first}, cursor {rhs.cursor} {
    rhs.first = nullptr;
}
template <typename T>
DataStructure::Allocator<T>::~Allocator() {
    this->free(this->first);
}
template <typename T>
DataStructure::Allocator<T> &DataStructure::Allocator<T>::operator=(const Allocator &rhs) & {
    auto temp {this->first};
    this->first = reinterpret_cast<pointer>(Allocator::operator new (sizeof(valueType) * rhs.allocateSize));
    this->free(temp);
    this->cursor = this->first;
    this->allocateSize = rhs.allocateSize;
    this->copyRHS(rhs);
    return *this;
}
template <typename T>
DataStructure::Allocator<T> &DataStructure::Allocator<T>::operator=(Allocator &&rhs) & noexcept {
    if(&rhs == this) {
        return *this;
    }
    this->free(this->first);
    this->first = rhs.first;
    this->allocateSize = rhs.allocateSize;
    this->cursor = rhs.cursor;
    rhs.first = nullptr;
    return *this;
}
template <typename T>
bool DataStructure::Allocator<T>::operator==(const Allocator &rhs) const {
    if(this->allocateSize not_eq rhs.allocateSize or this->size() not_eq rhs.size()) {
        return false;
    }
    auto lhsCursor {this->first};
    auto rhsCursor {rhs.first};
    while(lhsCursor not_eq this->cursor) {
        if(*lhsCursor++ not_eq *rhsCursor++) {
            return false;
        }
    }
    return true;
}
template <typename T>
bool DataStructure::Allocator<T>::operator!=(const Allocator &rhs) const {
    return not *this == rhs;
}
template <typename T>
DataStructure::Allocator<T>::operator bool() const noexcept {
    return this->allocateSize not_eq static_cast<sizeType>(0);
}
template <typename T>
typename DataStructure::Allocator<T>::pointer DataStructure::Allocator<T>::allocate(sizeType size) & {
    if(not size) {
        size = sizeof(valueType) < 128 ? 64 : 8;
    }
    if(this->first) {
        if(size <= this->allocateSize) {
            return this->first;
        }
        this->resize(size);
        return this->first;
    }
    this->allocateSize = size;
    this->first = reinterpret_cast<pointer>(
            Allocator::operator new (sizeof(valueType) * this->allocateSize)
    );
    this->cursor = this->first;
    return this->first;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer
DataStructure::Allocator<T>::construct(pointer p, constReference value) & noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDefaultConstructor())
        ) {
    this->check(p);
    new (p) valueType(value);
    if(p == this->cursor) {
        ++this->cursor;
    }
    return this->cursor;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer
DataStructure::Allocator<T>::construct(pointer p, rightValueReference value) & noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDefaultConstructor())
        ) {
    this->check(p);
    new (p) valueType(move(value));
    if(p == this->cursor) {
        ++this->cursor;
    }
    return this->cursor;
}
template <typename T>
template <typename ...Args>
typename DataStructure::Allocator<T>::pointer
DataStructure::Allocator<T>::construct(pointer p, Args &&...args) & {
    return this->construct(p, valueType(std::forward<Args>(args)...));
}
template <typename T>
typename DataStructure::Allocator<T>::pointer
DataStructure::Allocator<T>::destroy(pointer p) & noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
    Allocator::destroy(p, typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor());
    if(this->cursor - 1 == p) {
        --this->cursor;
    }
    return this->cursor;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer
DataStructure::Allocator<T>::destroy(pointer first, constPointer last) & noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
    Allocator::destroy(first, last, typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor());
    if(this->cursor == last) {
        this->cursor = first;
    }
    return this->cursor;
}
template <typename T>
bool DataStructure::Allocator<T>::full() const & noexcept {
    return this->cursor - this->first == static_cast<differenceType>(this->allocateSize);
}
template <typename T>
inline bool DataStructure::Allocator<T>::empty() const & noexcept {
    return this->cursor == this->first;
}
template <typename T>
typename DataStructure::Allocator<T>::sizeType DataStructure::Allocator<T>::size() const & noexcept {
    return static_cast<sizeType>(this->cursor - this->first);
}
template <typename T>
typename DataStructure::Allocator<T>::sizeType DataStructure::Allocator<T>::capacity() const & noexcept {
    return this->allocateSize;
}
template <typename T>
typename DataStructure::Allocator<T>::sizeType DataStructure::Allocator<T>::reserve() const & noexcept {
    return static_cast<sizeType>(this->end() - this->cursor);
}
template <typename T>
typename DataStructure::Allocator<T>::pointer DataStructure::Allocator<T>::begin() const & noexcept {
    return this->first;
}
template <typename T>
typename DataStructure::Allocator<T>::constPointer DataStructure::Allocator<T>::getCursor() const & noexcept{
    return this->cursor;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer &DataStructure::Allocator<T>::getCursor() & noexcept {
    return this->cursor;
}
template <typename T>
inline typename DataStructure::Allocator<T>::constPointer
DataStructure::Allocator<T>::end() const & noexcept {
    return this->first + static_cast<differenceType>(this->allocateSize);
}
template <typename T>
typename DataStructure::Allocator<T>::pointer DataStructure::Allocator<T>::resize(sizeType size) & {
    if(size <= this->allocateSize) {
        return this->first;
    }
    this->allocateSize = size;
    this->reallocate();
    return this->first;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer DataStructure::Allocator<T>::shrinkToFit() & {
    auto size {this->size()};
    if(size == this->allocateSize) {
        return this->first;
    }
    this->allocateSize = size;
    this->reallocate();
    return this->first;
}
template <typename T>
void DataStructure::Allocator<T>::swap(Allocator &rhs) noexcept {
    using std::swap;
    swap(this->allocateSize, rhs.allocateSize);
    swap(this->first, rhs.first);
    swap(this->cursor, rhs.cursor);
}
template <typename T>
typename DataStructure::Allocator<T>::pointer DataStructure::Allocator<T>::clear() & noexcept(
            static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
    if(this->empty()) {
        return this->cursor;
    }
    Allocator::destroy(
            this->first, this->cursor, typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor()
    );
    this->cursor = this->first;
    return this->cursor;
}
#ifdef DEBUG_DATA_STRUCTURE_FOR_ALLOCATOR
template <typename T>
typename DataStructure::Allocator<T>::sizeType &DataStructure::Allocator<T>::getAllocateSize() & noexcept {
    return this->allocateSize;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer &DataStructure::Allocator<T>::getFirst() & noexcept {
    return this->first;
}
template <typename T>
typename DataStructure::Allocator<T>::pointer &DataStructure::Allocator<T>::getCursor() & noexcept {
    return this->cursor;
}
#endif

#endif //DATA_STRUCTURE_ALLOCATOR_HPP
