#ifndef DATA_STRUCTURE_VECTOR_HPP
#define DATA_STRUCTURE_VECTOR_HPP

#include "Base.hpp"

namespace DataStructure {
#ifdef WANT_TO_BE_JONNY_SON     //Derive my class and don't want to be my sons. Any perfect things like this? FUCK OFF!
    template <typename T>
    class Vector: private ArrayBase<T> {
#else
    template <typename T>
    class Vector final : private ArrayBase<T> {
#endif
        /* The function is used to swap two Vectors. */
        friend void swap(Vector<T> &a, Vector<T> &b) {
            using std::swap;        //Using the STL swap function to avoid duplicate codes.
            swap(a.allocateSize, b.allocateSize);
            swap(a.array, b.array);
            swap(a.first, b.first);
            swap(a.cursor, b.cursor);
            swap(a.end, b.end);
        }
    private:
        bool checkFull() const override;        //Check whether the Memory allocator is full.
        void reallocate() override;     //If the Memory allocator is filled with the elements, then allot a bigger memory.
        void free() override;       //Free the memory holding.
        void allocate() override;       //Allocate the memory by this->allocateSize.
        T *backup(T *, size_t, bool = false);       //Backup the elements before inserting or erasing.
    public:
        Vector();       //Default constructor.
        explicit Vector(size_t, const T &);     //Explicit constructor, calling it for create a number of initial data.
        /* Deleted to avoid ambiguous calling. */
        /*template <typename ...ARGS>
        explicit Vector(ARGS &&...) noexcept;       //Explicit constructor, calling it for putting a list of initial data.
                                                        The data can be right-value or left-value. It is conflict with
                                                        constructor Vector(T &&, size_t) noexcept / Vector(T &&) noexcept
                                                        and Vector(std::initializer_list<T>), so it is deleted.
        explicit Vector(T &&, size_t = 1) noexcept;     //Explicit constructor, calling it for initializing with a
                                                            number of data. It is conflict with constructor
                                                            template <typename T>Vector(ARGS &&, size_t) noexcept and
                                                            Vector(T &&) noexcept and Vector(std::initializer_list<T>),
                                                            so it is deleted.
        explicit Vector(T &&) noexcept;*/       //Explicit constructor, calling it for initializing with a data.
                                                    // It may conflict with Vector(size_t), so it is deleted.
        explicit Vector(size_t);        //Explicit constructor, call it for initializing with a number of default data.
        Vector(const T *, const T *);       //Initialize the Vector with a range of data provided with two range of pointers.
        Vector(std::initializer_list<T>);       //Initialize with initializer_list.
        Vector(const Vector &);     //Copy constructor.
        Vector(Vector &&) noexcept;     //Move constructor.
        ~Vector();      //Destructor.
        Vector &operator=(const Vector &);      //Copy assignment operator. Overload with assignment operator =.
        Vector &operator=(Vector &&) noexcept;      //Move assignment operator. Overload with assignment operator =.
        T &operator[](unsigned n) const &;      //Array indexing operator used to return a reference from the this->array. Overload with array indexing operator [].
        bool operator<(const Vector &) const;       //Comparison operator. Return true when *this has less elements. When two Vectors has same size, return true when *this' first different element is less than another.
        bool operator<=(const Vector &) const;      //Comparison operator. Returning is similar to overloading operator <, The function's returning can be inferred with overloading operator < and itself.
        bool operator>(const Vector &) const;       //Comparison operator. Returning is similar to overloading operator <, The function's returning can be inferred with overloading operator < and itself.
        bool operator>=(const Vector &) const;      //Comparison operator. Returning is similar to overloading operator <, The function's returning can be inferred with overloading operator < and itself.
        bool operator==(const Vector &) const;      //Comparison operator. Return true when two Vectors have a identical size and every element is same to another.
        bool operator!=(const Vector &) const;      //Comparison operator. Return the converse result of overloading operator ==.
        explicit operator bool() const;     //Type conversions operator. Return true when there are elements in Vector.
        Vector &operator-();
        Vector &operator+();
        using iterator = typename ArrayBase<T>::pointer;
        using constIterator = typename ArrayBase<T>::constPointer;
    public:
#ifdef POP_GET_NUMBER       //Define POP_GET_NUMBER means want to pop functions return a number that is popped just now.
        T
#else
        void
#endif
            popBack();      //Pop from the last element.
#ifdef POP_GET_NUMBER
        T
#else
        void
#endif
            popFront();     //Pop from the first element.
        void pushBack(const T &);       //Push the element from the last.
        void pushFront(const T &);      //Push the element from the first.
        T at(unsigned n) const;     //Get a copy element from the array using specific indexing input by template-code-users.
        bool isEmpty() const;       //Return whether the Vector is empty or not.
        void clear();       //Clear the Vector.
        T const *insert(const T &, unsigned, size_t = 1);       //Insert a number of elements to a specific position by left-value.
        T const *insert(T &&, unsigned);        //Insert a element to a specific position by right-value.
        const T *const getConstantBegin() const;        //Get the constant constant-iterator from the beginning.
        const T *const getConstantEnd() const;      //Get the constant constant-iterator from the ending.
        T const *getBegin() const;      //Get the constant-iterator from the beginning.
        T const *getEnd() const;        //Get the constant-iterator from the ending.
        template <typename ...ARGS>
        T const *emplace(unsigned, ARGS &&...);        //Emplace a non-construct element to a specific position.
        template <typename ...ARGS>
        T const *emplaceBack(ARGS &&...) noexcept;      //Emplace a non-construct element to the last of Vector.
        template <typename ...ARGS>
        T const *emplaceFront(ARGS &&...) noexcept;     //Emplace a nopn-construct element to the beginning of Vetcor.
        T const *erase(unsigned, size_t = 1);       //Erase a number of elements from specific positions.
        size_t size() const;        //Return the size of Vector.
        const T front() const;      //Get the copy of first element.
        const T back() const;       //Get the copy of last element.
#ifdef OTHER_FUNCTION       //Those function shouldn't be used casually
    public:
        ptrdiff_t find(const T &) const;        //Find a element whether is in the Vector or not.
        template <typename ...ARGS>
        bool find(const T &, const ARGS &...) const;       //Find a number of elements whether is in the Vector or not.
        Vector<T> get(unsigned, size_t) const;      //Get a part of elements from Vector.
        void resize(size_t, bool = false);        //Reallocate memory by a number that specified by code-users. If the number is less than this->allocateSize, it will do nothing.
        ptrdiff_t reserve() const;      //Get the number of reserved memory.
        ptrdiff_t capacity() const;     //Get the capability of Vector.
        void shrinkToFit();     //Free the memory that is only allocated.
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR      //Those functions only used in debug Vector. It will destroy the encapsulation of class.
    public:
        std::allocator<T> *getInwardAllocator() const;      //Get the allocator.
        T *getInwardFirst() const;      //Get the pointer of first.
        T *getInwardCursor() const;     //Get the pointer of cursor.
        T *getInwardEnd() const;        //Get the pointer of end.
#endif
    };
}

#endif //DATA_STRUCTURE_VECTOR_HPP
