#ifndef DATA_STRUCTURE_BASE_HPP
#define DATA_STRUCTURE_BASE_HPP

#include <iostream>
#include "TypeTraits.hpp"
#include <cmath>
#include "Exception.hpp"

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
        mutable sizeType allocateSize {64};
        Alloc array;
    protected:
        ArrayBase() : array() {}
        ArrayBase(const ArrayBase &other) : allocateSize(other.allocateSize) {
            this->construct();
            this->copy(other);
        }
        ArrayBase(ArrayBase &&other) noexcept :
                array(std::move(other.array)), allocateSize(std::move(other.allocateSize)) {
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
        }
        friend inline void swap(ArrayBase &a, ArrayBase &b) {
            using std::swap;
            swap(a.allocateSize, b.allocateSize);
            swap(a.array, b.array);
        }
    };

    /* Allocator */
    template <typename T>
    class Allocator {
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
    public:
        enum {
            ALIGN = 8
        };
    protected:
        sizeType size;
        pointer first;
        pointer cursor;
        pointer end;
        virtual void free() noexcept {
            while(this->first not_eq this->cursor) {
                this->destroy(this->cursor - 1);
            }
            ::operator delete (this->first);
        }
        virtual void checkPointer(pointer first, pointer end, pointer p) const {
            if([](pointer first, pointer end, pointer p) -> bool {
                return std::greater_equal<pointer>()(p, end) and std::less<pointer>()(p, first);
            }(this->first, this->end, p)) {
                throw BadPointer("The argument pointer isn't allocated by Allocate!");
            }
        }
        virtual void reallocate() {
            const auto backupSize {this->cursor - this->first};
            if(not backupSize) {
                return;
            }
            auto backup {reinterpret_cast<pointer>(::operator new (sizeof(valueType) * backupSize))};
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
        }
    private:
        class BadPointer final : public RuntimeException {
        public:
            explicit BadPointer(const char *error) : RuntimeException(error) {}
            explicit BadPointer(const std::string &error) : RuntimeException(error) {}
        };
        class BadAllocate final : public Exception {
        public:
            explicit BadAllocate(const char *error) : Exception(error) {}
            explicit BadAllocate(const std::string &error) : Exception(error) {}
        };
    public:
        static void *operator new(sizeType size) {
            if(void *p {std::malloc(size)}) {
                return p;
            }
            throw BadAllocate("Bad Allocate!");
        }
        static void operator delete(void *p) noexcept {
            std::free(p);
        }
    public:
        constexpr Allocator() : size(0), first(nullptr), cursor(nullptr), end(nullptr) {

        }
        Allocator(const Allocator &other) :
                size(other.size), first(other.first), cursor(other.cursor), end(other.end) {

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
        virtual ~Allocator() {
            this->free();
        }
        virtual explicit operator bool() const {
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
        virtual pointer allocate(sizeType size) & {
            this->size = size;
            if(this->first) {
                this->reallocate();
                return this->first;
            }
            this->first = reinterpret_cast<valueType *>(
                    ::operator new (static_cast<size_t>(sizeof(valueType) * this->size))
            );
            if(!this->first) {
                throw BadPointer("Fail to allocate the memory!");
            }
            this->cursor = this->first;
            this->end = this->first + this->size;
            return this->first;
        }
        virtual pointer construct(referenceToPointer p, constReference object) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) valueType(object);
            return p;
        }
        template <typename ...Args>
        pointer construct(referenceToPointer p, Args &&...args) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) valueType(std::forward<Args>(args)...);
            return p;
        }
        virtual pointer construct(referenceToPointer p, rightValueReference object) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) valueType(std::move(object));
            return p;
        }
        virtual pointer destroy(pointer p) & {
            this->checkPointer(this->first, this->end, p);
            p->~valueType();
            if([&]() -> bool {
                return std::greater_equal<pointer>()(this->cursor - 1, this->first) and
                       this->cursor - 1 == p;
            }()) {
                --this->cursor;
            }
            return p;
        }
        virtual bool full() const & {
            return this->cursor == this->end;
        }
        virtual bool empty() const {
            return this->first == this->cursor;
        }
        sizeType maxSize() const {
            return this->size;
        }
        virtual sizeType usedSize() const {
            return this->cursor - this->first;
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
        void resetSize(sizeType size) & {
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
    template <typename T>
    class AllocatorReverse : public Allocator<T> {
        friend inline void swap(AllocatorReverse<T> &a, AllocatorReverse<T> &b) {
            swap(dynamic_cast<Allocator<T> &>(a), dynamic_cast<Allocator<T> &>(b));
        }
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
        using referenceToPointer = pointer &;
    private:
        class BadPointer final : public RuntimeException {
        public:
            explicit BadPointer(const char *error) : RuntimeException(error) {}
            explicit BadPointer(const std::string &error) : RuntimeException(error) {}
        };
        class BadAllocate final : public Exception {
        public:
            explicit BadAllocate(const char *error) : Exception(error) {}
            explicit BadAllocate(const std::string &error) : Exception(error) {}
        };
    private:
        class ReverseIterator final : public RandomAccessIterator {
        private:
            pointer iterator;
        public:
            ReverseIterator() = delete;
            explicit ReverseIterator(pointer p) : iterator {p} {}
            ReverseIterator(const ReverseIterator &other) : iterator {other.iterator} {}
            ReverseIterator(ReverseIterator &&other) noexcept : iterator {other.iterator} {
                other.iterator = nullptr;
            }
            ReverseIterator &operator=(const ReverseIterator &other) {
                if(&other == this) {
                    return *this;
                }
                this->iterator = other.iterator;
                return *this;
            }
            ReverseIterator &operator=(ReverseIterator &&other) noexcept {
                if(&other == this) {
                    return *this;
                }
                this->iterator = other.iterator;
                other.iterator = nullptr;
                return *this;
            }
            pointer operator->() {
                return this->iterator;
            }
            constPointer operator->() const {
                return this->iterator;
            }
            reference operator*() {
                return *this->iterator;
            }
            constReference operator*() const {
                return *this->iterator;
            }
            ReverseIterator &operator++() {
                --this->iterator;
                return *this;
            }
            ReverseIterator operator++(int) {
                ReverseIterator temp {*this};
                ++*this;
                return temp;
            }
            ReverseIterator &operator--() {
                ++this->iterator;
                return *this;
            }
            ReverseIterator operator--(int) {
                ReverseIterator temp {*this};
                --*this;
                return temp;
            }
            ReverseIterator operator+(long n) {
                return ReverseIterator(this->iterator -= n);
            }
            ReverseIterator operator-(long n) {
                return ReverseIterator(this->iterator += n);
            }
            ReverseIterator &operator+=(long n) {
                this->iterator -= n;
                return *this;
            }
            ReverseIterator &operator-=(long n) {
                this->iterator += n;
                return *this;
            }
            reference operator[](long n) {
                if(n >= 0) {
                    return *(this->iterator - n);
                }
                return *(this->iterator + n);
            }
            bool operator==(const ReverseIterator &other) const {
                return this->iterator == other.iterator;
            }
            bool operator not_eq(const ReverseIterator &other) const {
                return not(*this == other);
            }
            bool operator<(const ReverseIterator &other) const {
                return [&]() -> bool {
                    return std::greater<T *>()(this->iterator, other.iterator);
                }();
            }
            bool operator<=(const ReverseIterator &other) const {
                return *this < other or *this == other;
            }
            bool operator>(const ReverseIterator &other) const {
                return not(*this < other);
            }
            bool operator>=(const ReverseIterator &other) const {
                return *this > other or *this == other;
            }
            explicit operator pointer() const {
                return this->iterator;
            }
        };
    protected:
        void free() noexcept override {
            while(this->first not_eq this->cursor) {
                this->destroy(this->cursor + 1);
            }
            this->first = this->end;
            //::operator delete (this->end);
        }
        void checkPointer(pointer first, pointer end, pointer p) const override {
            if([](pointer first, pointer end, pointer p) -> bool {
                return std::less<pointer>()(p, end) and std::greater_equal<pointer>()(p, first);
            }(this->first, this->end, p)) {
                throw BadPointer("The argument pointer isn't allocated by Allocate!");
            }
        }
        void reallocate() override {
            const auto backupSize {this->first - this->cursor};
            if(not backupSize) {
                return;
            }
            auto backup {reinterpret_cast<pointer>(::operator new (sizeof(valueType) * backupSize))};
            auto backupCursor {this->first};
            for(auto i {0}; backupCursor not_eq this->cursor; ++i) {
                backup[i] = *backupCursor--;
            }
            this->free();
            this->allocate(this->size);
            for(auto i {0}; i < backupSize; ++i) {
                *this->cursor-- = *(backup + i);
            }
            ::operator delete (backup);
        }
    public:
        using Allocator<T>::Allocator;
        using Allocator<T>::operator=;
        ~AllocatorReverse() override {
            this->free();
        }
        pointer allocate(sizeType size) & override {
            this->size = size;
            if(this->first) {
                this->reallocate();
                return this->first;
            }
            this->end = reinterpret_cast<pointer>(
                    ::operator new (static_cast<size_t>(this->size * sizeof(valueType)))
            );
            if(not this->end) {
                throw BadPointer("Fail to allocate the memory!");
            }
            this->cursor = this->first = this->end + this->size - 1;
            return this->first;
        }
        pointer construct(referenceToPointer p, constReference value) & override {
            this->checkPointer(this->first, this->end, p);
            new (p--) valueType(value);
            return p;
        }
        template <typename ...Args>
        pointer construct(referenceToPointer p, Args &&...args) & {
            this->checkPointer(this->first, this->end, p);
            new (p--) valueType(std::forward<Args>(args)...);
            return p;
        }
        pointer construct(referenceToPointer p, rightValueReference value) & override {
            this->checkPointer(this->first, this->end, p);
            new (p--) valueType(std::move(value));
            return p;
        }
        ReverseIterator construct(ReverseIterator rIt, constReference value) & {
            this->checkPointer(this->first, this->end, static_cast<pointer>(rIt));
            new (static_cast<pointer>(rIt)) valueType(value);
            if(static_cast<pointer>(rIt) == this->cursor) {
                --this->cursor;
            }
            return rIt - 1;
        }
        template <typename ...Args>
        ReverseIterator construct(ReverseIterator rIt, Args &&...args) & {
            this->checkPointer(this->first, this->end, static_cast<pointer>(rIt));
            new (static_cast<pointer>(rIt)) valueType(std::forward<Args>(args)...);
            if(static_cast<pointer>(rIt) == this->cursor) {
                --this->cursor;
            }
            return rIt - 1;
        }
        ReverseIterator construct(ReverseIterator rIt, rightValueReference value) & {
            this->checkPointer(this->first, this->end, static_cast<pointer>(rIt));
            new (static_cast<pointer>(rIt)) valueType(std::move(value));
            if(static_cast<pointer>(rIt) == this->cursor) {
                --this->cursor;
            }
            return rIt - 1;
        }
        pointer destroy(pointer p) & override {
            this->checkPointer(this->first, this->end, p);
            p->~valueType();
            if([&]() -> bool {
                return std::less_equal<pointer>()(this->cursor + 1, this->first) and
                       this->cursor + 1 == p;
            }()) {
                ++this->cursor;
            }
            return p;
        }
        sizeType usedSize() const override {
            return this->first - this->cursor;
        }
        const ReverseIterator getFirst() const & {
            return ReverseIterator(this->first);
        }
        const ReverseIterator getCursor() const & {
            return ReverseIterator(this->cursor);
        };
        ReverseIterator getCursor() & {
            return ReverseIterator(this->cursor);
        }
        const ReverseIterator getEnd() const & {
            return ReverseIterator(this->end);
        }
    };
}

#endif //DATA_STRUCTURE_BASE_HPP
