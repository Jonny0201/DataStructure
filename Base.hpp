#ifndef DATA_STRUCTURE_BASE_HPP
#define DATA_STRUCTURE_BASE_HPP

#include <iostream>
#include "TypeTraits.hpp"
#include <cmath>

namespace DataStructure {
    template <typename T> class Allocator;
    template <typename T, typename Alloc>
    struct ArrayBase {
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
        using allocator = Alloc;
    protected:
        mutable sizeType allocateSize {50};
        Alloc array;
    protected:
        ArrayBase() : array() {}
        ArrayBase(const ArrayBase &other) : allocateSize(other.allocateSize) {
            this->construct();
            this->copy(other);
        }
        ArrayBase(ArrayBase &&other) noexcept : array(std::move(other.array)), allocateSize(std::move(other.allocateSize)) {
            other.array = Allocator<valueType>();
        }
        void checkSize(sizeType size) {
            const auto times {static_cast<double>(size) / static_cast<double>(this->allocateSize)};
            if(times <= 1) {
                return;
            }
            this->allocateSize *= std::ceil(times);
            this->array.resize(static_cast<typename Allocator<T>::sizeType>(this->allocateSize));
        }
        void construct() {
            this->array.allocate(static_cast<typename Allocator<T>::sizeType>(this->allocateSize));
        }
        void copy(const ArrayBase &other) {
            auto end {other.array.getCursor()};
            for(auto cursor {other.array.getFirst()}; cursor not_eq end; ++cursor) {
                this->array.construct(this->array.getCursor(), *cursor);
            }
            end = nullptr;
        }
        friend void swap(ArrayBase &a, ArrayBase &b) {
            using std::swap;
            swap(a.allocateSize, b.allocateSize);
            swap(a.array, b.array);
        }
    };

    /* Allocator */
    template <typename T>
    class Allocator final {
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
        using referenceToPointer = pointer &;
    private:
        sizeType size;
        pointer first;
        pointer cursor;
        pointer end;
        void free() {
            while(this->first not_eq this->cursor) {
                this->destroy(this->cursor - 1);
            }
            operator delete (this->first);
            this->first = this->cursor = this->end = nullptr;
        }
        void checkPointer(pointer first, pointer end, pointer p) {
            if([](pointer first, pointer end, pointer p) -> bool {
                std::less<pointer> less;
                std::greater_equal<pointer> ge;
                return ge(p, end) and less(p, first);
            }(this->first, this->end, p)) {
                throw BadPointer("The argument pointer isn't allocated by Allocate!");
            }
        }
        void reallocate() {
            const auto backupSize {this->cursor - this->first};
            if(not backupSize) {
                return;
            }
            auto backup {static_cast<pointer>(::operator new (sizeof(valueType) * backupSize))};
            auto backupCursor {this->first};
            for(auto i {0}; backupCursor not_eq this->cursor; ++i) {
                backup[i] = *backupCursor++;
            }
            this->free();
            this->allocate(this->size);
            for(auto i {0}; i < backupSize; ++i) {
                *this->cursor++ = *(backup + i);
            }
            ::operator delete (backup);
            backup = backupCursor = nullptr;
        }
    private:
        class BadPointer final : public std::out_of_range {
        public:
            explicit BadPointer(const char *error) : out_of_range(error) {}
            explicit BadPointer(const std::string &error) : out_of_range(error) {}
        };
    public:
        constexpr Allocator() : size(0), first(nullptr), cursor(nullptr), end(nullptr) {

        }
        Allocator(const Allocator &other) : size(other.size), first(other.first), cursor(other.cursor), end(other.end) {

        }
        Allocator(Allocator &&other) noexcept :
                size(std::move(other.size)), first(std::move(other.first)),
                cursor(std::move(other.cursor)), end(std::move(other.end)) {
            other.size = 0;
            other.first = other.cursor = other.end = nullptr;
        }
        Allocator &operator=(const Allocator &other) & {
            if(&other == this) {
                return *this;
            }
            this->free();
            this->size = other.size;
            this->first = other.first;
            this->cursor = other.cursor;
            this->end = other.end;
            return *this;
        }
        Allocator &operator=(Allocator &&other) & noexcept {
            if(&other == this) {
                return *this;
            }
            this->free();
            this->size = std::move(other.size);
            this->first = std::move(other.first);
            this->cursor = std::move(other.cursor);
            this->end = std::move(other.end);
            other.size = 0;
            other.first = other.cursor = other.end = nullptr;
            return *this;
        }
        ~Allocator() {
            this->free();
        }
        explicit operator bool() const {
            return this->size > 0;
        }
        friend void swap(Allocator &a, Allocator &b) {
            if(&a == &b) {
                return;
            }
            using std::swap;
            swap(a.size, b.size);
            swap(a.first, b.first);
            swap(a.cursor, b.cursor);
            swap(a.end, b.end);
        }
        pointer allocate(sizeType size) & {
            this->size = size;
            if(this->first) {
                this->reallocate();
                return this->first;
            }
            this->first = static_cast<valueType *>(::operator new(static_cast<size_t>(sizeof(valueType) * this->size)));
            if(!this->first) {
                throw BadPointer("Fail to allocate the memory!");
            }
            this->cursor = this->first;
            this->end = this->first + this->size;
            return this->first;
        }
        pointer construct(referenceToPointer p, constReference object) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) valueType(object);
            return p;
        }
        template <typename ...Args>
        pointer construct(referenceToPointer p, const Args &...args) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) valueType(args...);
            return p;
        }
        pointer construct(referenceToPointer p, rightValueReference object) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) valueType(std::move(object));
            return p;
        }
        pointer destroy(pointer p) & {
            this->checkPointer(this->first, this->end, p);
            using t = typename removePointer<pointer>::type;
            p->~t();
            if([&]() -> bool {
                std::greater_equal<pointer> ge;
                return ge(this->cursor - 1, this->first) and this->cursor - 1 == p;
            }()) {
                --this->cursor;
            }
            return p;
        }
        bool full() const & {
            return this->cursor == this->end;
        }
        bool empty() const {
            return this->first == this->cursor;
        }
        sizeType getSize() const & {
            return this->size;
        }
        pointer getFirst() const & {
            return this->first;
        }
        pointer getCursor() const & {
            return this->cursor;
        }
        referenceToPointer getCursor() & {
            return this->cursor;
        }
        pointer getEnd() const & {
            return this->end;
        }
        void resetSize(sizeType size) {
            this->size = size;
        }
        pointer resize(sizeType size) & {
            if(this->size > size) {
                return this->first;
            }
            this->size = size;
            this->reallocate();
            return this->first;
        }
        pointer shrinkToFit() & {
            differenceType diff {this->cursor - this->first};
            if(not diff) {
                return this->first;
            }
            this->size = static_cast<sizeType>(diff);
            this->reallocate();
            return this->first;
        }
#ifdef OTHER_FUNCTION
    public:
        BadPointer getBadPointer(const char *error) {
            return BadPointer(error);
        }
        BadPointer getBadPointer(const std::string &error) {
            return BadPointer(error);
        }
#endif
    };
}

#endif //DATA_STRUCTURE_BASE_HPP
