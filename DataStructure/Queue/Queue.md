# ::DataStructure::Queue

In the STL, `std::queue` is a container adapter. Queue is a FIFO (first in first out) data structure. In the `DataStructure`, I reversed the attribution - container adapter. However, for the queue, I think I should keep the queue's own attribution. There is a specilal queue in `DataStructure` - circular queue, which is the template specialization. The circular queue has two version, the one will sacrifice one position from the queue to keep circular, the other will will make a tag to keep circular.

It is namespaced in namespace `DataStructure`, so if you want to use this, you should add `DataStructure::` at first if you haven't declared `DataStructure` by `using namespace DataStructure`.

## Definition

    template <typename T, typename Container, bool Sacrifice, bool Tag>
    class Stack;

Default queue is a container adapter. In the version of queue, template parameter `bool Sacrifice` and `bool Tag` is useless.

#### Specialization
    template <typename T>
    class Queue<T, T *, false, false>;

This specialization is a sequence queue.

#### Specialization
    template <typename T>
    class Queue<T, T *, true, false>;

This specialization is a circular queue who sacrifices one position from the queue to keep circular.

#### Specialization
    template <typename T>
    class Queue<T, T *, false, true>;

The specialization is a circular queue who make a tag to keep circular.

## Member types

>- `valueType` <-> `T`
>- `reference` <-> `T &`
>- `pointer` <-> `T *`
>- `constPointer` <-> `const T *`
>- `constPointerConstant` <-> `const T *const`
>- `rightValueReference` <-> `T &&`
>- `differenceType` <-> `long`
>- `sizeType` <-> `unsigned long`

## Constructor and Destructor

```cpp
1. Queue();        //Default constructor.
2. Queue(const Queue &);        //Copy constructor.
3. Queue(Queue &&) noexcept;        //Move constructor.
4. ~Queue();
5. explicit Queue(sizeType);        //Partially specialized constructor.
```

## Operator
```cpp
1. Queue &operator=(const Queue &);        //Copy assignment operator.
2. Queue &operator=(Queue &&) noexcept;        //Move assignment operator.
3. bool operator==(const Queue &) const;
4. bool operator not_eq(const Queue &) const;        //not_eq <-> !=
5. explicit operator bool() const;
6. bool operator<=(const Queue &) const;
7. bool operator<(const Queue &) const;
8. bool operator>(const Queue &) const;
9. bool operator>=(const Queue &) const;
```

  > Tip : The operator <=, <, >, >= is deleted in specialization.

## Function

```cpp
1. bool empty() const;
2. bool full() const;        //Partially specialized function for Queue<T, T *, true, false> and Queue<T, T *, false, true>.
3. sizeType size() const;
4. constReference front() const;
5. constReference back() const;
6. void push(constReference);
7. void push(rightValueReference);
8. void pop();        //Returning-type depends on macro.
9. void clear();
10. void swap(Queue &);
11. friend void swap(Queue &, Queue &);
```

As you can see, what every function does is like what the name every function holds.

## Iterator

There isn't iterator in the queue.

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

These function should NOT be used in production environment. Besides, these functions will destroy the encapsulation of class.If you want to call these functions, you should declare a macro variable named `DEBUG_DATA_STRUCTURE_FOR_QUEUE` :

`#define DEBUG_DATA_STRUCTURE_FOR_FORWARD_QUEUE`

```cpp
1. container &getContainer();
2. pointer &getLast();        //Partially specialized function.
3. sizeType &getContainerSize();        //Partially specialized function.
4. pointer &getFirst();        //Partially specialized function for Queue<T, T *, true, false>.
5. bool &getTag();        //Partially specialized function for Stack<T, T *, false, true>.
```

  > Tip : `container` is a type from `Queue`, it is `private`.

## Problem Exists

Though the `Queue` is finished and it can be used now, it still exists many problems :

- You cannot use you own `Allocator` in the Stack.

If you find any error in the `Queue`, please tell me!

## Updates

# LICENSE

> Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
