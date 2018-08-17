# Data Structure

Project Name : Data Structure

Aim : Hopes it can help improve my programming skill!

## Introduction

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

I set protection to some functions I think it shouldn't be used casually, it is being protected by `#define`.

#### `Allocator`

`Allocator` plays a vital role in all containers. The responsibility of `Allocator` is to manage the memory.

The foremost thing I think is that the allocator should manage the memory by itself rather than by class-users. The designer of `Allocator` shouldn't let class-users deallocate the memory allocated by `Allocator`, which means the deconstructor of `Allocator` is responsible for deallocating the memory.

There should be four attributions for `Allocator` : `first`, `cursor`, `end` and `size`.

`Allocator` firstly allocates a large of memory, `first` is the first of the memory pointer, `end` is the end of the memory pointer and `size` for the size of memory that has been allocated. `cursor` is a pointer that always points to the next memory address that will be used. Due to the discrepanies of access method with STL's `std::allocator`, so you should design three functions to get memory pointers.

The copy constructor and move constructor should NOT be deleted constructors in `Allocator`, the two constructors should copy or move all things that are from other Allocators.

`Allocator` also should hold the copy assign operator and move assign operator.

Apart from what has mentioned above, these functions are the basic of `Allocator` : `allocate`, `construct` and `destroy`. These functions is similar to the functions from STL's `std::allocator`.

These attributions and functions is a must for `Allocator`, otherwise your `Allocator` cannot be compatible with the containers from DataStructure.

If you want your `Allocator` more powerful, you can design these two functions : `resize` for resize the size of allocated memory and `shrinkToFit` for shrink the memory that hasn't been used. If you defined some macro to unlock some functions, then you must design `resize` and `shrinkToFit` function.

Finally, Allocator should hold two functions : `operator new` and `operator delete`. I suggest there can be a memory pool in the allocator.

## Completed

>- Vector : It is designed by array whose behaviour like an array.
>- ForwardList : The list whose iterator only can go forward.
>- List : The list whose iterator can not only go forward, but also go back.

## Coming Soon...

>- StaticList
>- Stack
>- BilateralStack
>- Queue
>- PriorityQueue
>- Deque
>- String
>- HeapString
>- BlockingLinkedString

## Environment

 ```
 macOS 10.13.5
 CLion 2018.1.2
 Apple LLVM version 9.1.0 (clang-902.0.39.2)
 ```

The programme is based on C++ 11. So when you compile, you should add the command :

`-std=c++11`

# LICENSE

> Project : Data Structure

> Copyright © 2018 [Jonny Charlotte](https://jonny.vip)
