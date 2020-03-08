# ::DataStructure::List

Compared to `ForwardList`, the iterator of `List` is a bidirectional iterator. All the elements from `List` is stored non-continuously like `ForwardList` which means you can insert and erase elements easily but visiting elements will be time-consuming. If the elements that need to be saved with a lot of operatoringts of inserting and erasing, with a little of visiting or changes and you have a demand that iterator is bidirectional, then you should consider using `List` to store them.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't declared `DataStructure` by `using namespace DataStructure`.

Till 19th August, 2018, it still haven't been tested seriously (I only tested `int`). So if you want to include this in yourself's programme, you should test it carefully at first.

For the `Allocator`, `List` only uses its `operator new` and `operator delete`.

## Definition

`template <typename T, typename Alloc = DataStructure::Allocator<T>>
 class List;`

## Member types

>- `valueType` <-> `T`
>- `constType` <-> `const T`
>- `reference` <-> `T &`
>- `constReference` <-> `const T &`
>- `pointer` <-> `T *`
>- `constPointer` <-> `const T *`
>- `constPointerConstant` <-> `const T *const`
>- `rightValueReference` <-> `T &&`
>- `iterator` <-> `DataStructure::List::Iterator`
>- `constIterator` <-> `const DataStructure::List::Iterator`
>- `iteratorReference` <-> `DataStructure::List::Iterator &`
>- `constIteratorReference` <-> `const DataStructure::List::Iterator &`
>- `allocator` <-> `Alloc`
>- `differenceType` <-> `long`
>- `sizeType` <-> `unsigned long`

## Constructor and Destructor

```cpp
1. List();        //Default constructor.
2. List(sizeType, constReference);
3. explicit List(sizeType);
4. List(iterator, iterator);
5. List(pointer , pointer);
6. List(std::initializer_list<valueType>);
7. explicit List(const List &);
8. List(const List &);        //Copy constructor.
9. List(List &&) noexcept;        //Move constructor.
10. ~List();
```

  1) Default constructor. Constructs a new empty `List`.
  2) Constructs the `List` with count copies of elements with value.
  3) Constructs the `List` with count copies of elements with default value `valueType()`.
  4) Constructs the `List` with a range of elements that is provided by a range iterator.
  5) Constructs the `List` with a range of elements that is provided by a range pointer.
  6) Constructs the `List` with the `std::initializer_list`.
  7) Constructs the `List` with other allocator.
  8) Copy constructor. Constructs the `List` with other `List` by copying the elements from other `List`.
  9) Move constructor. Constructs the `List` with other `List` by moving the elements from other `List`.

## Operator
```cpp
1. List &operator=(const List &);        //Copy assignment operator.
2. List &operator=(List &&) noexcept;        //Move assignment operator.
3. bool operator<(const List &) const;
4. bool operator<=(const List &) const;
5. bool operator>(const List &) const;
6. bool operator>=(const List &) const;
7. bool operator==(const List &) const;
8. bool operator not_eq(const List &) const;        //not_eq <-> !=
9. explicit operator bool() const;
```

  3\) -- 6\) The comparison operator is different from the operator of C++ Standard Template Library's `std::list`. I will introduce in operator `<` for example. For the other operators, you can analogize from operator `<`. Now assumed that there is a `List` named A and an another `List` named B that is going to compare with `List` A. First, the function will compare the size of two `List`s, that the `List` A has a bigger size will return false as result. If two `List`s have the same sizes then will compare every element, till find a position that two `List`s have a different element from each other, then compare which element. If `List` A's element is smaller, then return true.<br />

    > Tip : The type of List should support the operator then the overloading operators will work, or will make a compile error.

  7\) -- 8\) Only two `List`s have the same sizes and every position's element is identical then the operator `==` will return true, else the operator `!=` will return true.

  9\) It is common to use the operator `bool()` in the condition statements to judge whether the `List` is empty or not.

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
12. void clear();
13. void pushBack(constReference);
14. void pushBack(rightValueReference);
15. void popBack();        //Returning-type depends on macro
16. void pushFront(constReference);
17. void pushFront(rightValueReference);
18. void pushFront();
19. iterator insert(constIterator, constReference, sizeType);
20. iterator insert(constIterator, rightValueReference, sizeType);
21. iterator insert(constReference, differenceType, sizeType);
22. iterator insert(rightValueReference, differenceType, sizeType);
23. iterator insert(constIterator, std::initializer_list<valueType>);
24. template <typename ForwardIterator>
    iterator insert(constIterator, ForwardIterator, ForwardIterator);
25. template <typename ...Args>
    iterator emplace(constIterator, Args &&...);
26. template <typename ...Args>
    iterator emplaceFront(Args &&...);
27. template <typename ...Args>
    iterator emplaceBack(Args &&...);
28. iterator erase(constIterator, sizeType);
29. iterator erase(differenceType, sizeType);
30. iterator erase(constIterator, constIterator);
```

As you can see, what every function does is like what the name every function holds.

> Tip : List can be put in **Range-For** (C++11).

## Iterator

The iterator from `List` is a bidirectional iterator.

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
```

## Advanced Function

These functions is what I don't want anyone who uses casually. If you want to call these functions, you should declare a macro variable named `OTHER_FUNCTION` :

`#define OTHER_FUNCTION`

```cpp
1. List get(differenceType, sizeType) const;
2. iterator beforeBegin() const;
3. constIterator beforeBegin() const;
```

  1\) Get the element list and put the list into a new `List` then return it.
  2\) -- 3\) Get the before-begin iterator.

Due to the particularity of `List`'s iterator, so I'm going to add these functions :
```cpp
1. iterator merge(const ForwardList &);
2. template <typename Compare>
   iterator merge(const ForwardList &, Compare comp);
3. iterator splice(constIterator, const ForwardList &);
4. iterator splice(constIterator, const ForwardList, constIterator);
5. iterator splice(constIterator, const ForwardList, constIterator, constIterator);
6. iterator remove(constReference);
7. template <typename UnaryPredicate>
   iterator removeIf(UnaryPredicate);
8. void reverse();
9. void unique() const;
10. void sort();
```
  1\) Merge two `List`s.
  2\) -- 5\) Splice other `List` to `*this`.
  6\) -- 7\) Remove the eligible first value from `List`.
  8\) Reserve the elements from `List`.
  9\) Remove the duplicate elements from `List`.
  10\) Sort the elements from `List`.

## Debug Function

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should declare a macro variable named `DEBUG_DATA_STRUCTURE_FOR_LIST` :

`#define DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST`

```cpp
1. node &getFirst();
2. node &getEnd();
```

  > Tip : `node` is a type from `List`, it is `private`.

## Problem Exists

Though the `List` is finished and it can be used now, it still exists many problems :

- Constructor `List(iterator, iterator);` should accept any iterator including pointers not only the iterators from `List`.
- There isn't a reserve iterator in `List`.
- Any unknown error.

If you find any error in the `List`, please tell me!

## Updates

# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://github.com/Jonny0201)
