# ::DataStructure::Vector

### Vector Refactored!

Just like C++ Standard Template Library, `Vector` is a multifunction array. All the elements from `Vector` is stored contiguously which means you can visit element easily but inserting or erasing elements will be time-consuming. If the elements that need to be saved with only a little operating of erasing or inserting and with a lot of operating of visits or changes, then you should consider using Vector to store them.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't declare `DataStructure` by `using namespace DataStructure`.

The refactoring is to simply for class users. So now you needn't include two files like
`#include "Vector.hpp"` and `#include "Vector.cpp"`. It is in the one file now `Vector.hpp`.

Till 2nd July, 2018, it still haven't been tested seriously (I tested `int` and `simple` class like

```cpp
struct s {
    int a;
    char b;
};
```

So if you want to include this in yourself programme, you should test it carefully at first.

This time I add an `Allocator` for Vector not only relying on STL's `std::allocator`. However, what you should pay attention is that there are an abundance of discrepancies between the Allocator `Vector` need and STL's `std::allocator`, which suggests C++'s standard allocator cannnot be compatible with `DataStructure::Vector`. If you want Vector use your allocator, then you should read the portion for `Allocator` from DataStructure's documentation carefully and try your best to read how I write `DataStructure::Allocator`.

I also delete the comments due to the reason that I have described all details in this documentation for `DataStructure::Vector`. I think my coding style is nice for reading cooperating with the documentation.

## Definition

`template <typename T, typename Alloc = DataStructure::Allocator<T>>`

 `class Vector final;`

`final` prohibits anyone inherit from this class.


## Member types

>- `valueType` <-> `T`
>- `constType` <-> `const T`
>- `reference` <-> `T &`
>- `constReference` <-> `const T &`
>- `pointer` <-> `T *`
>- `constPointer` <-> `const T *`
>- `constPointerConstant` <-> `const T *const`
>- `rightValueReference` <-> `T &&`
>- `iterator` <-> `DataStructure::Vector::Iterator`
>- `constIterator` <-> `const DataStructure::Vector::Iterator`
>- `iteratorReference` <-> `DataStructure::Vector::Iterator &`
>- `allocator` <-> `Alloc`
>- `differenceType` <-> `ptrdiff_t`
>- `sizeType` <-> `size_t`

## Constructor and Destructor

```cpp
1. Vector();        //Default constructor.
2. Vector(sizeType, constReference);
3. explicit Vector(sizeType);
4. Vector(iterator, iterator);
5. Vector(pointer , pointer);
6. Vector(std::initializer_list<valueType>);
7. explicit Vector(const Alloc &);
8. Vector(const Vector &);        //Copy constructor.
9. Vector(Vector &&) noexcept;        //Move constructor.
```

  1) Default constructor. Constructs a new empty `Vector`.
  2) Constructs the `Vector` with count copies of elements with value.
  3) Constructs the `Vector` with count copies of elements with default value `valueType()`.
  4) Constructs the `Vector` with a range of elements that is provided by a range iterator.
  5) Constructs the `Vector` with a range of elements that is provided by a range pointer.
  6) Constructs the `Vector` with the `std::initializer_list`.
  7) Constructs the `Vector` with other allocator.
  8) Copy constructor. Constructs the `Vector` with other `Vector` by copying the elements from other `Vector`.
  9) Move constructor. Constructs the `Vector` with other `Vector` by moving the elements from other `Vector`.

## Operator
```cpp
1. Vector &operator=(const Vector &);        //Copy assignment operator.
2. Vector &operator=(Vector &&) noexcept;        //Move assignment operator.
3. reference operator[](differenceType) const &;
4. bool operator<(const Vector &) const;
5. bool operator<=(const Vector &) const;
6. bool operator>(const Vector &) const;
7. bool operator>=(const Vector &) const;
8. bool operator==(const Vector &) const;
9. bool operator not_eq(const Vector &) const;        //not_eq <-> !=
10. explicit operator bool() const;
11. Vector &operator+();
12. Vector &operator-();
```

  3\) The operator is like arrays' indexing operator, it return a reference of indexing elements.<br />

  4\) -- 7\) The comparison operator is different from the operator of C++ Standard Template Library's `std::vector`. I will introduce in operator `<` for example. For the other operators, you can analogize from operator `<`. Now assumed that there is a `Vector` named A and an another `Vector` named B that is going to compare with `Vector` A. First, the function will compare the size of two `Vector`, that the `Vector` A has a bigger size will return false as result. If two `Vector`s have the same sizes then will compare every element, till find a position that two `Vector`s have a different element from each other, then compare which element. If `Vector` A's element is smaller, then return true.<br />

    > Tip : The type of Vector should support the operator then the overloading operators will work, or will make a compile error.

  8\) -- 9\) Only two `Vector`s have the same sizes and every position's element is identical then the operator `==` will return true, else the operator `!=` will return true.<br />

  10\) It is common to use the operator `bool()` in the condition statements to judge whether the `Vector` is empty or not.

## Function
```cpp
1. valueType popBack();        //Returning value depends on macro.
2. void popBack();
3. valueType popFront();        //Returning value depends on macro.
4. void popFront();
5. void pushBack(constReference);
6. void pushFront(constReference);
7. valueType at(differenceType) const;
8. bool empty() const;
9. void clear();
10. iterator insert(constReference, differenceType, sizeType = 1);
11. iterator insert(constReference, constIterator, sizeType = 1);
12. template <typename ForwardIterator>
    iterator insert(constIterator, ForwardIterator, ForwardIterator);
13. iterator insert(constIterator, std::initializer_list<valueType>);
14. template <typename ...Args>
    iterator emplace(differenceType, Args &&...) noexcept;
15. template <typename ...Args>
    iterator emplaceBack(Args &&...) noexcept;
16. template <typename ...Args>
    iterator emplaceFront(Args &&...) noexcept;
17. iterator erase(differenceType, sizeType = 1);
18. iterator erase(constIterator);
20. sizeType size() const;
21. valueType front() const;
22. valueType back() const;
23. iterator begin() const;
24. iterator end() const;
25. constIterator constBegin() const;
26. constIterator constEnd() const;
```

As you can see, what every function does is like what the name every function holds.

> Refactoring : <br />
    > - `insert` and `emplace` will return `iterator` instead of pointer, which is safer. <br />
    > - `isEmpty` is renamed to `empty`. <br />
    > - `getBegin`, `getEnd` is renamed to `begin` and `end`. You can put `Vector` in **Range-For** (C++ 11). <br />

## Iterator for `Vetcor`

The iterator from `Vector` is a random access iterator.

Operator supports :
```cpp
1. reference operator*() const;
2. pointer operator->() const;
3. Iterator &operator++();
4. Iterator operator++(int);
5. Iterator &operator--();
6. Iterator operator--(int);
7. reference operator[](differenceType);
8. bool operator==(const Iterator &) const;
9. bool operator not_eq(const Iterator &) const;        //not_eq <-> !=
10. bool operator<(const Iterator &) const;
11. bool operator<=(const Iterator &) const;
12. bool operator>(const Iterator &) const;
13. bool operator>=(const Iterator &) const;
14. Iterator operator+(differenceType) const;
15. Iterator operator-(differenceType) const;
16. friend differenceType operator-(const Iterator &, const Iterator &);
```

<br /> Tip : function ~~differenceType operator-(const Iterator &) const;~~ has been deleted.


## Advanced Function

These functions is what I don't want anyone who uses casually. If you want to call these functions, you should declare a macro variable named `OTHER_FUNCTION` :

`#define OTHER_FUNCTION`

```cpp
1. iterator find(constReference) const;
2. template <typename ...Args>
   bool find(constReference, const Args &...) const;
3. Vector get(differenceType, sizeType) const;
4. void resize(sizeType);
5. sizeType reserve() const;
6. void shrinkToFit();
7. sizeType capacity() const;
```
  1\) Find the element in the `Vector` (Refactoring : Returning iterator instead of returning position).<br />
  2\) Find all elements in the `Vector`, only that all elements exist in Vector will return true.<br />
  3\) Get the element list and put the list into a new `Vector` then return it.<br />
  4\) Comparing the provided `allocateSize` and existing `allocateSize` from the class. Reallocate the memory of the `Vector` when the provided `allocateSize` is greater than existing `allocateSize` from the class (Refactoring : The function's work has delegated to `Allocator`).<br />
  5\) Get the information that how many vacancies are in the `Vector`.<br />
  6\) Free the memory that occupied by vacancies and hasn't been used (Refactoring : The function's work has delegated to `Allocator`).
  7\) Get the information that how many positions altogether are in the `Vector` (Refactoring : The function's work has delegated to `Allocator`).<br />

## Debug Function

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should declare a macro variable named `DEBUG_DATA_STRUCTURE_FOR_VECTOR` :

`#define DEBUG_DATA_STRUCTURE_FOR_VECTOR`

```cpp
1. allocator &getAllocator() const;
2. auto getFirst() const -> decltype(this->array.getFirst());
3. auto getCursor() const -> decltype(this->array.getCursor());
4. auto getEnd() const -> decltype(this->array.getEnd());
5. sizeType &getAllocateSize() const;
```

## Problem Exists

Though the `Vector` is finished and it can be used now, it still exists many problems :

- Constructor `Vector(iterator, iterator);` should accept any iterator including pointers not only the iterators from `Vector`.
- There isn't a reserve iterator in `Vector`.
- Any unknown error.

If you find any error in the `Vector`, please tell me!

## Updates

### 3rd May, 2018 Update :
The bug that when two Vectors is equal but the operator `<=` would return false now is fixed.
Simplify the code of the operators `<=` and `>=` by using the operators `<`, `>` and `=`.
Add two new unitary operators `+` and `-` for Vector.

### 8th May, 2018 Update :
1. Fix the cacography that can lead to compile error from the beginning.
2. Simplify the codes of functions that need to backup the elements with freeing the old memory allocated by adding a new function named `backup()` and calling it.
3. Fix the fatal error that the constructor accepting range-iterator hasn't allocated the memory to construct the elements.
4. Fix the bug that the function named `back()` returns a nonexistent element.
5. Fix the bug that there is no element in the Vector but calling the function named `at()` or using the operator `[]` would get e illegal element.
6. Since the emplace functions can throw the exceptions, I removed the `noexcept` from them.
7. The work of `popFront()`, `pushFront()` and right-value inserting now is consigned to `insert()` or `erase()`
8. Fix the bug that find a non-first element will lead to a non-break loop.
9. Now the operator `[]` can be used by a Vector that is right-value.
10. Add the range detecting for `get()`.
11. The work `shrinkToFit()` should do now is consigned to `resize()`
12. Add the specific work for `resize()` to fit when `shrinkToFit()` calls him.
13. Delete the function `template <typename ...Args> bool Vector<T>::find(const Args &...args) const` temporarily, because there is a bug I still cannot fix till now, but it will come back soon!


    **Now all functions has passed the test by build-in type!**

### 8th May, 2018 Update :
Now the function that is able to find a series of numbers comes back!

### 2nd July, 2018 Refactor:
1. Add Allocator.
2. Add Iterator.
3. Rename some functions.
4. Add new `insert` overload functions, `emplace` overload functions, `erase` overload functions
5. Change the old code which is out for new `Vector`.
6. Clear the types. All function's returning types and parameter types use the type from `Vector`


# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
