#ifndef DATA_STRUCTURE_TYPETRAITS_HPP
#define DATA_STRUCTURE_TYPETRAITS_HPP

namespace DataStructure {
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
    struct RemovePointer {
        using type = T;
    };
    template <typename T>
    struct RemovePointer<T *> {
        using type = T;
    };
    template <typename T>
    struct RemovePointer<T *const> {
        using type = T;
    };
    template <typename T>
    struct RemovePointer<T *volatile> {
        using type = T;
    };
    template <typename T>
    struct RemovePointer<T *const volatile> {
        using type = T;
    };
    template <typename T>
    struct RemoveConst {
        using type = T;
    };
    template <typename T>
    struct RemoveConst<const T> {
        using type = T;
    };
    template <typename T>
    struct RemoveReference {
        using type = T;
    };
    template <typename T>
    struct RemoveReference<T &> {
        using type = T;
    };
    template <typename T>
    struct RemoveReference<T &&> {
        using type = T;
    };
    template <typename T>
    struct IsReference {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsReference<T &> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsReference<T &&> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsLeftValueReference {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsLeftValueReference<T &> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsRightValueReference {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsRightValueReference<T &&> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsConst {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsConst<const T> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsPointer {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsPointer<T *> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsPointer<T *const> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsPointer<T *volatile> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsPointer<T *const volatile> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsConstReference {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsConstReference<const T &> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct IsConstPointer {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsConstPointer<const T *> {
        using result = __DataStructure_trueType;
    };
    template <typename T, typename U>
    struct IsSame {
        using result = __DataStructure_falseType;
    };
    template <typename T>
    struct IsSame<T, T> {
        using result = __DataStructure_trueType;
    };
    template <typename T>
    struct AddConst {
        using result = const T;
    };
    template <typename T,
                    bool = static_cast<bool>(typename IsLeftValueReference<T>::result()),
                    bool = static_cast<bool>(typename IsRightValueReference<T>::result()),
                    bool = static_cast<bool>(typename IsPointer<T>::result())
             >
    struct AddLowLevelConst {};
    template <typename T>
    struct AddLowLevelConst<T, true, false, false> {
        using result = const typename RemoveReference<T>::type &;
    };
    template <typename T>
    struct AddLowLevelConst<T, false, true, false> {
        using result = const typename RemoveReference<T>::type &&;
    };
    template <typename T>
    struct AddLowLevelConst<T, false, false, true> {
        using result = const typename RemovePointer<T>::type *;
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
    template <typename T>
    struct __DataStructure_TypeTraits {
        using hasTrivialDefaultConstructor = __DataStructure_falseType;
        using hasTrivialCopyConstructor = __DataStructure_falseType;
        using hasTrivialMoveConstructor = __DataStructure_falseType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_falseType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_falseType;
        using hasTrivialDestructor = __DataStructure_falseType;
        using is_POD_type = __DataStructure_falseType;
    };
    template <typename T>
    struct __DataStructure_TypeTraits<T *> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<unsigned int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<short int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<unsigned short int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<char> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<signed char> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<unsigned char> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<char16_t> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<char32_t> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<wchar_t> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<unsigned long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<long long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<unsigned long long int> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<float> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<double> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <>
    struct __DataStructure_TypeTraits<long double> {
        using hasTrivialDefaultConstructor = __DataStructure_trueType;
        using hasTrivialCopyConstructor = __DataStructure_trueType;
        using hasTrivialMoveConstructor = __DataStructure_trueType;
        using hasTrivialCopyAssignmentOperator = __DataStructure_trueType;
        using hasTrivialMoveAssignmentOperator = __DataStructure_trueType;
        using hasTrivialDestructor = __DataStructure_trueType;
        using is_POD_type = __DataStructure_trueType;
    };
    template <typename, bool>
    struct __DataStructure_IteratorTraitsAuxiliary {
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
    struct __DataStructure_IteratorTraitsAuxiliary<Iterator, false> {
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
    struct __DataStructure_IteratorTraitsAuxiliary<T *, POD> {
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
    template <typename Iterator>
    using __DataStructure_IteratorTraits = __DataStructure_IteratorTraitsAuxiliary<Iterator,
            static_cast<bool>(typename __DataStructure_TypeTraits<Iterator>::is_POD_type())
    >;
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
                __DataStructure_IteratorTraits<Iterator>::iteratorTag::isInputIterator
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
                __DataStructure_IteratorTraits<Iterator>::iteratorTag::isOutputIterator
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
                __DataStructure_IteratorTraits<Iterator>::iteratorTag::isForwardIterator
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
                __DataStructure_IteratorTraits<Iterator>::iteratorTag::isBidirectionalIterator
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
                __DataStructure_IteratorTraits<Iterator>::iteratorTag::isRandomAccessIterator
        >::__type;
    };
    template <typename T>
    constexpr typename RemoveReference<T>::type &&move(T &&value) noexcept {
        return static_cast<typename RemoveReference<T>::type &&>(value);
    }
    template <typename Iterator, bool>
    struct __DataStructure_IteratorDifferenceAuxiliary {
        static_assert(__DataStructure_IteratorTraits<Iterator>::iteratorTag::isInputIterator,
                        "The template argument should be an input iterator at least!"
                );
        using differenceType = typename __DataStructure_IteratorTraits<Iterator>::differenceType;
        differenceType operator()(Iterator first, Iterator last) const noexcept {
            differenceType count {0};
            while(first not_eq last) {
                ++first;
                ++count;
            }
            return count;
        }
    };
    template <typename Iterator>
    struct __DataStructure_IteratorDifferenceAuxiliary<Iterator, true> {
        static_assert(__DataStructure_IteratorTraits<Iterator>::iteratorTag::isRandomAccessIterator,
                        "The template argument should be an iterator which is able to random accessed"
                );
        using differenceType = typename __DataStructure_IteratorTraits<Iterator>::differenceType;
        differenceType operator()(Iterator first, Iterator last) const noexcept {
            return last - first;
        }
    };
    template <typename Iterator>
    using IteratorDifference = __DataStructure_IteratorDifferenceAuxiliary<Iterator,
                    __DataStructure_IteratorTraits<Iterator>::iteratorTag::isRandomAccessIterator
            >;
    template <typename T, bool = static_cast<bool>(typename IsPointer<T>::result()),
                bool = typename IsConst<typename RemovePointer<
                                            typename RemoveReference<T>::type
                                       >::type>::result()()
             >
    struct __DataStructure_ConstOrNonConst {
        using __result = typename RemoveConst<typename RemovePointer<T>::type>::type *;
    };
    template <typename T>
    struct __DataStructure_ConstOrNonConst<T, false, false> {
        using __result = const typename RemoveReference<T>::type &;
    };
    template <typename T>
    struct __DataStructure_ConstOrNonConst<T, false, true> {
        using __result = typename RemoveConst<typename RemoveReference<T>::type>::type &;
    };
    template <typename T>
    struct __DataStructure_ConstOrNonConst<T, true, false> {
        using __result = const typename RemovePointer<T>::type *;
    };
    template <typename T>
    struct __DataStructure_TemplateTypeTraits {};
    template <template <typename ...>
                class S, typename ...Args>
    struct __DataStructure_TemplateTypeTraits<S<Args...>> {
        template <typename ...ResultArgs>
        using __result = S<ResultArgs...>;
    };
}

#endif //DATA_STRUCTURE_TYPETRAITS_HPP
