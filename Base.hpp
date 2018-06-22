#ifndef DATA_STRUCTURE_BASE_HPP
#define DATA_STRUCTURE_BASE_HPP

#include <iostream>

namespace DataStructure {
    template <typename T>
    class ArrayBase {
    public:
        typedef T type;
        typedef const T constType;
        typedef T & reference;
        typedef const T & constReference;
        typedef T * pointer;
        typedef const T * constPointer;
        typedef const T *const constPointerConstant;
        typedef T && rValueReference;
    protected:
        mutable ptrdiff_t allocateSize {50};
        std::allocator<T> array;
        T *first {nullptr};
        T *cursor {nullptr};
        T *end {nullptr};
        virtual bool checkFull() const = 0;
        virtual void reallocate() = 0;
        virtual void free() = 0;
        virtual void allocate() = 0;
    };
    
    template <typename T>
    class Allocator final {
    public:
        using differenceType = ptrdiff_t;
        using sizeType = size_t;
        using type = T;
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
            if(this->cursor == p) {
                ++this->cursor;
            }
        }
        void reallocate() {
            const auto backupSize {this->cursor - this->first};
            if(not backupSize) {
                return;
            }
            auto backup {new type[backupSize]};
            auto backupCursor {this->first};
            for(auto i {0}; backupCursor not_eq this->cursor; ++i) {
                backup[i] = *backupCursor++;
            }
            this->free();
            this->allocate(this->size);
            for(auto i {0}; i < backupSize; ++i) {
                *this->cursor++ = *(backup + i);
            }
            delete[] backup;
            backup = backupCursor = nullptr;
        }
    private:
        class BadPointer final : public std::out_of_range {
        public:
            explicit constexpr BadPointer(const char *error) : out_of_range(error) {}
            explicit BadPointer(const std::string &error) : out_of_range(error) {}
        };
    public:
        constexpr Allocator() : size(0), first(nullptr), cursor(nullptr), end(nullptr) {

        }
        Allocator(const Allocator &other) : size(other.size), first(other.first), cursor(other.cursor), end(other.end) {
            if(&other not_eq this) {
                this->free();
            }
        }
        Allocator(Allocator &&) = delete;
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
        Allocator &operator=(Allocator &&) = delete;
        ~Allocator() {
            this->free();
        }
        explicit operator bool() const {
            return this->size > 0;
        }
        pointer allocate(sizeType size) & {
            this->size = size;
            if(this->first) {
                this->reallocate();
                return this->first;
            }
            this->first = static_cast<type *>(::operator new(static_cast<size_t>(sizeof(type) * this->size)));
            if(!this->first) {
                throw BadPointer("Fail to allocate the memory!");
            }
            this->cursor = this->first;
            this->end = this->first + this->size;
            return this->first;
        }
        pointer construct(referenceToPointer p, constReference object) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) type(object);
            return p;
        }
        template <typename ...Args>
        pointer construct(referenceToPointer p, const Args &...args) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) type(args...);
            return p;
        }
        pointer construct(referenceToPointer p, rightValueReference object) & {
            this->checkPointer(this->first, this->end, p);
            new (p++) type(std::move(object));
            return p;
        }
        pointer destroy(pointer p) & {
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
            return not(this->empty());
        }
        bool empty() const {
            for(auto cursor {this->first}; cursor not_eq this->cursor; ++cursor) {
                if(*cursor) {
                    return false;
                }
            }
            return true;
        }
        sizeType getSize() const & {
            return this->size;
        }
        pointer getFirst() const & {
            return this->first;
        }
        referenceToPointer getCursor() & {
            return this->cursor;
        }
        pointer getEnd() const & {
            return this->end;
        }
#ifdef OTHER_FUNCTION
    public:
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
