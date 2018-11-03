#ifndef DATA_STRUCTURE_ITERATOR_HPP
#define DATA_STRUCTURE_ITERATOR_HPP

#include "TypeTraits.hpp"

namespace DataStructure {
    template <typename T, typename Ref, typename Ptr>
    class __DataStructure_WrapIterator final {
    private:
        using thisType = __DataStructure_WrapIterator;
    public:
        using valueType = T;
        using pointer = Ptr;
        using reference = Ref;
        using sizeType = typename __DataStructure_IteratorTraits<pointer>::sizeType;
        using differenceType = typename __DataStructure_IteratorTraits<pointer>::differenceType;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using constPointer = const valueType *;
        using iteratorTag = RandomAccessIterator;
    private:
        using reverseReference = typename __DataStructure_ConstOrNonConst<reference>::__result;
        using reversePointer = typename __DataStructure_ConstOrNonConst<pointer>::__result;
    private:
        pointer iterator;
    public:
        constexpr __DataStructure_WrapIterator() : iterator {nullptr} {}
        explicit __DataStructure_WrapIterator(pointer iterator) : iterator {iterator} {}
        __DataStructure_WrapIterator(const thisType &) = default;
        __DataStructure_WrapIterator(thisType &&) noexcept = default;
        ~__DataStructure_WrapIterator() = default;
    public:
        __DataStructure_WrapIterator &operator=(const thisType &) = default;
        __DataStructure_WrapIterator &operator=(thisType &&) noexcept = default;
        reference operator*() const noexcept {
            return *this->iterator;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        reference operator[](differenceType index) const {
            return *(iterator + index);
        }
        thisType &operator+=(differenceType index) noexcept {
            this->iterator += index;
            return *this;
        }
        thisType &operator-=(differenceType index) noexcept {
            return *this += -index;
        }
        thisType &operator++() noexcept {
            ++this->iterator;
            return *this;
        }
        thisType &operator--() noexcept {
            --this->iterator;
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
        bool operator!=(const thisType &rhs) const noexcept {
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
        operator __DataStructure_WrapIterator<
                    valueType, reverseReference, reversePointer
                 >() const noexcept {
            return __DataStructure_WrapIterator<valueType, reverseReference, reversePointer>(
                    reinterpret_cast<
                        typename __DataStructure_WrapIterator<
                                    valueType, reverseReference, reversePointer
                                 >::pointer
                    >(this->iterator)
            );
        }

    };
    template <typename Iterator, typename ReverseType>
    class __DataStructure_ReverseIterator final {
    private:
        using traits = __DataStructure_IteratorTraitsAuxiliary<Iterator, static_cast<bool>(
                        typename __DataStructure_TypeTraits<Iterator>::is_POD_type()
                )>;
        static_assert(traits::iteratorTag::isOutputIterator or traits::iteratorTag::isInputIterator,
                            "The template argument need an iterator type!"
                     );
        static_assert(traits::iteratorTag::isRandomAccessIterator,
                            "The template argument need an iterator who can be random accessed!"
                     );
        using reverseType = ReverseType;
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
            return right.iterator - left.iterator;
        }
        bool operator==(const thisType &rhs) const noexcept {
            return this->iterator == rhs.iterator;
        }
        bool operator!=(const thisType &rhs) const noexcept {
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
        operator __DataStructure_ReverseIterator<reverseType, Iterator>() const noexcept {
            return __DataStructure_ReverseIterator<reverseType, Iterator>(this->iterator);
        }
    };
    template <typename T, typename Ref, typename Ptr>
    struct __DataStructure_ForwardNode final {
        static_assert(
                static_cast<bool>(typename IsReference<Ref>::result()) or
                static_cast<bool>(typename IsPointer<Ptr>::result()),
                "Template arguments error! "
                "The second type must be a reference type, "
                "the third type must be a pointer type."
        );
        static_assert(
                static_cast<bool>(
                    typename IsSame<
                            T, typename RemoveConst<typename RemoveReference<Ref>::type>::type
                    >::result()
                ) or
                static_cast<bool>(
                    typename IsSame<
                            T, typename RemoveConst<typename RemoveReference<Ptr>::type>::type
                    >::result()
                ),
                "Template arguments error! "
                "The second type must be reference-to-first_type, "
                "the third type must be pointer-to-first_type."
        );
    private:
        using node = __DataStructure_ForwardNode;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = Ref;
        using pointer = Ptr;
        using link = node *;
        using reverseType = __DataStructure_ForwardNode<
                                valueType,
                                typename __DataStructure_ConstOrNonConst<Ref>::__result,
                                typename __DataStructure_ConstOrNonConst<Ptr>::__result
                            >;
    public:
        link next;
        valueType data;
    };
    template <typename NodeType>
    class __DataStructure_ForwardListIterator {
    private:
        using nodeType = NodeType;
        using thisType = __DataStructure_ForwardListIterator;
    public:
        using sizeType = typename nodeType::sizeType;
        using differenceType = typename nodeType::differenceType;
        using valueType = typename nodeType::valueType;
        using reference = typename nodeType::reference;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = typename nodeType::pointer;
        using constPointer = const valueType *;
        using iteratorTag = ForwardIterator;
        using link = typename nodeType::link;
    private:
        link iterator;
    public:
        constexpr __DataStructure_ForwardListIterator() : iterator {nullptr} {};
        explicit __DataStructure_ForwardListIterator(link iterator) : iterator {iterator} {}
        __DataStructure_ForwardListIterator(const thisType &) = default;
        __DataStructure_ForwardListIterator(thisType &&) noexcept = default;
        ~__DataStructure_ForwardListIterator() = default;
    public:
        __DataStructure_ForwardListIterator &operator=(const thisType &) = default;
        __DataStructure_ForwardListIterator &operator=(thisType &&) noexcept = default;
        reference operator*() const noexcept {
            return this->iterator->data;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        thisType &operator++() noexcept {
            this->iterator = this->iterator->next;
            return *this;
        }
        thisType operator++(int) noexcept {
            auto temp {*this};
            ++*this;
            return temp;
        }
        bool operator==(const thisType &rhs) const noexcept {
            return this->iterator == rhs.iterator;
        }
        bool operator!=(const thisType &rhs) const noexcept {
            return not(*this == rhs);
        }
        bool operator<(const thisType &) const noexcept = delete;
        bool operator<=(const thisType &) const noexcept = delete;
        bool operator>(const thisType &) const noexcept = delete;
        bool operator>=(const thisType &) const noexcept = delete;
        explicit operator bool() const noexcept {
            return static_cast<bool>(this->iterator);
        }
        operator __DataStructure_ForwardListIterator<typename nodeType::reverseType>() const noexcept {
            return __DataStructure_ForwardListIterator<typename nodeType::reverseType>(
                    reinterpret_cast<typename nodeType::reverseType *>(this->iterator)
            );
        }
    };
    template <typename T, typename Ref, typename Ptr>
    struct __DataStructure_BidirectionalNode final {
        static_assert(
                static_cast<bool>(typename IsReference<Ref>::result()) or
                static_cast<bool>(typename IsPointer<Ptr>::result()),
                "Template arguments error! "
                "The second type must be a reference type, "
                "the third type must be a pointer type."
        );
        static_assert(
                static_cast<bool>(
                    typename IsSame<
                            T, typename RemoveConst<typename RemoveReference<Ref>::type>::type
                    >::result()
                ) or
                static_cast<bool>(
                    typename IsSame<
                            T, typename RemoveConst<typename RemoveReference<Ptr>::type>::type
                    >::result()
                ),
                "Template arguments error! "
                "The second type must be reference-to-first_type, "
                "the third type must be pointer-to-first_type."
        );
    private:
        using node = __DataStructure_BidirectionalNode;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = Ref;
        using pointer = Ptr;
        using link = node *;
        using reverseType = __DataStructure_BidirectionalNode<
                                valueType,
                                typename __DataStructure_ConstOrNonConst<Ref>::__result,
                                typename __DataStructure_ConstOrNonConst<Ptr>::__result
                            >;
    public:
        link next;
        link previous;
        valueType data;
    };
    template <typename NodeType>
    class __DataStructure_ListIterator {
    private:
        using nodeType = NodeType;
        using thisType = __DataStructure_ListIterator;
    public:
        using sizeType = typename nodeType::sizeType;
        using differenceType = typename nodeType::differenceType;
        using valueType = typename nodeType::valueType;
        using reference = typename nodeType::reference;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = typename nodeType::pointer;
        using constPointer = const valueType *;
        using iteratorTag = BidirectionalIterator;
        using link = typename nodeType::link;
    private:
        link iterator;
    public:
        constexpr __DataStructure_ListIterator() : iterator {nullptr} {}
        explicit __DataStructure_ListIterator(link iterator) : iterator {iterator} {}
        __DataStructure_ListIterator(const thisType &) = default;
        __DataStructure_ListIterator(thisType &&) noexcept = default;
        ~__DataStructure_ListIterator() = default;
    public:
        __DataStructure_ListIterator &operator=(const thisType &) = default;
        __DataStructure_ListIterator &operator=(thisType &&) noexcept = default;
        reference operator*() const noexcept {
            return this->iterator->data;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        thisType &operator++() noexcept {
            this->iterator = this->iterator->next;
            return *this;
        }
        thisType operator++(int) noexcept {
            auto temp {*this};
            ++*this;
            return temp;
        }
        thisType &operator--() noexcept {
            this->iterator = this->iterator->previous;
            return *this;
        }
        thisType operator--(int) noexcept {
            auto temp {*this};
            --*this;
            return temp;
        }
        bool operator==(const thisType &rhs) const noexcept {
            return this->iterator == rhs.iterator;
        }
        bool operator!=(const thisType &rhs) const noexcept {
            return not(*this == rhs);
        }
        bool operator<(const thisType &) const noexcept = delete;
        bool operator<=(const thisType &) const noexcept = delete;
        bool operator>(const thisType &) const noexcept = delete;
        bool operator>=(const thisType &) const noexcept = delete;
        explicit operator bool() const noexcept {
            return static_cast<bool>(this->iterator);
        }
        operator __DataStructure_ListIterator<typename nodeType::reverseType>() const noexcept {
            return __DataStructure_ListIterator<typename nodeType::reverseType>(
                    reinterpret_cast<typename nodeType::reverseType *>(this->iterator)
            );
        }
    };
    template <typename NodeType>
    class __DataStructure_ListReverseIterator final {
    private:
        using nodeType = NodeType;
        using thisType = __DataStructure_ListReverseIterator;
    public:
        using sizeType = typename nodeType::sizeType;
        using differenceType = typename nodeType::differenceType;
        using valueType = typename nodeType::valueType;
        using reference = typename nodeType::reference;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = typename nodeType::pointer;
        using constPointer = const valueType *;
        using iteratorTag = BidirectionalIterator;
        using link = typename nodeType::link;
    private:
        link iterator;
    public:
        constexpr __DataStructure_ListReverseIterator() : iterator {nullptr} {}
        explicit __DataStructure_ListReverseIterator(nodeType *iterator) : iterator {iterator} {}
        __DataStructure_ListReverseIterator(const thisType &) = default;
        __DataStructure_ListReverseIterator(thisType &&) noexcept = default;
        ~__DataStructure_ListReverseIterator() = default;
    public:
        __DataStructure_ListReverseIterator &operator=(const thisType &) = default;
        __DataStructure_ListReverseIterator &operator=(thisType &&) noexcept = default;
        reference operator*() const noexcept {
            return this->iterator->data;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        thisType &operator++() noexcept {
            this->iterator = this->iterator->previous;
            return *this;
        }
        thisType operator++(int) noexcept {
            auto temp {*this};
            ++*this;
            return temp;
        }
        thisType &operator--() noexcept {
            this->iterator = this->iterator->next;
            return *this;
        }
        thisType operator--(int) noexcept {
            auto temp {*this};
            --*this;
            return temp;
        }
        bool operator==(const thisType &rhs) const noexcept {
            return this->iterator == rhs.iterator;
        }
        bool operator!=(const thisType &rhs) const noexcept {
            return not(*this == rhs);
        }
        bool operator<(const thisType &) const noexcept = delete;
        bool operator<=(const thisType &) const noexcept = delete;
        bool operator>(const thisType &) const noexcept = delete;
        bool operator>=(const thisType &) const noexcept = delete;
        explicit operator bool() const noexcept {
            return static_cast<bool>(this->iterator);
        }
    };
    template <typename T, typename Ref, typename Ptr, typename Allocator>
    class __DataStructure_DequeIterator final {
    private:
        using thisType = __DataStructure_DequeIterator;
        using allocatorType = Allocator;
        using buffer = allocatorType *;
    public:
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = Ref;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = Ptr;
        using constPointer = const valueType *;
        using iteratorTag = RandomAccessIterator;
    private:
        buffer node;
        pointer iterator;
    public:
        constexpr __DataStructure_DequeIterator() : node {nullptr}, iterator {nullptr} {}
        __DataStructure_DequeIterator(pointer iterator, buffer node) : node {node}, iterator {iterator} {}
        __DataStructure_DequeIterator(const thisType &) = default;
        __DataStructure_DequeIterator(thisType &&) noexcept = default;
        ~__DataStructure_DequeIterator() = default;
    public:
        __DataStructure_DequeIterator &operator=(const thisType &) = default;
        __DataStructure_DequeIterator &operator=(thisType &&) noexcept = default;
        reference operator*() const noexcept {
            return *this->iterator;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        differenceType operator-(const thisType &rhs) const noexcept {
            return static_cast<differenceType>(this->node->capacity()) * (this->node - rhs.node - 1) +
                    this->iterator - this->node->begin() + rhs.node->end() - rhs.iterator;
        }
        thisType &operator++() noexcept {
            if(++this->iterator < this->node->end()) {
                return *this;
            }
            ++this->node;
            this->iterator = this->node->begin();
            return *this;
        }
        thisType operator++(int) noexcept {
            auto temp {*this};
            ++*this;
            return temp;
        }
        thisType &operator--() noexcept {
            if(--this->iterator >= this->node->begin()) {
                return *this;
            }
            --this->node;
            this->iterator = this->node->end() - static_cast<differenceType>(1);
            return *this;
        }
        thisType operator--(int) noexcept {
            auto temp {*this};
            --*this;
            return temp;
        }
        thisType &operator+=(differenceType n) noexcept {
            const auto offset {n + (this->iterator - this->node->begin())};
            const auto size {static_cast<differenceType>(this->node->capacity())};
            if(offset >= 0 and offset < size) {
                this->iterator += n;
                return *this;
            }
            const auto nodeOffset {offset > 0 ? offset / size : -((-offset - 1) / size) - 1};
            this->node += nodeOffset;
            this->iterator = this->node->begin() + (offset - nodeOffset * size);
            return *this;
        }
        thisType &operator-=(differenceType n) noexcept {
            return *this += -n;
        }
        thisType operator+(differenceType n) const noexcept {
            auto temp {*this};
            return temp += n;
        }
        thisType operator-(differenceType n) const noexcept {
            return *this + -n;
        }
        reference operator[](differenceType n) const noexcept {
            return *(*this + n);
        }
        bool operator==(const thisType &rhs) const noexcept {
            return this->iterator == rhs.iterator and this->node == rhs.node;
        }
        bool operator!=(const thisType &rhs) const noexcept {
            return not(*this == rhs);
        }
        bool operator<(const thisType &rhs) const noexcept {
            return this->node == rhs.node ? this->iterator < rhs.iterator : this->node < rhs.node;
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
        operator __DataStructure_DequeIterator<valueType,
                    typename __DataStructure_ConstOrNonConst<reference>::__result,
                    typename __DataStructure_ConstOrNonConst<pointer>::__result, allocatorType
                 >() const noexcept {
            return __DataStructure_DequeIterator<valueType,
                        typename __DataStructure_ConstOrNonConst<reference>::__result,
                        typename __DataStructure_ConstOrNonConst<pointer>::__result, allocatorType
                   >(reinterpret_cast<
                           typename __DataStructure_ConstOrNonConst<pointer>::__result
                     >(this->iterator), this->node);
        }
    public:
        thisType &construct(constReference value) noexcept(static_cast<bool>(
                typename __DataStructure_TypeTraits<valueType>::hasTrivialCopyConstructor())
        ) {
            this->node->construct(this->iterator, value);
            return *this;
        }
        thisType &construct(rightValueReference value) noexcept(static_cast<bool>(
                typename __DataStructure_TypeTraits<valueType>::hasTrivialMoveConstructor())
        ) {
            this->node->construct(this->iterator, value);
            return *this;
        }
        template <typename ...Args>
        thisType &construct(Args &&...args) noexcept(static_cast<bool>(
                typename __DataStructure_TypeTraits<valueType>::hasTrivialMoveConstructor())
        ) {
            return this->construct(valueType(forward<Args>(args)...));
        }
        thisType &destroy() noexcept(static_cast<bool>(
                typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        ) {
            this->node->destroy(this->iterator);
            return *this;
        }
    };
}

#endif //DATA_STRUCTURE_ITERATOR_HPP
