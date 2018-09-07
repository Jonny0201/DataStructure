# ::DataStructure::Stack

In the STL, `std::stack` is a container adapter. Stack is a FILO (first in last out) data structure. In the `DataStructure`, I reversed the attribution - container adapter. However, for the stack, I think I should keep the stack's own attribution. There are two specilal stacks in `DataStructure`, all are template specializations.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't declared `DataStructure` by `using namespace DataStructure`.

## Definition

    template <typename T, typename Container, bool Bilateral>
    class Stack;

Default stack is a container adapter.

#### Specialization
    template <typename T>
    class Stack<T, T *, false>;

This specialization is a sequence stack.

#### Specialization
    template <typename T>
    class Stack<T, T *, true>;

This specialization is a bilateral-sequence stack.

## Member types

>- `valueType` <-> `T`
>- `reference` <-> `T &`
>- `pointer` <-> `T *`
>- `constPointer` <-> `const T *`
>- `constPointerConstant` <-> `const T *const`
>- `rightValueReference` <-> `T &&`
>- `iterator` <-> `DataStructure::Stack::Iterator`
>- `constIterator` <-> `const DataStructure::Stack::Iterator`
>- `allocator` <-> `Alloc`
>- `differenceType` <-> `long`
>- `sizeType` <-> `unsigned long`

## Constructor and Destructor

```cpp
1. Stack();        //Default constructor.
2. Satck(const Stack &);        //Copy constructor.
3. Stack(Stack &&) noexcept;        //Move constructor.
4. ~Stack();
5. explicit Stack(sizeType);        //Partially specialized constructor.
```

## Operator
```cpp
1. Stack &operator=(const Stack &);        //Copy assignment operator.
2. Stack &operator=(Stack &&) noexcept;        //Move assignment operator.
3. bool operator==(const Stack &) const;
4. bool operator not_eq(const Stack &) const;        //not_eq <-> !=
5. explicit operator bool() const;
```

## Function

```cpp
1. bool empty() const;
2. sizeType size() const;
3. constReference top() const;
4. void push(constReference);
5. void push(rightValueReference);
6. void pop();        //Returning-type depends on macro.
7. void clear();
8. void swap(Stack &);
9. friend void swap(Stack &, Stack &);
```

As you can see, what every function does is like what the name every function holds.

## Iterator

There isn't iterator in the stack.

## Advanced Function

These functions is what I don't want anyone who uses casually. If you want to call these functions, you should declare a macro variable named `OTHER_FUNCTION` :

`#define OTHER_FUNCTION`

```cpp
1. void resize(sizeType);
2. void shrinkToFit();
3. sizeType reserve() const;
4. sizeType capacity() const;
```

## Debug Function

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should declare a macro variable named `DEBUG_DATA_STRUCTURE_FOR_STACK` :

`#define DEBUG_DATA_STRUCTURE_FOR_FORWARD_STACK`

```cpp
1. container &getContainer();
2. pointer &getLast();        //Partially specialized function for Stack<T, T *, false>.
3. sizeType &getContainerSize();        //Partially specialized function.
4. pointer &getLeftLast();        //Partially specialized function for Stack<T, T *, true>.
5. pointer &getRightLast();        //Partially specialized function for Stack<T, T *, true>.
```

  > Tip : `container` is a type from `Stack`, it is `private`.

## Problem Exists

Though the `Stack` is finished and it can be used now, it still exists many problems :

- You cannot use you own `Allocator` in the Stack.

If you find any error in the `Stack`, please tell me!

## Updates

# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
