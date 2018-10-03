#ifndef DATA_STRUCTURE_TYPETRAITS_HPP
#define DATA_STRUCTURE_TYPETRAITS_HPP

namespace DataStructure {
    template <typename T>
    struct removePointer {
        using type = T;
    };
    template <typename T>
    struct removePointer<T *> {
        using type = T;
    };
    template <typename T>
    struct removePointer<const T *> {
        using type = const T;
    };
    template <typename T>
    struct removeReference {
        using type = T;
    };
    template <typename T>
    struct removeReference<T &> {
        using type = T;
    };
    template <typename T>
    struct removeReference<T &&> {
        using type = T;
    };
    struct NotIterator {
        constexpr static bool isInputIterator {false};
        constexpr static bool isOutputIterator {false};
        constexpr static bool isForwardIterator {false};
        constexpr static bool isBidirectionalIterator {false};
        constexpr static bool isRandomAccessIterator {false};
    };
    struct InputIterator {
        constexpr static bool isInputIterator {true};
        constexpr static bool isOutputIterator {false};
        constexpr static bool isForwardIterator {false};
        constexpr static bool isBidirectionalIterator {false};
        constexpr static bool isRandomAccessIterator {false};
    };
    struct OutputIterator {
        constexpr static bool isInputIterator {false};
        constexpr static bool isOutputIterator {true};
        constexpr static bool isForwardIterator {false};
        constexpr static bool isBidirectionalIterator {false};
        constexpr static bool isRandomAccessIterator {false};
    };
    struct ForwardIterator : public InputIterator, public OutputIterator {
        constexpr static bool isInputIterator {InputIterator::isInputIterator};
        constexpr static bool isOutputIterator {OutputIterator::isOutputIterator};
        constexpr static bool isForwardIterator {true};
        constexpr static bool isBidirectionalIterator {false};
        constexpr static bool isRandomAccessIterator {false};
    };
    struct BidirectionalIterator : public ForwardIterator {
        constexpr static bool isInputIterator {ForwardIterator::isInputIterator};
        constexpr static bool isOutputIterator {ForwardIterator::isOutputIterator};
        constexpr static bool isForwardIterator {ForwardIterator::isForwardIterator};
        constexpr static bool isBidirectionalIterator {true};
        constexpr static bool isRandomAccessIterator {false};
    };
    struct RandomAccessIterator : public BidirectionalIterator {
        constexpr static bool isInputIterator {BidirectionalIterator::isInputIterator};
        constexpr static bool isOutputIterator {BidirectionalIterator::isOutputIterator};
        constexpr static bool isForwardIterator {BidirectionalIterator::isForwardIterator};
        constexpr static bool isBidirectionalIterator {BidirectionalIterator::isBidirectionalIterator};
        constexpr static bool isRandomAccessIterator {true};
    };
    struct __DataStructure_trueType {
        constexpr bool operator()() const noexcept {
            return true;
        }
        explicit constexpr operator bool() const noexcept {
            return true;
        }
    };
    struct __DataStructure_falseType {
        constexpr bool operator()() const noexcept {
            return false;
        }
        explicit constexpr operator bool() const noexcept {
            return false;
        }
    };
    template <typename T>
    struct __DataStructure_isPointer {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct __DataStructure_isPointer<T *> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct __DataStructure_isPointer<T *&> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct __DataStructure_isPointer<T *const> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct __DataStructure_typeTraits {
        using hasTrivialDefaultConstructor = __DataStructure_falseType;
        using hasTrivialCopyConstructor = __DataStructure_falseType;
        using hasTrivialMoveConstructor = __DataStructure_falseType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_falseType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_falseType;
        using hasTrivialDestructor = __DataStructure_falseType;
        using is_POD_type = __DataStructure_falseType;
    };
    template <typename T>
    struct __DataStructure_typeTraits<T *> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<unsigned int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<short int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<unsigned short int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<char> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<signed char> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<unsigned char> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<char16_t> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<char32_t> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<wchar_t> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<unsigned long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<long long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<unsigned long long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<float> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<double> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_typeTraits<long double> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <typename, bool>
    struct __DataStructure_IteratorTraits {
        using sizeType = void;
        using differenceType = void;
        using valueType = void;
        using reference = void;
        using constReference = void;
        using rightValueReference = void;
        using pointer = void;
        using constPointer = void;
        using iteratorTag = NotIterator;
    };
    template <typename Iterator>
    struct __DataStructure_IteratorTraits<Iterator, false> {
        using sizeType = typename Iterator::sizeType;
        using differenceType = typename Iterator::differenceType;
        using valueType = typename Iterator::valueType;
        using reference = typename Iterator::reference;
        using constReference = typename Iterator::constReference;
        using rightValueReference = typename Iterator::rightValueReference;
        using pointer = typename Iterator::pointer;
        using constPointer = typename Iterator::constPointer;
        using iteratorTag = typename Iterator::iteratorTag;
    };
    template <typename T, bool POD>
    struct __DataStructure_IteratorTraits<T *, POD> {
        using sizeType = unsigned long;
        using differenceType = long;
        using valueType = T;
        using reference = valueType &;
        using constReference = const valueType &;
        using rightValueReference = valueType &&;
        using pointer = valueType *;
        using constPointer = const valueType *;
        using iteratorTag = RandomAccessIterator;
    };
    template <typename, bool>
    struct __DataStructure_InputIteratorInferringAuxiliary {
        using __type = __DataStructure_falseType;
    };
    template <typename Iterator>
    struct __DataStructure_InputIteratorInferringAuxiliary<Iterator, true> {
        using __type = Iterator;
    };
    template <typename Iterator>
    struct __DataStructure_isInputIterator {
        using __result = typename __DataStructure_InputIteratorInferringAuxiliary<Iterator,
                __DataStructure_IteratorTraits<Iterator, static_cast<bool>(
                                typename __DataStructure_typeTraits<Iterator>::is_POD_type()
                        )>::iteratorTag::isInputIterator
        >::__type;
    };
    template <typename, bool>
    struct __DataStructure_OutputIteratorInferringAuxiliary {
        using __type = __DataStructure_falseType;
    };
    template <typename Iterator>
    struct __DataStructure_OutputIteratorInferringAuxiliary<Iterator, true> {
        using __type = Iterator;
    };
    template <typename Iterator>
    struct __DataStructure_isOutputIterator {
        using __result = typename __DataStructure_OutputIteratorInferringAuxiliary<Iterator,
                __DataStructure_IteratorTraits<Iterator, static_cast<bool>(
                        typename __DataStructure_typeTraits<Iterator>::is_POD_type()
                )>::iteratorTag::isOutputIterator
        >::__type;
    };
    template <typename, bool>
    struct __DataStructure_ForwardIteratorInferringAuxiliary {
        using __type = __DataStructure_falseType;
    };
    template <typename Iterator>
    struct __DataStructure_ForwardIteratorInferringAuxiliary<Iterator, true> {
        using __type = Iterator;
    };
    template <typename Iterator>
    struct __DataStructure_isForwardIterator {
        using __result = typename __DataStructure_ForwardIteratorInferringAuxiliary<Iterator,
                __DataStructure_IteratorTraits<Iterator, static_cast<bool>(
                        typename __DataStructure_typeTraits<Iterator>::is_POD_type()
                )>::iteratorTag::isForwardIterator
        >::__type;
    };
    template <typename, bool>
    struct __DataStructure_BidirectionalIteratorInferringAuxiliary {
        using __type = __DataStructure_falseType;
    };
    template <typename Iterator>
    struct __DataStructure_BidirectionalIteratorInferringAuxiliary<Iterator, true> {
        using __type = Iterator;
    };
    template <typename Iterator>
    struct __DataStructure_isBidirectionalIterator {
        using __result = typename __DataStructure_BidirectionalIteratorInferringAuxiliary<Iterator,
                __DataStructure_IteratorTraits<Iterator, static_cast<bool>(
                        typename __DataStructure_typeTraits<Iterator>::is_POD_type()
                )>::iteratorTag::isBidirectionalIterator
        >::__type;
    };
    template <typename, bool>
    struct __DataStructure_RandomAccessIteratorInferringAuxiliary {
        using __type = __DataStructure_falseType;
    };
    template <typename Iterator>
    struct __DataStructure_RandomAccessIteratorInferringAuxiliary<Iterator, true> {
        using __type = Iterator;
    };
    template <typename Iterator>
    struct __DataStructure_isRandomAccessIterator {
        using __result = typename __DataStructure_RandomAccessIteratorInferringAuxiliary<Iterator,
                __DataStructure_IteratorTraits<Iterator, static_cast<bool>(
                        typename __DataStructure_typeTraits<Iterator>::is_POD_type()
                )>::iteratorTag::isRandomAccessIterator
        >::__type;
    };
    template <typename T>
    constexpr typename removeReference<T>::type &&move(T &&value) noexcept {
        return static_cast<typename removeReference<T>::type &&>(value);
    }
}

#endif //DATA_STRUCTURE_TYPETRAITS_HPP
