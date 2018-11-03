#ifndef DATA_STRUCTURE_DEQUE_HPP
#define DATA_STRUCTURE_DEQUE_HPP

#include "../Allocator.hpp"
#include "../Iterator.hpp"

namespace DataStructure {
    template <typename T, typename Alloc = Allocator<T>, unsigned long BufferSize = 64>
    class Deque final {
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
        using iterator = __DataStructure_DequeIterator<valueType, reference, pointer, allocator>;
        using constIterator = __DataStructure_DequeIterator<valueType, constReference, constPointer, allocator>;
        using reverseIterator = __DataStructure_ReverseIterator<iterator, constIterator>;
        using constReverseIterator = __DataStructure_ReverseIterator<constIterator, iterator>;
    private:
        using bufferType = allocator *;
    private:
        enum : unsigned long {
            bufferSize = (BufferSize == 0) ? static_cast<unsigned long>(
                                                sizeof(valueType) > 512 ? 1 : 256 / sizeof(valueType)
                                             ) : BufferSize
        };
        enum : unsigned long {
            preserveSize = static_cast<unsigned long>(2)
        };
        enum class __Deque_CheckParameter {
            TAIL_SUCCESSFUL, HEAD_SUCCESSFUL, ALL_FAILED
        };
    private:
        sizeType bufferNumber;
        bufferType buffer;
        iterator last;
        iterator first;
    private:
        constexpr static sizeType startSize(sizeType = 0) noexcept;
    private:
        void initBuffer(sizeType = 0);
        void free() noexcept(
                static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
        );
        __Deque_CheckParameter checkReserve(sizeType, bool = false) const noexcept;
        template <typename Type>
        void insertBackwardAuxiliary(Type, sizeType, iterator);
        template <typename Type>
        void insertForwardAuxiliary(Type, sizeType, iterator);
        void addBuffer(sizeType, bool = false);
        template <typename Type>
        iterator insertAuxiliary(differenceType, Type, sizeType, bool);
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr>
        void insertBackwardAuxiliaryForIterator(typename __DataStructure_isInputIterator<InputIterator>::__result,
                InputIterator, iterator, sizeType
        );
        template <typename InputIterator,
                        typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr>
        void insertForwardAuxiliaryForIterator(typename __DataStructure_isInputIterator<InputIterator>::__result,
                InputIterator, iterator, sizeType
        );
        template <typename InputIterator,
                typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr>
        iterator insertAuxiliaryForIterator(differenceType,
                typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator, bool
        );
        void eraseForwardAuxiliary(differenceType, sizeType);
        void eraseBackwardAuxiliary(differenceType, sizeType);
        template <typename Type>
        void pushFrontAuxiliary(Type);
        template <typename Type>
        void pushBackAuxiliary(Type);
        void shrink(bool = false);
    public:
        Deque();
        explicit Deque(sizeType);
        Deque(sizeType, constReference);
        template <typename InputIterator,
                    typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        Deque(typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator);
        Deque(std::initializer_list<valueType>);
        Deque(const Deque &);
        Deque(Deque &&) noexcept;
        ~Deque();
    public:
        Deque &operator=(const Deque &);
        Deque &operator=(Deque &&) noexcept;
        Deque &operator=(std::initializer_list<valueType>);
        reference operator[](differenceType) &;
        constReference operator[](differenceType) const &;
        bool operator==(const Deque &) const noexcept;
        bool operator!=(const Deque &) const noexcept;
        bool operator<(const Deque &) const noexcept;
        bool operator<=(const Deque &) const noexcept;
        bool operator>(const Deque &) const noexcept;
        bool operator>=(const Deque &) const noexcept;
        Deque operator+() const;
        Deque operator-() const;
        explicit operator bool() const noexcept;
    public:
        void assign(sizeType, constReference = valueType());
        template <typename InputIterator,
                    typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
                 >
        void assign(typename __DataStructure_isInputIterator<InputIterator>::__result, InputIterator);
        void assign(std::initializer_list<valueType>);
        valueType at(differenceType) const;
        valueType front() const;
        valueType back() const;
        iterator begin() const noexcept;
        constIterator cbegin() const noexcept;
        iterator end() const noexcept;
        constIterator cend() const noexcept;
        reverseIterator rbegin() const noexcept;
        constReverseIterator crbegin() const noexcept;
        reverseIterator rend() const noexcept;
        constReverseIterator crend() const noexcept;
        sizeType size() const noexcept;
        sizeType capacity() const noexcept;
        sizeType reserve() const noexcept;
        iterator resize(sizeType);
        bool empty() const noexcept;
        iterator shrinkToFit();
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
                        typename __DataStructure_isInputIterator<InputIterator>::__result,
                        InputIterator
        );
        template <typename InputIterator,
                typename __DataStructure_isInputIterator<InputIterator>::__result * = nullptr
        >
        iterator insert(differenceType,
                        typename __DataStructure_isInputIterator<InputIterator>::__result,
                        InputIterator
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
        void swap(Deque &) noexcept;
        bufferType getAllocator() const & noexcept;
#ifdef DEBUG_DATA_STRUCTURE_FOR_DEQUE
        sizeType &getBufferNumber() & noexcept;
        bufferType &getBuffer() & noexcept;
        iterator &getFirst() & noexcept;
        iterator &getLast() & noexcept;
#endif
    };
    template <typename T, typename Allocator, unsigned long BufferSize>
    void swap(Deque<T, Allocator, BufferSize> &, Deque<T, Allocator, BufferSize> &) noexcept;
}

template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::swap(Deque<T, Allocator, BufferSize> &lhs, Deque<T, Allocator, BufferSize> &rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T, typename Allocator, unsigned long BufferSize>
inline constexpr typename DataStructure::Deque<T, Allocator, BufferSize>::sizeType
DataStructure::Deque<T, Allocator, BufferSize>::startSize(sizeType size) noexcept {
    return (size + static_cast<sizeType>(Deque::preserveSize)) /
                static_cast<sizeType>(Deque::bufferSize) == 0ul ? 1ul :
                (size + static_cast<sizeType>(
                                                Deque::preserveSize
                                             )) / static_cast<sizeType>(Deque::bufferSize) + (
                    static_cast<sizeType>(not(size + static_cast<sizeType>(Deque::preserveSize)) %
                            static_cast<sizeType>(Deque::bufferSize) == static_cast<sizeType>(0)
                    )
                );
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline void DataStructure::Deque<T, Allocator, BufferSize>::initBuffer(sizeType size) {
    while(size < this->bufferNumber) {
        this->buffer[size++].allocate(static_cast<sizeType>(bufferSize));
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline void DataStructure::Deque<T, Allocator, BufferSize>::free() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    delete[] this->buffer;
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline typename DataStructure::Deque<T, Allocator, BufferSize>::__Deque_CheckParameter
DataStructure::Deque<T, Allocator, BufferSize>::checkReserve(sizeType size, bool headFirstly) const noexcept {
    if(headFirstly) {
        if(this->first - iterator(this->buffer->begin(), this->buffer) > size) {
            return __Deque_CheckParameter::HEAD_SUCCESSFUL;
        }
        auto lastBuffer {this->buffer + static_cast<differenceType>(this->bufferNumber - 1)};
        if(iterator(lastBuffer->end(), lastBuffer) - this->last) {
            return __Deque_CheckParameter::TAIL_SUCCESSFUL;
        }
        return __Deque_CheckParameter::ALL_FAILED;
    }
    auto lastBuffer {this->buffer + static_cast<differenceType>(this->bufferNumber - 1)};
    if(static_cast<sizeType>(iterator(lastBuffer->end(), lastBuffer) - this->last) > size) {
        return __Deque_CheckParameter::TAIL_SUCCESSFUL;
    }
    if(static_cast<sizeType>(this->first - iterator(this->buffer->begin(), this->buffer) + 1) > size) {
        return __Deque_CheckParameter::HEAD_SUCCESSFUL;
    }
    return __Deque_CheckParameter::ALL_FAILED;
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename Type>
inline void DataStructure::Deque<T, Allocator, BufferSize>::insertBackwardAuxiliary(
        Type value, sizeType size, iterator insertPosition
) {
    auto newLast {this->last + static_cast<differenceType>(size)};
    auto cursor {newLast - static_cast<differenceType>(1)};
    auto moveCursor {this->last - static_cast<differenceType>(1)};
    while(moveCursor >= insertPosition) {
        --cursor.construct(move(*moveCursor));
        --moveCursor.destroy();
    }
    this->last = newLast;
    while(size--) {
        ++insertPosition.construct(value);
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename Type>
inline void DataStructure::Deque<T, Allocator, BufferSize>::insertForwardAuxiliary(
        Type value, sizeType size, iterator insertPosition
) {
    auto newFirst {this->first - static_cast<differenceType>(size)};
    auto cursor {newFirst + static_cast<differenceType>(1)};
    auto moveCursor {this->first + static_cast<differenceType>(1)};
    while(moveCursor not_eq insertPosition) {
        ++cursor.construct(move(*moveCursor));
        ++moveCursor.destroy();
    }
    this->first = newFirst;
    insertPosition = cursor;
    while(size--) {
        ++insertPosition.construct(value);
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline void DataStructure::Deque<T, Allocator, BufferSize>::addBuffer(sizeType size, bool addToFront) {
    auto newBufferNumber {Deque::startSize(this->capacity() + size)};
    auto difference {static_cast<differenceType>(newBufferNumber - this->bufferNumber)};
    auto newBuffer {new allocator[newBufferNumber]()};
    auto firstDifference {this->first - iterator(this->buffer->begin(), this->buffer)};
    auto oldSize {static_cast<differenceType>(this->size() + 1)};
    if(addToFront) {
        for(auto i {
                        static_cast<sizeType>(difference)
                   }, j {static_cast<sizeType>(0)}; i < newBufferNumber; ++i) {
            newBuffer[i] = move(this->buffer[j++]);
        }
        for(auto i {0}; i < difference; ++i) {
            newBuffer[i].allocate(static_cast<sizeType>(bufferSize));
        }
        auto oldStart {newBuffer + difference};
        this->first = iterator(oldStart->begin(), oldStart) + firstDifference;
        this->last = this->first + oldSize;
        this->bufferNumber = move(newBufferNumber);
        this->free();
        this->buffer = move(newBuffer);
        return;
    }
    for(auto i {0}; i < this->bufferNumber; ++i) {
        newBuffer[i] = move(this->buffer[i]);
    }
    for(auto i {this->bufferNumber}; i < newBufferNumber; ++i) {
        newBuffer[i].allocate(static_cast<sizeType>(bufferSize));
    }
    this->first = iterator(newBuffer->begin(), newBuffer) + firstDifference;
    this->last = this->first + oldSize;
    this->bufferNumber = move(newBufferNumber);
    this->free();
    this->buffer = move(newBuffer);
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename Type>
inline typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insertAuxiliary(
        differenceType index, Type value, sizeType size, bool backward
) {
    auto insertPosition {this->begin() + index};
    if(backward) {
        switch(this->checkReserve(size)) {
            case __Deque_CheckParameter::TAIL_SUCCESSFUL:
                this->insertBackwardAuxiliary<Type>(value, size, insertPosition);
                return insertPosition;
            case __Deque_CheckParameter::HEAD_SUCCESSFUL:
                this->insertForwardAuxiliary<Type>(value, size, insertPosition);
                return insertPosition - size;
            default:
                break;
        }
        this->addBuffer(size);
        insertPosition = this->begin() + index;
        this->insertBackwardAuxiliary<Type>(value, size, insertPosition);
        return insertPosition;
    }
    switch(this->checkReserve(size, true)) {
        case __Deque_CheckParameter::HEAD_SUCCESSFUL:
            this->insertForwardAuxiliary<Type>(value, size, insertPosition);
            return insertPosition - size;
        case __Deque_CheckParameter::TAIL_SUCCESSFUL:
            this->insertBackwardAuxiliary<Type>(value, size, insertPosition);
            return insertPosition;
        default:
            break;
    }
    this->addBuffer(size, true);
    insertPosition = this->begin() + index;
    this->insertForwardAuxiliary<Type>(value, size, insertPosition);
    return insertPosition - size;
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
inline void DataStructure::Deque<T, Allocator, BufferSize>::insertForwardAuxiliaryForIterator(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last,
        iterator insertPosition, sizeType size
) {
    auto newFirst {this->first - static_cast<differenceType>(size)};
    auto cursor {newFirst + static_cast<differenceType>(1)};
    auto moveCursor {this->first + static_cast<differenceType>(1)};
    while(moveCursor not_eq insertPosition) {
        ++cursor.construct(move(*moveCursor));
        ++moveCursor.destroy();
    }
    this->first = newFirst;
    insertPosition = cursor;
    while(first not_eq last) {
        ++insertPosition.construct(static_cast<valueType>(*first++));
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
            typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
inline void DataStructure::Deque<T, Allocator, BufferSize>::insertBackwardAuxiliaryForIterator(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last,
        iterator insertPosition, sizeType size
) {
    auto newLast {this->last + static_cast<differenceType>(size)};
    auto cursor {newLast - static_cast<differenceType>(1)};
    auto moveCursor {this->last - static_cast<differenceType>(1)};
    while(moveCursor >= insertPosition) {
        --cursor.construct(move(*moveCursor));
        --moveCursor.destroy();
    }
    this->last = newLast;
    while(first not_eq last) {
        ++insertPosition.construct(static_cast<valueType>(*first++));
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
inline typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insertAuxiliaryForIterator(
        differenceType index,
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last,
        bool backward
) {
    auto insertPosition {this->begin() + index};
    const auto size {IteratorDifference<InputIterator>()(first, last)};
    if(backward) {
        switch(this->checkReserve(size)) {
            case __Deque_CheckParameter::TAIL_SUCCESSFUL:
                this->insertBackwardAuxiliaryForIterator(first, last, insertPosition, size);
                return insertPosition;
            case __Deque_CheckParameter::HEAD_SUCCESSFUL:
                this->insertForwardAuxiliaryForIterator(first, last, insertPosition, size);
                return insertPosition - size;
            default:
                break;
        }
        this->addBuffer(size);
        insertPosition = this->begin() + index;
        this->insertBackwardAuxiliaryForIterator(first, last, insertPosition, size);
        return insertPosition;
    }
    switch(this->checkReserve(size, true)) {
        case __Deque_CheckParameter::HEAD_SUCCESSFUL:
            this->insertForwardAuxiliaryForIterator(first, last, insertPosition, size);
            return insertPosition - size;
        case __Deque_CheckParameter::TAIL_SUCCESSFUL:
            this->insertBackwardAuxiliaryForIterator(first, last, insertPosition, size);
            return insertPosition;
        default:
            break;
    }
    this->addBuffer(size, true);
    insertPosition = this->begin() + index;
    this->insertForwardAuxiliaryForIterator(first, last, insertPosition, size);
    return insertPosition - size;
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline void DataStructure::Deque<T, Allocator, BufferSize>::eraseBackwardAuxiliary(
        differenceType index, sizeType size
) {
    auto erasePosition {this->begin() + index};
    auto cursor {erasePosition};
    for(auto i {0}; i < size; ++i) {
        ++cursor.destroy();
    }
    while(cursor not_eq this->last) {
        ++erasePosition.construct(move(*cursor));
        ++cursor.destroy();
    }
    this->last -= static_cast<differenceType>(size);
    this->shrink();
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline void DataStructure::Deque<T, Allocator, BufferSize>::eraseForwardAuxiliary(
        differenceType index, sizeType size
) {
    auto erasePosition {this->begin() + static_cast<differenceType>(index)};
    --size;
    auto cursor {erasePosition + static_cast<differenceType>(size)};
    while(cursor >= erasePosition) {
        --cursor.destroy();
    }
    erasePosition += static_cast<differenceType>(size);
    while(cursor not_eq this->first) {
        --erasePosition.construct(move(*cursor));
        --cursor.destroy();
    }
    this->first = move(erasePosition);
    this->shrink(true);
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename Type>
inline void DataStructure::Deque<T, Allocator, BufferSize>::pushBackAuxiliary(Type value) {
    const auto lastBuffer {
        this->buffer + static_cast<differenceType>(this->bufferNumber - static_cast<sizeType>(1))
    };
    if(this->last == iterator(lastBuffer->end() - static_cast<differenceType>(1), lastBuffer)) {
        this->addBuffer(static_cast<sizeType>(1));
    }
    ++this->last.construct(value);
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename Type>
inline void DataStructure::Deque<T, Allocator, BufferSize>::pushFrontAuxiliary(Type value) {
    if(this->first == iterator(this->buffer->begin(), this->buffer)) {
        this->addBuffer(static_cast<sizeType>(1), true);
    }
    --this->first.construct(value);
}
template <typename T, typename Allocator, unsigned long BufferSize>
inline void DataStructure::Deque<T, Allocator, BufferSize>::shrink(bool head) {
    auto oldSize {static_cast<differenceType>(this->size() + 1)};
    auto size {static_cast<sizeType>(0)};
    if(head) {
        auto maxIndex {this->bufferNumber - 1};
        for(auto i {0}; i < maxIndex; ++i) {
            auto buffer {this->buffer + static_cast<differenceType>(i)};
            if(iterator(buffer->end(), buffer) < this->first) {
                ++size;
                continue;
            }
            break;
        }
        auto lastBuffer {this->buffer + static_cast<differenceType>(maxIndex)};
        auto lastOffset {iterator(lastBuffer->end(), lastBuffer) - this->last};
        auto newBufferNumber {this->bufferNumber - size};
        auto newBuffer {new allocator[newBufferNumber]()};
        for(sizeType i {0}, j {size}; i < newBufferNumber; ++i, ++j) {
            newBuffer[i] = move(this->buffer[j]);
        }
        this->buffer = move(newBuffer);
        this->bufferNumber = move(newBufferNumber);
        lastBuffer = this->buffer + static_cast<differenceType>(this->bufferNumber - 1);
        this->last = iterator(lastBuffer->end() - lastOffset, lastBuffer);
        this->first = this->last - oldSize;
        return;
    }
    for(auto i {this->bufferNumber - 1}; i > 0; --i) {
        auto buffer {this->buffer + static_cast<differenceType>(i)};
        if(this->last < iterator(buffer->begin(), buffer)) {
            ++size;
            continue;
        }
        break;
    }
    auto firstOffset {this->first - iterator(this->buffer->begin(), this->buffer)};
    auto newBufferNumber {this->bufferNumber - size};
    auto newBuffer {new allocator[newBufferNumber]()};
    for(auto i {0}; i < newBufferNumber; ++i) {
        newBuffer[i] = move(this->buffer[i]);
    }
    this->free();
    this->buffer = move(newBuffer);
    this->bufferNumber = move(newBufferNumber);
    this->first = iterator(this->buffer->begin() + firstOffset, this->buffer);
    this->last = this->first + oldSize;
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::Deque() : Deque(static_cast<sizeType>(0)) {}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::Deque(sizeType size) : Deque(size, valueType()) {}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::Deque(sizeType size, constReference value) :
        bufferNumber {
            Deque::startSize(size + static_cast<sizeType>(Deque::bufferSize / 2 - Deque::preserveSize))
        } ,
        buffer {new allocator[this->bufferNumber]()},
        last {iterator(
                this->buffer->allocate(static_cast<sizeType>(bufferSize)) +
                static_cast<differenceType>(Deque::bufferSize / 2), this->buffer
              )},
        first {this->last - static_cast<differenceType>(1)} {
    this->initBuffer(static_cast<sizeType>(1));
    while(size--) {
        ++this->last.construct(value);
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
DataStructure::Deque<T, Allocator, BufferSize>::Deque(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last) :
        bufferNumber {Deque::startSize(IteratorDifference<InputIterator>()(first, last) +
                        static_cast<sizeType>(Deque::bufferSize / 2 - Deque::preserveSize))
        },
        buffer {new allocator[this->bufferNumber]()},
        last {iterator(
                this->buffer->allocate(static_cast<sizeType>(bufferSize)) +
                static_cast<differenceType>(Deque::bufferSize / 2), this->buffer
              )},
        first {this->last - static_cast<differenceType>(1)} {
    this->initBuffer(static_cast<differenceType>(1));
    while(first not_eq last) {
        ++this->last.construct(static_cast<valueType>(*first++));
    }
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::Deque(std::initializer_list<valueType> list) :
        Deque(list.begin(), list.end()) {}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::Deque(const Deque &rhs) :
        Deque(rhs.cbegin(), rhs.cend()) {}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::Deque(Deque &&rhs) noexcept :
        bufferNumber {rhs.bufferNumber}, buffer {rhs.buffer},
        last {rhs.last}, first {rhs.first} {
    rhs.buffer = nullptr;
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::~Deque() {
    this->free();
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize> &
DataStructure::Deque<T, Allocator, BufferSize>::operator=(const Deque &rhs) {
    auto temp {move(this->buffer)};
    try {
        this->buffer = new allocator[rhs.bufferNumber]();
    }catch(...) {
        this->buffer = move(temp);
        throw;
    }
    delete[] temp;
    this->bufferNumber = rhs.bufferNumber;
    auto firstTemp {move(this->first)};
    try {
        this->first = iterator(this->buffer.allocate(static_cast<sizeType>(bufferSize)), this->buffer) + (
                rhs.first - iterator(rhs.buffer->begin(), rhs.buffer)
        );
    }catch(...) {
        this->first = move(firstTemp);
        throw;
    }
    this->last = this->first + static_cast<differenceType>(1);
    for(auto &c : rhs) {
        ++this->last.construct(c);
    }
    return *this;
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize> &
DataStructure::Deque<T, Allocator, BufferSize>::operator=(Deque &&rhs) noexcept {
    if(this == &rhs) {
        return *this;
    }
    this->free();
    this->bufferNumber = rhs.bufferNumber;
    this->buffer = rhs.buffer;
    this->first = rhs.first;
    this->last = rhs.last;
    rhs.buffer = nullptr;
    return *this;
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize> &
DataStructure::Deque<T, Allocator, BufferSize>::operator=(std::initializer_list<valueType> list) {
    *this = Deque(list.begin(), list.end());
    return *this;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::reference
DataStructure::Deque<T, Allocator, BufferSize>::operator[](differenceType index) & {
    return this->first[++index];
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::constReference
DataStructure::Deque<T, Allocator, BufferSize>::operator[](differenceType index) const & {
    return static_cast<constReference>(const_cast<Deque &>(*this)[index]);
}
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::operator==(const Deque &rhs) const noexcept {
    return this->size() == rhs.size() and [](const Deque &lhs, const Deque &rhs) -> bool {
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
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::operator!=(const Deque &rhs) const noexcept {
    return not(*this == rhs);
}
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::operator<(const Deque &rhs) const noexcept {
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
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::operator<=(const Deque &rhs) const noexcept {
    return *this < rhs or *this == rhs;
}
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::operator>(const Deque &rhs) const noexcept {
    return not(*this <= rhs);
}
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::operator>=(const Deque &rhs) const noexcept {
    return not(*this < rhs);
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::operator+() const {
    auto temp {*this};
    for(auto &c : temp) {
        c = +c;
    }
    return temp;
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::operator-() const {
    auto temp {*this};
    for(auto &c : temp) {
        c = -c;
    }
    return temp;
}
template <typename T, typename Allocator, unsigned long BufferSize>
DataStructure::Deque<T, Allocator, BufferSize>::operator bool() const noexcept {
    return not this->empty();
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::assign(sizeType size, constReference value) {
    if(this->checkReserve(size) not_eq __Deque_CheckParameter::TAIL_SUCCESSFUL) {
        this->addBuffer(size);
    }
    auto cursor {this->first + static_cast<differenceType>(1)};
    while(size and cursor not_eq this->last) {
        cursor.destroy();
        ++cursor.construct(value);
        --size;
    }
    if(size) {
        while(size--) {
            ++this->last.construct(value);
        }
        return;
    }
    while(this->last not_eq cursor) {
        --this->last.destroy();
    }
    this->shrink();
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
void DataStructure::Deque<T, Allocator, BufferSize>::assign(
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    auto size {IteratorDifference<InputIterator>()(first, last)};
    if(this->checkReserve(size) not_eq __Deque_CheckParameter::TAIL_SUCCESSFUL) {
        this->addBuffer(size);
    }
    auto cursor {this->first + static_cast<differenceType>(1)};
    while(first not_eq last and cursor not_eq this->last) {
        cursor.destroy();
        ++cursor.construct(static_cast<valueType>(*first++));
    }
    if(first not_eq last) {
        while(first not_eq last) {
            ++this->last.construct(static_cast<valueType>(*first++));
        }
        return;
    }
    while(this->last not_eq cursor) {
        --this->last.destroy();
    }
    this->shrink();
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::assign(std::initializer_list<valueType> list) {
    this->assign(list.begin(), list.end());
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::valueType
DataStructure::Deque<T, Allocator, BufferSize>::at(differenceType n) const {
    return (*this)[n];
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::valueType
DataStructure::Deque<T, Allocator, BufferSize>::front() const {
    return *(this->first + static_cast<differenceType>(1));
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::valueType
DataStructure::Deque<T, Allocator, BufferSize>::back() const {
    return *(this->last - static_cast<differenceType>(1));
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::begin() const noexcept {
    return this->first + static_cast<differenceType>(1);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::constIterator
DataStructure::Deque<T, Allocator, BufferSize>::cbegin() const noexcept {
    return static_cast<constIterator>(this->first + static_cast<differenceType>(1));
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::end() const noexcept {
    return this->last;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::constIterator
DataStructure::Deque<T, Allocator, BufferSize>::cend() const noexcept {
    return static_cast<constIterator>(this->last);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::reverseIterator
DataStructure::Deque<T, Allocator, BufferSize>::rbegin() const noexcept {
    return reverseIterator(this->end() - 1);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::constReverseIterator
DataStructure::Deque<T, Allocator, BufferSize>::crbegin() const noexcept {
    return constReverseIterator(this->cend() - 1);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::reverseIterator
DataStructure::Deque<T, Allocator, BufferSize>::rend() const noexcept {
    return reverseIterator(this->first);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::constReverseIterator
DataStructure::Deque<T, Allocator, BufferSize>::crend() const noexcept {
    return constReverseIterator(static_cast<constIterator>(this->first));
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::sizeType
DataStructure::Deque<T, Allocator, BufferSize>::size() const noexcept {
    return this->last - this->first - 1;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::sizeType
DataStructure::Deque<T, Allocator, BufferSize>::capacity() const noexcept {
    sizeType count {0};
    for(auto i {0}; i < this->bufferNumber; ++i) {
        count += this->buffer[i].capacity();
    }
    return count - static_cast<sizeType>(Deque::preserveSize);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::sizeType
DataStructure::Deque<T, Allocator, BufferSize>::reserve() const noexcept {
    auto lastBuffer {this->buffer + (this->bufferNumber - 1)};
    return this->first - iterator(this->buffer->begin(), this->buffer) + static_cast<sizeType>(1) +
                (iterator(lastBuffer->end(), lastBuffer) - this->last) - static_cast<sizeType>(preserveSize);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::resize(sizeType size) {
    if(size <= static_cast<sizeType>(Deque::bufferSize) * this->bufferNumber) {
        return this->begin();
    }
    auto newBufferNumber {Deque::startSize(size)};
    auto newBuffer {new allocator[newBufferNumber]()};
    auto newFirst {
            iterator(newBuffer->allocate(static_cast<sizeType>(bufferSize)) +
            static_cast<differenceType>(1), newBuffer)
    };
    auto newLast {newFirst + static_cast<differenceType>(1)};
    for(auto i {1}; i < newBufferNumber; ++i) {
        newBuffer[i].allocate(static_cast<sizeType>(bufferSize));
    }
    while(++this->first not_eq this->last) {
        ++newLast.construct(move(*this->first));
        this->first.destroy();
    }
    this->free();
    this->buffer = move(newBuffer);
    this->bufferNumber = move(newBufferNumber);
    this->first = move(newFirst);
    this->last = move(newLast);
    return this->begin();
}
template <typename T, typename Allocator, unsigned long BufferSize>
bool DataStructure::Deque<T, Allocator, BufferSize>::empty() const noexcept {
    return this->last - this->first == static_cast<differenceType>(1);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::shrinkToFit() {
    if(not this->reserve()) {
        return this->begin();
    }
    auto newBuffer {new allocator[1ul]()};
    auto newFirst {
        iterator(newBuffer->allocate(
                                this->size() + static_cast<sizeType>(Deque::preserveSize)
                            ), newBuffer)
    };
    auto newLast {newFirst + static_cast<differenceType>(1)};
    while(++this->first < this->last) {
        ++newLast.construct(move(*this->first));
        this->first.destroy();
    }
    this->free();
    this->buffer = move(newBuffer);
    this->bufferNumber = static_cast<sizeType>(1);
    this->first = move(newFirst);
    this->last = move(newLast);
    return this->begin();
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::clear() noexcept(
        static_cast<bool>(typename __DataStructure_TypeTraits<valueType>::hasTrivialDestructor())
) {
    if(this->empty()) {
        return;
    }
    while(--this->last not_eq this->first) {
        this->last.destroy();
    }
    ++this->last;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(
        differenceType index, constReference value, sizeType size
) {
    if(not size) {
        return this->begin() + index;
    }
    if(not index) {
        while(size--) {
            this->pushFront(value);
        }
        return this->begin();
    }else if(index == this->size()) {
        for(auto i {0}; i < size; ++i) {
            this->pushBack(value);
        }
        return this->end() - static_cast<differenceType>(size);
    }
    return static_cast<differenceType>(this->size()) - index <= index ?
                this->insertAuxiliary<constReference>(index, value, size, true) :
                this->insertAuxiliary<constReference>(index, value, size, false);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(differenceType index, rightValueReference value) {
    if(not index) {
        this->pushFront(value);
        return this->begin();
    }else if(index == this->size()) {
        this->pushBack(value);
        return this->end() - static_cast<differenceType>(1);
    }
    return static_cast<differenceType>(this->size()) - index <= index ?
           this->insertAuxiliary<rightValueReference>(index, move(value), static_cast<sizeType>(1), true) :
           this->insertAuxiliary<rightValueReference>(index, move(value), static_cast<sizeType>(1), false);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(
        constIterator position, constReference value, sizeType size
) {
    return this->insert(position - this->first, value, size);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(constIterator position, rightValueReference value) {
    return this->insert(position - this->first, move(value));
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(differenceType index,
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    if(first == last) {
        return this->begin() + index;
    }
    if(not index) {
        while(first not_eq last) {
            this->pushFront(static_cast<valueType>(*first++));
        }
        return this->begin();
    }else if(index == this->size()) {
        auto size {IteratorDifference<InputIterator>()(first, last)};
        while(first not_eq last) {
            this->pushBack(static_cast<valueType>(*first++));
        }
        return this->end() - size;
    }
    return static_cast<differenceType>(this->size()) - index <= index ?
           this->insertAuxiliaryForIterator(index, first, last, true) :
           this->insertAuxiliaryForIterator(index, first, last, false);
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename InputIterator,
                typename DataStructure::__DataStructure_isInputIterator<InputIterator>::__result *
>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(constIterator position,
        typename __DataStructure_isInputIterator<InputIterator>::__result first, InputIterator last
) {
    return this->insert(position - this->begin(), first, last);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(
        differenceType index, std::initializer_list<valueType> list
) {
    return this->insert(index, list.begin(), list.end());
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::insert(
        constIterator position, std::initializer_list<valueType> list
) {
    return this->insert(position - this->begin(), list.begin(), list.end());
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::erase(differenceType index, sizeType size) {
    if(not size) {
        return this->begin() + index;
    }
    if(not index) {
        while(size--) {
            this->popFront();
        }
        return this->begin();
    }else if(index == this->size()) {
        while(size--) {
            this->popBack();
        }
        return this->end() - static_cast<differenceType>(1);
    }
    this->size() - static_cast<sizeType>(index) + size >= static_cast<sizeType>(index) ?
            this->eraseBackwardAuxiliary(index, size) :
            this->eraseForwardAuxiliary(index, size);
    return this->begin() + index;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::erase(constIterator position, sizeType size) {
    return this->erase(position - this->begin(), size);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::erase(constIterator first, constIterator last) {
    return this->erase(first - this->begin(), last - first);
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::pushFront(constReference value) {
    this->pushFrontAuxiliary<constReference>(value);
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::pushFront(rightValueReference value) {
    this->pushFrontAuxiliary<rightValueReference>(move(value));
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::pushBack(constReference value) {
    this->pushBackAuxiliary<constReference>(value);
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::pushBack(rightValueReference value) {
    this->pushBackAuxiliary<rightValueReference>(move(value));
}
template <typename T, typename Allocator, unsigned long BufferSize>
#ifdef POP_GET_OBJECT
typename DataStructure::Deque<T, Allocator, BufferSize>::valueType
#else
void
#endif
DataStructure::Deque<T, Allocator, BufferSize>::popFront() {
#ifdef POP_GET_OBJECT
    auto temp {move(*this->begin())};
#endif
    (++this->first).destroy();
    this->shrink(true);
#ifdef POP_GET_OBJECT
    return temp;
#endif
}
template <typename T, typename Allocator, unsigned long BufferSize>
#ifdef POP_GET_OBJECT
typename DataStructure::Deque<T, Allocator, BufferSize>::valueType
#else
void
#endif
DataStructure::Deque<T, Allocator, BufferSize>::popBack() {
#ifdef POP_GET_OBJECT
    auto temp {move(*(this->last - 1))};
#endif
    (--this->last).destroy();
    this->shrink();
#ifdef POP_GET_OBJECT
    return temp;
#endif
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename ...Args>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::emplace(differenceType index, Args &&...args) {
    return this->insert(index, valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename ...Args>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator
DataStructure::Deque<T, Allocator, BufferSize>::emplace(constIterator position, Args &&...args) {
    return this->insert(position - this->begin(), valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename ...Args>
void DataStructure::Deque<T, Allocator, BufferSize>::emplaceFront(Args &&...args) {
    this->pushFront(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator, unsigned long BufferSize>
template <typename ...Args>
void DataStructure::Deque<T, Allocator, BufferSize>::emplaceBack(Args &&...args) {
    this->pushBack(valueType(std::forward<Args>(args)...));
}
template <typename T, typename Allocator, unsigned long BufferSize>
void DataStructure::Deque<T, Allocator, BufferSize>::swap(Deque &rhs) noexcept {
    using std::swap;
    swap(this->bufferNumber, rhs.bufferNumber);
    swap(this->buffer, rhs.buffer);
    auto temp {move(this->first)};
    this->first = move(rhs.first);
    rhs.first = move(temp);
    temp = move(this->last);
    this->last = move(rhs.last);
    rhs.last = move(temp);
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::bufferType
DataStructure::Deque<T, Allocator, BufferSize>::getAllocator() const & noexcept {
    return this->buffer;
}

#ifdef DEBUG_DATA_STRUCTURE_FOR_DEQUE
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::sizeType &
DataStructure::Deque<T, Allocator, BufferSize>::getBufferNumber() & noexcept {
    return this->bufferNumber;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::bufferType &
DataStructure::Deque<T, Allocator, BufferSize>::getBuffer() & noexcept {
    return this->buffer;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator &
DataStructure::Deque<T, Allocator, BufferSize>::getFirst() & noexcept {
    return this->first;
}
template <typename T, typename Allocator, unsigned long BufferSize>
typename DataStructure::Deque<T, Allocator, BufferSize>::iterator &
DataStructure::Deque<T, Allocator, BufferSize>::getLast() & noexcept {
    return this->last;
}
#endif

#endif //DATA_STRUCTURE_DEQUE_HPP
