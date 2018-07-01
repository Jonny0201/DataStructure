#ifndef DATA_STRUCTURE_TYPETRAITS_HPP
#define DATA_STRUCTURE_TYPETRAITS_HPP

namespace DataStructure {
    /* remove pointer */
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
    /* remove reference */
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
    /* Iterator */
    struct InputIterator {};
    struct OutputIterator {};
    struct ForwardIterator : virtual public InputIterator, virtual public OutputIterator {};
    struct BidirectionalIterator : public ForwardIterator {};
    struct RandomAccessIterator : public BidirectionalIterator {};
}

#endif //DATA_STRUCTURE_TYPETRAITS_HPP
