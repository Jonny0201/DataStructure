# ::DataStructure::Vector

Just like C++ Standard Template Library, Vector is a multifunction array. All the elements from Vector is stored contiguously which means you can visit element easily but inserting or erasing elements will take more time. If the elements that need to be saved with only a little operating of erasing or inserting and with a lot of operating of visits or changes, then you should consider using Vector to store them.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't written `using namespace DataStructure`.

It defined in header <Vector.hpp> and <Vector.cpp>. Because of the attribution of template class, you should include two of the headers by
`#include <Vector.hpp>
 #include <Vector.cpp>`
or you can include a all-module header by
`#include <DataStructure.hpp>`

Till 1st May, 2018, it still haven't been tested seriously. So if you want to include this in yourself programme, you should test it carefully at first.

## Definition

`template <typename T>
 class Vector;`


## Member types

>- `type` <-> `T`
>- `constType` <-> `const T`
>- `reference` <-> `T &`
>- `constReference` <-> `const T &`
>- `pointer` <-> `T *`
>- `constPointer` <-> `const T *`
>- `constPointerConstant` <-> `const T *const`
>- `rValueReference` <-> `T &&`
>- `iterator` <-> `pointer`
>- `constIterator` <-> `constPointer`

## Constructor and Destructor

```
1. Vector();       //Default constructor.
2. explicit Vector(size_t, const T &);
3. explicit Vector(size_t);
4. Vector(const T *, const T *);
5. Vector(std::initializer_list<T>);
6. Vector(cosnt Vector &);        //Copy constructor.
7. Vector(Vector &&);        //Move constructor.
8. ~Vector();
```
Because of conflict of functions, those constructor has been deleted :
>- `template <typename ...ARGS>
     explicit Vector(ARGS &&...) noexcept;`
>- `explicit Vector(T &&, size_t = 1) noexcept;`
>- `explicit Vector(T &&) noexcept;`

  1) Default constructor will make a new Vector that is empty
  2) Construct the Vector arguments from `const T &`, the number of element is specified by `size_t`
  3) Construct the Vector, the number of element that is default initialized is specified by `size_t`
  4) Construct the Vector with a range of elements that provided by a range pointers.
  5) Construct the Vector with the `std::initializer_list`

## Operator
```
1. Vector &operator=(const Vector &);        //Copy assignment operator.
2. Vector &operator=(Vector &&) noexcept;        //Move assignment operator.
3. T &operator[](unsigned n) const &;
4. bool operator<(const Vector &) const;
5. bool operator<=(const Vector &) const;
6. bool operator>(const Vector &) const;
7. bool operator>=(const Vector &) const;
8. bool operator==(const Vector &) const;
9. bool operator!=(const Vector &) const;
10. explicit operator bool() const;
11. Vector &operator+();
12. Vector &operator-();
```

  3\) The operator is like arrays' indexing operator, it return a reference of indexing elements.<br />

    > Tip : For the operator `[]`, you shouldn't use it in a right-value Vector.

  4\) -- 6\) The comparison operator is different from the operator of C++ Standard Template Library's vector. I will introduce in operator `<` for example. For the other operators, you can analogize from operator `<`. Now assumed that there is a Vector named A and an another Vector named B that is going to compare with Vector A. First, the function will compare the size of two Vector, that the Vector A has a bigger size will return false as result. If two Vectors has the same size then will compare every element, till find a position that two Vector have a different element from each other, then compare which element. If Vector A's element is smaller, then return true.<br />

    > Tip : The type of Vector should support the operator then the overloading operator will work, or will make a compile error.

  8\) -- 9\) Only two Vectors has the same size and every position's element is identical then the operator `==` will return true, else the operator `!=` will return true.<br />

  10\) It is common to use the operator `bool()` in the condition statements to judge whether the Vector is empty or not.

## Function
```
1. T popBack();
2. void popBack();
3. T popFront();
4. void popFront();
5. void pushBack(const T &);
6. void pushFront(const T &);
7. T at(unsigned n) const;
8. bool isEmpty() const;
9. void clear();
10. T const *insert(const T &, unsigned, size_t = 1);
11. T const *insert(T &&, unsigned);
12. const T *const getConstantBegin() const;
13. const T *const getConstantEnd() const;
14. T const *getBegin() const;
15. T const *getEnd() const;
16. template <typename ...ARGS>
     T const *emplace(unsigned, ARGS &...) noexcept;
17. template <typename ...ARGS>
     T const *emplaceBack(ARGS &&...) noexcept;
18. template <typename ...ARGS>
     T const *emplaceFront(ARGS &&...) noexcept;
19. size_t size() const;
20. const T front() const;
21. const T back() const;
```

As you can see, what every function should do is like what the name every function holds, I will specially introduce insert()、emplace() and erase() function :<br />

  10\) For the first parameter, you should deliver a `T` type argument that can be a right-value argument or a left-value argument, then set the second parameter as the inserting position. If you want to insert not only one, you can set the last parameter, let the function help you insert a number of elements that you want.<br />

  11\) Different from the previous insert(), this function asks you to diliver only right-value argument.<br />

  16\) -- 18\) You can diliver many arguments to fit the `T` type's construtor. The emplace() asks you to tell the function what the emplace position should be and the other needn't. The emplace-named function will construct the `T` type in the function then insert it. It is what the difference comparing with the function insert().<br />


## Advanced Function

These functions is what the writer don't want anyone who use casually. If you want to call these functions, you should hold a macro variable named `OTHER_FUNCTION` :

`#define OTHER_FUNCTION`

```
1. ptrdiff_t find(const T &) const;
2. template <typename ...ARGS>
 bool find(const ARGS &...) const;
3. Vector<T> get(unsigned, size_t) const;
4. void resize(size_t);
5. ptrdiff_t reserve() const;
6. ptrdiff_t capacity() const;
7. void shrinkToFit();
```
  1\) Find the provided element in the Vector.<br />
  2\) Find all elements provided in the Vector, only that all elements exist in Vector will return true.<br />
  3\) Get the number of element whose position is provided by code-users in the Vector.<br />
  4\) Comparing the provided allocateSize and existing allocateSize from the class. Reallocate the memory of the Vector when the provided allocateSize is greater than existing allocateSize from the class.<br />
  5\) Get the information that how many vacancies is in the Vector.<br />
  6\) Get the information that how many position altogether is in the Vector.<br />
  7\) Free the memory that occupied by vacancies.

## Debug Function

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should hold a macro variable named `DEBUG_DATA_STRUCTURE_FOR_VECTOR` :

`#define DEBUG_DATA_STRUCTURE_FOR_VECTOR`

```
std::allocator<T> *getInwardAllocator() const;
T *getInwardFirst() const;
T *getInwardCursor() const;
T *getInwardEnd() const;
```

## Problem Exists

Though the Vector is finished and it can be used now, it still exists many problems :

- There are many duplicated code in the function insert()、emplace() and erase().
- The iterator of the Vector is pointers, which is unsafe.
- Code-users cannot use the memory allocator that designed by themselves in this version of Vector.
- Because of the rough testing, there will be many bugs I still haven't discovered.

## Updates

```
3rd May, 2018 Update :
The bug that when two Vectors is equal but the operator `<=` would return false now is fixed.
Simplify the code of the operators `<=` and `>=` by using the operators `<`, `>` and `=`.
Add two new unitary operators `+` and `-` for Vector.
```


# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
