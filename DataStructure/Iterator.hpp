#ifndef DATA_STRUCTURE_ITERATOR_HPP
#define DATA_STRUCTURE_ITERATOR_HPP

#include "TypeTraits.hpp"

namespace DataStructure {
    template <typename T, typename Ptr, typename Ref>
    class __DataStructure_WrapIterator final {
    public:
        using sizeType = typename __DataStructure_IteratorTraits<Ptr, static_cast<bool>(
                        typename __DataStructure_typeTraits<Ptr>::is_POD_type()
                )>::sizeType;
        using differenceType = typename __DataStructure_IteratorTraits<Ptr, static_cast<bool>(
                        typename __DataStructure_typeTraits<Ptr>::is_POD_type()
                )>::differenceType;
        using valueType = T;
        using reference = Ref;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = Ptr;
        using constPointer = const valueType *;
        using iteratorTag = RandomAccessIterator;
    private:
        using Iterator = __DataStructure_WrapIterator;
    private:
        pointer iterator;
    public:
        constexpr __DataStructure_WrapIterator() : iterator {nullptr} {}
        explicit __DataStructure_WrapIterator(pointer iterator) : iterator {iterator} {}
        __DataStructure_WrapIterator(const Iterator &) = default;
        __DataStructure_WrapIterator(Iterator &&) noexcept = default;
        ~__DataStructure_WrapIterator() = default;
    public:
        Iterator &operator=(const Iterator &) = default;
        Iterator &operator=(Iterator &&) noexcept = default;
        reference operator*() const noexcept {
            return *this->iterator;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        reference operator[](differenceType index) const {
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
            return *this - rhs > 0;
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
        explicit operator bool() const noexcept {
            return static_cast<bool>(this->iterator);
        }
    };
    template <typename Iterator>
    class __DataStructure_ReverseIterator final {
    private:
        using traits = __DataStructure_IteratorTraits<Iterator, static_cast<bool>(
                        typename __DataStructure_typeTraits<Iterator>::is_POD_type()
                )>;
        static_assert(traits::iteratorTag::isOutputIterator or traits::iteratorTag::isInputIterator,
                            "The template argument need an iterator type!"
                     );
        static_assert(traits::iteratorTag::isRandomAccessIterator,
                            "The template argument need an iterator who can be random accessed at least!"
                     );
    public:
        using sizeType = typename traits::sizeType;
        using differenceType = typename traits::differenceType;
        using valueType = typename traits::valueType;
        using reference = typename traits::reference;
        using constReference = typename traits::constReference;
        using rightValueReference = typename traits::rightValueReference;
        using pointer = typename traits::pointer;
        using constPointer = typename traits::constPointer;
        using iteratorTag = typename traits::iteratorTag;
        using iteratorType = Iterator;
    private:
        using thisType = __DataStructure_ReverseIterator;
    private:
        iteratorType iterator;
    public:
        constexpr __DataStructure_ReverseIterator() : iterator() {}
        explicit __DataStructure_ReverseIterator(iteratorType iterator) : iterator {iterator} {}
        __DataStructure_ReverseIterator(const thisType &) = default;
        __DataStructure_ReverseIterator(thisType &&) noexcept = default;
        ~__DataStructure_ReverseIterator() = default;
    public:
        thisType &operator=(const thisType &) = default;
        thisType &operator=(thisType &&) noexcept = default;
        reference operator*() const noexcept {
            return *this->iterator;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        reference operator[](differenceType index) const {
            return *(iterator - index);
        }
        thisType &operator+=(differenceType index) noexcept {
            this->iterator -= index;
            return *this;
        }
        thisType &operator-=(differenceType index) noexcept {
            return *this += -index;
        }
        thisType &operator++() noexcept {
            --this->iterator;
            return *this;
        }
        thisType &operator--() noexcept {
            ++this->iterator;
            return *this;
        }
        thisType operator++(int) noexcept {
            auto temp {*this};
            ++*this;
            return temp;
        }
        thisType operator--(int) noexcept {
            auto temp {*this};
            --*this;
            return temp;
        }
        thisType operator+(differenceType n) const noexcept {
            auto temp {*this};
            temp += n;
            return temp;
        }
        thisType operator-(differenceType n) const noexcept {
            return this->operator+(-n);
        }
        friend differenceType operator-(const thisType &left, const thisType &right) noexcept {
            return left.iterator - right.iterator;
        }
        bool operator==(const thisType &rhs) const noexcept {
            return this->iterator == rhs.iterator;
        }
        bool operator not_eq (const thisType &rhs) const noexcept {
            return not(*this == rhs);
        }
        bool operator<(const thisType &rhs) const noexcept {
            return *this - rhs > 0;
        }
        bool operator<=(const thisType &rhs) const noexcept {
            return *this < rhs or *this == rhs;
        }
        bool operator>(const thisType &rhs) const noexcept {
            return not(*this <= rhs);
        }
        bool operator>=(const thisType &rhs) const noexcept {
            return not(*this < rhs);
        }
        explicit operator bool() const noexcept {
            return static_cast<bool>(this->iterator);
        }
    };
}

#endif //DATA_STRUCTURE_ITERATOR_HPP
