# Data Structure

Project Name : Data Structure

## Introduction

**[warning] The programming has been deprecated, please move to https://github.com/Jonny0201/data_structure.**

Data structure is the base of the computer programming.

It helps programmers store and handle data.

Data Structure is imitating by C++ Standard Template Library, however, what you should focus on is that there are an abundance of discrepancies with C++ STL. All the discrepancies that can confuse you I will introduce one by one.

Data Structrue can be used in any programs.

## Module

This Data Structure written by Jonny in C++ will include :

```
1. List
2. Stack
3. Queue
4. Dictionary
5. Tree
6. Graph
7. Hash
8. Heap
```

## Base

### <center>Allocator Standard</center>

#### Introduction

In the `DataStructure`, Allocator is used by all containers. It takes responsibility for managing memory. The `DataStructure::Allocator` class template is the default Allocator used by all containers if no user-specified allocator is provided. In the special situation, the default allocator may become a burden if the programme need manage the memory by itself. Sometimes the programmers need customize the Allocator, if the programmers want that the Allocator customized by self can be used in `DataStructure`'s containers, the programmers should obey this starndard.

#### Standard

1. `Allocator` should take responsibility for a linear sequence allocated by itself. The work of Allocating the linear sequence should be left to member function `allocate` instead of constructor.
2. The member variables (attributes) of `Allocator` include the head pointer of the linear sequence in the `Allocator`, the cursor pointer of the linear sequence and the size of linear sequence (this member variable's type should be `unsigned long`).
3. The result of the operation that `sizeof(Allocator<T>)` in the x86_64 architecture machine should less or less equal than 48ul.
4. The type member in `Allocator` should include `sizeType`, `differenceType`, `valueType`, `reference`, `constReference`, `rightValueReference`, `pointer`, `constPointer`
5. There should be two overloaded, static and public functions `operator new` and `operator delete` at least in `Allocator`.
6. There should be two static and public functions named `construct` and `destroy` in `Allocator`. `construct` is used to construct any object, `destroy` is used to destruct any object or a range. These two functions only accept one or two arguments whose type is `void *`.
7. `Allocator` can be copy-constructed, copy-assigned, move-constructed and move-assigned. The operations who are related to moving should be signed `noexcept`.
8. `Allocator` is able to make a comparison (`==` or `!=` [`not_eq`]) with the same type `Allocator`.
9. Member functions of `Allocator`<br />
    *`allocate` : Building the fundamental facility for `Allocator`. The function holds a parameter with a default argument whose type is `sizeType`. By the way, If the argument is `0`, the function still need to allocate the memory, but the number of memory need allocating is undefined (The behaviour of throwing an exception when the argument is `0` is a ***WRONG BEHAVIOUR***). The returning-type of `allocate` is `pointer` who is first pointer of the linear sequence from `Allocator`.<br />
    *`construct` : The function is different from static function `construct`. This function can only construct for the pointer who is from the linear sequence from `Allocator`. So the parameter of this function can only accept the `pointer` and the arguments who is going to be used in constructing. The returning-type of this function is `pointer` who is the cursor pointer from the linear sequence from `Allocator`.<br />
    *`destroy` : The function is different from static function `destroy`. This function can only destruct for the pointer who is from the linear sequence from `Allocator`. It is an overloaded function, accepting an object-pointer or a range of object-pointer. The returning-type of this function is same as the function `construct`.<br />
    *`empty` : That the linear sequence is never be used will lead to returning `true`.<br />
    *`capacity` : Returns a `sizeType` type number who represents for the max capacity of `Allocator`.<br />
    *`reserve` : Returns a `sizeType` type number who represents for the reserve of `Allocator`.<br />
    *`begin` : Returns the first pointer of the linear sequence from `Allocator`.<br />
    *`getCursor` : This is an overloaded function that returns the cursor pointer of the linear sequence from `Allocator`.The one returns `constPointer` type, the other returns reference to `pointer`.<br />
    *`end` : Returns the pointer who is after last pointer of the linear sequence from `Allocator`.<br />
    *`resize` : Resets the size of `Allocator` and returns the new linear sequence's first pointer. It accepts an `sizeType` type argument. If the size accepted is less than the size of `Allocator` currently, the function will do nothing.<br />
    *`shrinkToFit` : Resets the size of `Allocator` to the size of current `Allocator` and returns the new linear sequence's first pointer.<br />
    *`swap` : Swaps two same type `Allocator`s.<br />
10. The global function `swap` in namespace `DataStructure` is used to swap to same type `Allocator`s.
11. The default constructor of `Allocator` should NOT do the things that the function `allocate` need to do.
12. The behaviour that deallocating the linear sequence from `Allocator` should leave to the destructor of `Allocator`.

#### The Undefined Behaviour in Designing Allocator

1. Whether the member function `construct` and `destroy` should check the pointer who is from argument.
2. Whether `Allocator` should hold the public member function named `full` that is used to check if the `Allocator` is full.
3. Whether the member function `destroy` should check if the `Allocator` is empty.
4. Whether `Allocator` should hold a memory pool.
5. Whether the overloaded static member function `operator new` and `operator delete` should allocate memory from memory pool who is from `Allocator`.
6. Whether `Allocator` should hole the overloaded operator `<`, `<=`, `>`, `>=`.
7. Whether the global function `swap` in namespace should be friend function to `Allocator` (If the function is not the friend function to `Allocator`, the function should use `Allocator`'s member function `swap` to implement).
8. Whether the parameter of the member function `construct` is reference to pointer.
9. Whether the member function `construct` will increment the pointer. (If implemented this, the parameter of member function `construct` should be reference to pointer).
10. If the member function `allocate` accepted an argument that is `0`, the function should continue allocate the memory normally, but the number of memory need allocating is undefined and should NOT continue be `0` (The behaviour of throwing an exception when the argument is `0` is a ***WRONG BEHAVIOUR***).
11. Whether `Allocator` should hold the member function named `clear` that is used to clear the element from linear sequence.
12. Whether the `Allocator`'s template parameter exists the number that is going to be used in member function `allocate`'s default argument. (If implemented this, this template parameter should hold a default argument. The type of this parameter should be `unsigned long`).
13. Whether the default constructor from `Allocator` is signed `constexpr`.
14. Whether the `Allocator` should hold the public member function to convert `Allocator` to `bool`. (If implemented this, this member function should be signed `explicit`).

## Completed

>- Vector : Vector is a sequence container that encapsulates dynamic size arrays.
>- ForwardList : ForwardList is a container that supports fast insertion and removal of elements from anywhere in the container.
>- List : List is a container that supports constant time insertion and removal of elements from anywhere in the container.
>- Deque : Deque (double-ended queue) is an indexed sequence container that allows fast insertion and deletion at both its beginning and its end.
>- Stack : Default Stack is a container adapter that gives the programmer the functionality of a stack - specifically, a FILO (first-in, last-out) data structure.
>- BilateralStack : A stack who is in high space-utilization rate. There are two stacks in every bilateral stack.
>- Queue : Default Queue is a container adapter that gives the programmer the functionality of a queue - specifically, a FIFO (first-in, first-out) data structure.

## Coming Soon...

>- StaticList
>- PriorityQueue
>- String
>- HeapString
>- BlockingLinkedString

## Environment

 ```
 macOS 10.13.6
 CLion 2018.2.4
 Apple LLVM version 10.0.0 (clang-1000.11.45.2)
 ```

The programme is based on C++ 11. So when you compile, you should add the command :

`-std=c++11`

# LICENSE

> Project : Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
