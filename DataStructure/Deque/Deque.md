# ::DataStructure::Deque

Compared to `Vector`, `Deque` (double-ended queue) is a fakely sequence structure. To keep the fake sequence, `Deque` will make every effort to manage the memory, which will spend many time. If you are not really needing a double-ended structure, please use `Vector` instead of using `Deque`. However, like the `Vector`, `Deque` allows fast insertion and fast deletion at both its beginning and its end.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't declared `DataStructure` by `using namespace DataStructure`.

Till 9th September, 2018, it still haven't been tested seriously (I only tested `int` seriously, but there are still many bugs fucking me...). So if you want to include this in yourself's programme, you should test it carefully at first.

## Definition

`template <typename T, unsigned long BufferSize = 64, typename Alloc = Allocator<T>>
 class Deque final;`

The second template parameter `BufferSize` is used in how much memory the Allocator needs manage.

## Member types

>- `valueType` <-> `T`
>- `reference` <-> `T &`
>- `constReference` <-> `const T &`
>- `pointer` <-> `T *`
>- `constPointer` <-> `const T *`
>- `constPointerConstant` <-> `const T *const`
>- `rightValueReference` <-> `T &&`
>- `iterator` <-> `DataStructure::Deque::Iterator`
>- `constIterator` <-> `const DataStructure::Deque::Iterator`
>- `allocator` <-> `Alloc`
>- `differenceType` <-> `long`
>- `sizeType` <-> `unsigned long`

## Constructor and Destructor

```cpp
1. Deque();        //Default constructor.
2. Deque(sizeType, constReference);
3. explicit Deque(sizeType);
4. Deque(iterator, iterator);
5. Deque(pointer , pointer);
6. Deque(std::initializer_list<valueType>);
7. Deque(const Deque &);        //Copy constructor.
8. Deque(Deque &&) noexcept;        //Move constructor.
9. ~Deque();
```

  1) Default constructor. Constructs a new empty `Deque`.
  2) Constructs the `Deque` with count copies of elements with value.
  3) Constructs the `Deque` with count copies of elements with default value `valueType()`.
  4) Constructs the `Deque` with a range of elements that is provided by a range iterator.
  5) Constructs the `Deque` with a range of elements that is provided by a range pointer.
  6) Constructs the `Deque` with the `std::initializer_list`.
  7) Copy constructor. Constructs the `Deque` with other `Deque` by copying the elements from other `Deque`.
  8) Move constructor. Constructs the `Deque` with other `Deque` by moving the elements from other `Deque`.

## Operator
```cpp
1. Deque &operator=(const Deque &);        //Copy assignment operator.
2. Deque &operator=(Deque &&) noexcept;        //Move assignment operator.
3. bool operator<(const Deque &) const;
4. bool operator<=(const Deque &) const;
5. bool operator>(const Deque &) const;
6. bool operator>=(const Deque &) const;
7. bool operator==(const Deque &) const;
8. bool operator not_eq(const Deque &) const;        //not_eq <-> !=
9. explicit operator bool() const;
```

  3\) -- 6\) The comparison operator is different from the operator of C++ Standard Template Library's `std::deque`. I will introduce in operator `<` for example. For the other operators, you can analogize from operator `<`. Now assumed that there is a `Deque` named A and an another `Deque` named B that is going to compare with `Deque` A. First, the function will compare the size of two `Deque`s, that the `Deque` A has a bigger size will return false as result. If two `Deque`s have the same sizes then will compare every element, till find a position that two `Deque`s have a different element from each other, then compare which element. If `Deque` A's element is smaller, then return true.<br />

    > Tip : The valueType of Deque should support the operator then the overloading operators will work, or using will make a compile error.

  7\) -- 8\) Only two `Deque`s have the same sizes and every position's element is identical then the operator `==` will return true, else the operator `!=` will return true.

  9\) It is common to use the operator `bool()` in the condition statements to judge whether the `Deque` is empty or not.

## Function

```cpp
1. void assign(sizeType, constReference);
2. void assign(iterator, iterator);
3. void assign(pointer, pointer);
4. void assign(std::initializer_list<valueType>);
5. valueType front() const;
6. valueType back() cnost;
7. bool empty() const;
8. sizeType size() const;
9. iterator begin() const;
10. iterator end() const;
11. constIterator constBegin() const;
12. constIterator constEnd() const;
13. valueType at(differenceType) const;
14. void clear();
15. void pushBack(constReference);
16. void pushBack(rightValueReference);
17. void popBack();        //Returning-type depends on macro
18. void pushFront(constReference);
19. void pushFront(rightValueReference);
20. void popFront();        //Returning-type depends on macro
21. iterator insert(constIterator, constReference, sizeType);
22. iterator insert(constIterator, rightValueReference, sizeType);
23. iterator insert(constReference, differenceType, sizeType);
24. iterator insert(rightValueReference, differenceType, sizeType);
25. iterator insert(constIterator, std::initializer_list<valueType>);
26. template <typename ForwardIterator>
    iterator insert(constIterator, ForwardIterator, ForwardIterator);
27. template <typename ...Args>
    iterator emplace(constIterator, Args &&...);
28. template <typename ...Args>
    iterator emplaceFront(Args &&...);
29. template <typename ...Args>
    iterator emplaceBack(Args &&...);
30. iterator erase(constIterator, sizeType);
31. iterator erase(differenceType, sizeType);
32. iterator erase(constIterator, constIterator);
33. void swap(Deque &);
34. void swap(Deque &, Deque &);
```

As you can see, what every function does is like what the name every function holds.

> Tip : Deque can be put in **Range-For** (C++11).

## Iterator

The iterator from `Deque` is a bidirectional iterator.

Operator supports :
```cpp
1. T &operator*();
2. const T &operator*() const;
3. T *operator->();
4. const T *operator->() const;
5. bool operator==(const Iterator &) const;
6. bool operator not_eq(const Iterator &) const;
7. Iterator &operator++();
8. Iterator operator++(int);
9. Iterator &operator--();
10. Iterator operator--(int);
11. reference operator[](differenceType);
12. differenceType operator-(const Iterator &) const;
13. Iterator &operator+=(differenceType);
14. Iterator &operator-=(differenceType);
15. Iterator operator+(differenceType);
16. Iterator operator-(differenceType);
17. bool operator<(const Iterator &) const;
18. bool operator<=(const Iterator &) const;
19. bool operator>(const Iterator &) const;
20. bool operator>=(const Iterator &) const;
21. explicit operator bool() const;
```

## Advanced Function

These functions is what I don't want anyone who uses casually. If you want to call these functions, you should declare a macro variable named `OTHER_FUNCTION` :

`#define OTHER_FUNCTION`

```cpp
1. Deque get(differenceType, sizeType) const;
2. void resize(sizeType);
3. void shrinkToFit();
4. sizeType capacity() const;
```

  1\) Get the element list and put the list into a new `Deque` then return it.
  2\) If the size provided is greater than the `Allocator`'s `allocateSize`, all `Allocator`s' `allocateSize` will be changed to the size provided.
  3\) Make every `Allocator` shrink to fit. (The function's work has delegated to `Allocator`)
  4\) Get the capacity of `Deque`.

## Debug Function

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should declare a macro variable named `DEBUG_DATA_STRUCTURE_FOR_DEQUE` :

`#define DEBUG_DATA_STRUCTURE_FOR_FORWARD_DEQUE`

```cpp
1. map *&getBuffer();
2. sizeType getBufferSize() const;
3. iterator &getFirst();
4. iterator &getLast();
```

  > Tip : `map` is a type from `Deque`, it is `private`.

## Problem Exists

Though the `Deque` is finished and it can be used now, it still exists many problems :

- Constructor `Deque(iterator, iterator);` should accept any iterator including pointers not only the iterators from `Deque`.
- There isn't a reserve iterator in `Deque`.
- Any unknown error.

If you find any error in the `Deque`, please tell me!

## Updates

# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://github.com/Jonny0201)
