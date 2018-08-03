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
    struct removePointer<T *const> {
        using type = T;
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
    struct InputIterator {};
    struct OutputIterator {};
    struct ForwardIterator : virtual public InputIterator, virtual public OutputIterator {};
    struct BidirectionalIterator : public ForwardIterator {};
    struct RandomAccessIterator : public BidirectionalIterator {};
    struct __DataStructure_trueType {};
    struct __DataStructure_falseType {};
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
}

#endif //DATA_STRUCTURE_TYPETRAITS_HPP
