# ::DataStructure::ForwardList

`FowardList` is a list whose iterator can only go forward. All the lements from `ForwardList` is stored non-continuously which means you can insert and erase elements easily but visiting elements will be time-consuming. If the elements that need to be saved with a lot of operatoringts of inserting and erasing and with a little of visiting or changes, then you should consider using `ForwardList` to store them.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't declare `DataStructure` by `using namespace DataStructure`.

Till 15th July, 2018, it still haven't been tested seriously (I only tested `int`). So if you want to include this in yourself programme, you should test it carefully at first.

For the Allocator, ForwardList only uses its `operator new` and `operator delete`.

## Definition

`template <typename T, typename Alloc = DataStructure::Allocator<T>>
 class ForwardList;`

If the `List` is going to inherit from `ForwardList`, then the ForwardList should **NOT** be `final class`

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
1. ForwardList();        //Default constructor.
2. ForwardList(sizeType, constReference);
3. explicit ForwardList(sizeType);
4. ForwardList(iterator, iterator);
5. ForwardList(pointer , pointer);
6. ForwardList(std::initializer_list<valueType>);
7. explicit ForwardList(const ForwardList &);
8. ForwardList(const ForwardList &);        //Copy constructor.
9. ForwardList(ForwardList &&) noexcept;        //Move constructor.
10. ~ForwardList();
```

  1) Default constructor. Constructs a new empty `ForwardList`.
  2) Constructs the `ForwardList` with count copies of elements with value.
  3) Constructs the `ForwardList` with count copies of elements with default value `valueType()`.
  4) Constructs the `ForwardList` with a range of elements that is provided by a range iterator.
  5) Constructs the `ForwardList` with a range of elements that is provided by a range pointer.
  6) Constructs the `ForwardList` with the `std::initializer_list`.
  7) Constructs the `ForwardList` with other allocator.
  8) Copy constructor. Constructs the `ForwardList` with other `ForwardList` by copying the elements from other `ForwardList`.
  9) Move constructor. Constructs the `ForwardList` with other `ForwardList` by moving the elements from other `ForwardList`.

## Operator
```cpp
1. ForwardList &operator=(const ForwardList &);        //Copy assignment operator.
2. ForwardList &operator=(ForwardList &&) noexcept;        //Move assignment operator.
3. bool operator<(const ForwardList &) const;
4. bool operator<=(const ForwardList &) const;
5. bool operator>(const ForwardList &) const;
6. bool operator>=(const ForwardList &) const;
7. bool operator==(const ForwardList &) const;
8. bool operator not_eq(const ForwardList &) const;        //not_eq <-> !=
9. explicit operator bool() const;
```

  3\) -- 6\) The comparison operator is different from the operator of C++ Standard Template Library's `std::forward_list`. I will introduce in operator `<` for example. For the other operators, you can analogize from operator `<`. Now assumed that there is a `ForwardList` named A and an another `ForwardList` named B that is going to compare with `ForwardList` A. First, the function will compare the size of two `ForwardList`s, that the `ForwardList` A has a bigger size will return false as result. If two `ForwardList`s have the same sizes then will compare every element, till find a position that two `ForwardList`s have a different element from each other, then compare which element. If `ForwardList` A's element is smaller, then return true.<br />

    > Tip : The type of Vector should support the operator then the overloading operators will work, or will make a compile error.

  7\) -- 8\) Only two `ForwardList`s have the same sizes and every position's element is identical then the operator `==` will return true, else the operator `!=` will return true.

  9\) It is common to use the operator `bool()` in the condition statements to judge whether the `ForwardList` is empty or not.

## Function

```cpp
1. valueType pop();        //Returning value depends on macro.
2. void pop();
3. void push(const ValueType &);
4. valueType front() const;
5. iterator insertAfter(constReference, differenceType, sizeType = 1);
6. void insertAfter(constReference, constIterator, sizeType = 1);
7. template <typename ForwardIterator>
   void insertAfter(constIterator, ForwardIterator, ForwardIterator);
8. void insertAfter(constIterator, std::initializer_list<valueType>);
9. void eraseAfter(constIterator);
10. iterator eraseAfter(differenceType, sizeType = 1);
11. void eraseAfter(constIterator, constIterator);
12. template <typename ...Args>
    void emplaceFront(Args &&...);
13. template <typename ...Args>
    iterator emplaceAfter(differenceType, Args &&...);
14. void clear();
15. bool empty() const;
16. sizeType size() const;
17. iterator begin() const;
18. iterator end() const;
19. constIterator constBegin() const;
20. constIterator constEnd() const;
```

As you can see, what every function does is like what the name every function holds.

But the point you should focus on is that `insertAfter`、`eraseAfter` and `emplaceAfter` functions operate the element where the position is after incoming argument's position.

> Tip : ForwardList can be put in **Range-For** (C++11).

## Iterator for `ForwardList`

The iterator from `ForwardList` is a special iterator. It can only be dereference and increment value.

Operator supports :
```cpp
1. T &operator*();
2. bool operator==(const Iterator &) const;
3. bool operator not_eq(const Iterator &) const;
4. Iterator &operator++();
5. Iterator operator++(int);
```

## Advanced Function

These functions is what I don't want anyone who uses casually. If you want to call these functions, you should declare a macro variable named `OTHER_FUNCTION` :

`#define OTHER_FUNCTION`

```cpp
1. ForwardList get(differenceType, sizeType) const;
2. iterator beforeBegin() const;
3. constIterator beforeBegin() const;
```

  1\) Get the element list and put the list into a new `ForwardList` then return it.
  2\) -- 3\) Get the before-begin iterator.

Due to the particularity of ForwardList's iterator, so I'm going to add these functions :
```cpp
1. iterator merge(const ForwardList &);
2. template <typename Compare>
   iterator merge(const ForwardList &, Compare comp);
3. iterator spliceAfter(constIterator, const ForwardList &);
4. iterator spliceAfter(constIterator, const ForwardList, constIterator);
5. iterator spliceAfter(constIterator, const ForwardList, constIterator, constIterator);
6. iterator remove(constReference);
7. template <typename UnaryPredicate>
   iterator removeIf(UnaryPredicate);
8. void reverse();
9. void unique() const;
10. void sort();
```
  1\) Merge two `ForwardList`s.
  2\) -- 5\) Splice other `ForwardList` to `*this`.
  6\) -- 7\) Remove the eligible first value from `ForwardList`.
  8\) Reserve the elements from `ForwardList`.
  9\) Remove the duplicate elements from `ForwardList`.
  10\) Sort the elements from `ForwardList`.

## Debug Function

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should declare a macro variable named `DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST` :

`#define DEBUG_DATA_STRUCTURE_FOR_FORWARD_LIST`

```cpp
1. node &getFirst();
2. node &getEnd();
```

  > Tip : `node` is a type from `ForwardList`, it is `private`.

## Problem Exists

Though the `ForwardList` is finished and it can be used now, it still exists many problems :

- Constructor `ForwardList(iterator, iterator);` should accept any iterator including pointers not only the iterators from `ForwardList`.
- There isn't a reserve iterator in `ForwardList`.
- Any unknown error.

If you find any error in the `ForwardList`, please tell me!

## Updates

# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
