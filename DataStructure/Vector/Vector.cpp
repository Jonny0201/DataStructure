#include "Vector.hpp"
#include <vector>

using namespace DataStructure;

template <typename T>
bool Vector<T>::checkFull() const {
    return this->cursor - this->first == this->allocateSize;
}
template <typename T>
void Vector<T>::reallocate() {
    /* Use the array of pointer to save the elements. */
    auto size {this->cursor - this->first};
    T *init {this->backup(this->first, size)};
    /* Reallocate the memory. */
    this->allocateSize *= 2;
    this->allocate();
    /* Put the backup elements to new Vector. */
    for(auto i {0}; i < size; ++i) {
        this->array.construct(this->cursor++, init[i]);
    }
    delete[] init;
    init = nullptr;
}
template <typename T>
inline void Vector<T>::allocate() {
    this->cursor = this->first = this->array.allocate(this->allocateSize);
    this->end = this->first + this->allocateSize;
}
template <typename T>
void Vector<T>::free() {
    auto freeCursor {this->first};
    while(freeCursor != this->cursor) {
        this->array.destroy(freeCursor++);
    }
    this->array.deallocate(this->first, static_cast<typename std::allocator<T>::size_type>(this->allocateSize));
    this->first = nullptr;
    this->cursor = nullptr;
    this->end = nullptr;
}
template <typename T>
T *Vector<T>::backup(T *cursor, size_t size, bool isErase) {
    T *init;
    try {
        init = new T [size];
    }catch(std::exception &e) {
        std::cerr << "Fail to allocate the memory!" << std::endl;
        return nullptr;
    }
    if(isErase) {
        return init;
    }
    for(auto i {0}; cursor != this->cursor; ++i) {
        init[i] = *cursor++;
    }
    this->free();
    return init;
}
template <typename T>
Vector<T>::Vector() {
    this->allocate();
}
template <typename T>
Vector<T>::Vector(size_t size, const T &element) {
    this->allocate();
    for(auto i {0}; i < size; ++i) {
        if(this->checkFull()) {
            this->reallocate();
        }
        this->array.construct(this->cursor++, element);
    }
}
/*template <typename T>
template <typename ...ARGS>
Vector<T>::Vector(ARGS &&...args) noexcept {
    this->allocate();
    this->array.construct(this->cursor++, std::forward<ARGS>(args)...);
}
template <typename T>
Vector<T>::Vector(T &&element, size_t size) noexcept {
    this->allocate();
    auto tmp {std::move(element)};
    for(auto i {0}; i < size; ++i) {
        if(this->checkFull()) {
            this->reallocate();
        }
        this->array.construct(this->cursor++, tmp);
    }
}*/
template <typename T>
Vector<T>::Vector(size_t size) {
    this->allocate();
    for(auto i {0}; i < size; ++i) {
        if(this->checkFull()) {
            this->reallocate();
        }
        this->array.construct(this->cursor++, T());
    }
}
/*template <typename T>
Vector<T>::Vector(T &&element) noexcept {
    this->allocate();
    this->array.construct(this->cursor++, std::forward<T>(element));
}*/
template <typename T>
Vector<T>::Vector(std::initializer_list<T> elements) {
    this->allocate();
    auto begin {elements.begin()};
    auto end {elements.end()};
    while(begin != end) {
        this->array.construct(this->cursor++, *begin++);
    }
}
template <typename T>
Vector<T>::Vector(const T *begin, const T *end) {
    this->allocate();
    auto arrayCursor {begin};
    while(arrayCursor != end) {
        this->array.construct(this->cursor++, *arrayCursor++);
    }
}
template <typename T>
Vector<T>::Vector(const Vector &other) {
    this->allocateSize = other.allocateSize;
    this->cursor = this->first = this->array.allocate(this->allocateSize);
    this->end = this->first + this->allocateSize;
    auto begin {other.first};
    auto end {other.cursor};
    while(begin != end) {
        this->array.construct(this->cursor++, *begin++);
    }
}
template <typename T>
Vector<T>::Vector(Vector &&other) noexcept {
    this->allocateSize = other.allocateSize;
    this->cursor = this->first = this->array.allocate(this->allocateSize);
    this->end = this->first + this->allocateSize;
    auto begin {other.first};
    auto end {other.cursor};
    while(begin != end) {
        this->array.construct(this->cursor++, std::move(*begin++));
    }
}
template <typename T>
Vector<T>::~Vector() {
    this->free();
    this->first = nullptr;
    this->cursor = nullptr;
    this->end = nullptr;
}
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if(&other == this) {
        return *this;
    }
    this->free();
    this->allocateSize = other.allocateSize;
    this->cursor = this->first = this->array.allocate(this->allocateSize);
    this->end = this->first + this->allocateSize;
    auto begin {other.first};
    auto end {other.cursor};
    while(begin != end) {
        this->array.construct(this->cursor++, *begin++);
    }
    return *this;
}
template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
    if(&other == this) {
        return *this;
    }
    this->free();
    this->allocateSize = other.allocateSize;
    this->cursor = this->first = this->array.allocate(this->allocateSize);
    this->end = this->first + this->allocateSize;
    auto begin {other.first};
    auto end {other.cursor};
    while(begin != end) {
        this->array.construct(this->cursor++, std::move(*begin++));
    }
    return *this;
}
template <typename T>
T &Vector<T>::operator[](unsigned n) const & {
    if(n >= static_cast<unsigned>(this->cursor - this->first)) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    return *(this->first + n);
}
template <typename T>
bool Vector<T>::operator==(const Vector &other) const {
    return this->size() == other.size() and [](const Vector &a, const Vector &b) -> bool {
        auto size {a.size()};
        std::equal_to<T> net;
        for(auto i {0}; i < size; ++i) {
            if(!net(a[i], b[i])) {
                return false;
            }
        }
        return true;
    }(*this, other);
}
template <typename T>
bool Vector<T>::operator!=(const Vector &other) const {
    return !(*this == other);
}
template <typename T>
bool Vector<T>::operator>(const Vector &other) const {
    if(this->size() != other.size()) {
        return this->size() > other.size();
    }
    return [](const Vector &a, const Vector &b) -> bool {
        auto size {a.size()};
        std::equal_to<T> et;
        std::greater<T> g;
        for(auto i {0}; i < size; ++i) {
            if(et(a[i], b[i])) {
                continue;
            }
            return g(a[i], b[i]);
        }
        return false;
    }(*this, other);
}
template <typename T>
bool Vector<T>::operator<(const Vector &other) const {
    return !(*this > other);
}
template <typename T>
bool Vector<T>::operator>=(const Vector &other) const {
    return *this == other or *this > other;
}
template <typename T>
bool Vector<T>::operator<=(const Vector &other) const {
    return *this == other or *this < other;
}
template <typename T>
Vector<T>::operator bool() const {
    return this->first != this->cursor;
}
template <typename T>
Vector<T> &Vector<T>::operator-() {
    auto cursor {this->first};
    while(cursor != this->cursor) {
        //*cursor++ = -*cursor;     //Undefined behaviour in C++.
        typename std::remove_reference<decltype(*cursor)>::type save {*cursor};
        *cursor++ = -save;
    }
    return *this;
}
template <typename T>
Vector<T> &Vector<T>::operator+() {
    return *this;
}
template <typename T>
#ifdef POP_GET_NUMBER
T
#else
void
#endif
    Vector<T>::popBack() {
    if(this->isEmpty()) {
        throw std::domain_error("Error, the vector is empty!");
    }
#ifdef POP_GET_NUMBER
    auto popNumber {*this->cursor};
#endif
    this->array.destroy(this->cursor--);
#ifdef POP_GET_NUMBER
    return popNumber;
#endif
}
template <typename T>
#ifdef POP_GET_NUMBER
T
#else
void
#endif
        Vector<T>::popFront() {
    if(this->isEmpty()) {
        throw std::domain_error("Error, the vector is empty!");
    }
#ifdef POP_GET_NUMBER
    auto popNumber {*this->cursor};
#endif
    this->erase(0);
#ifdef POP_GET_NUMBER
    return popNumber;
#endif
}
template <typename T>
void Vector<T>::pushBack(const T &element) {
    /* Check if there are vacancies so that the new element can be put in. */
    if(this->checkFull()) {
        this->reallocate();
    }
    this->array.construct(this->cursor++, element);
}
template <typename T>
void Vector<T>::pushFront(const T &element) {
    /* Check if there are vacancies so that the new element can be put in. */
    if(this->checkFull()) {
        this->reallocate();
    }
    this->insert(element, 0);
}
template <typename T>
T Vector<T>::at(unsigned n) const {
    if(n >= static_cast<unsigned>(this->cursor - this->first)) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    return static_cast<typename std::remove_reference<decltype((*this)[n])>::type>((*this)[n]);
}
template <typename T>
bool Vector<T>::isEmpty() const {
    return this->first == this->cursor;
}
template <typename T>
inline void Vector<T>::clear() {
    this->free();
    this->allocate();
}
template <typename T>
size_t Vector<T>::size() const {
    return static_cast<size_t>(this->cursor - this->first);
}
template <typename T>
const T Vector<T>::front() const {
    return static_cast<typename std::remove_reference<decltype(*this->first)>::type>(*this->first);
}
template <typename T>
const T Vector<T>::back() const {
    return static_cast<typename std::remove_reference<decltype(*this->cursor)>::type>(*(this->cursor - 1));
}
template <typename T>
T const *Vector<T>::getBegin() const {
    return this->first;
}
template <typename T>
T const *Vector<T>::getEnd() const {
    return this->cursor;
}
template <typename T>
const T *const Vector<T>::getConstantBegin() const {
    return static_cast<const T *const>(this->first);
}
template <typename T>
const T *const Vector<T>::getConstantEnd() const {
    return static_cast<const T *const>(this->end);
}
template <typename T>
template <typename ...Args>
T const *Vector<T>::emplaceBack(Args &&...args) noexcept {
    /* Check if there are vacancies so that the new element can be put in. */
    if(this->checkFull()) {
        this->reallocate();
    }
    this->array.construct(this->cursor, std::forward<Args>(args)...);
    return this->cursor++;      //Return the iterator is needed so that code-users can update the iterator that is created by themselves.
}
template <typename T>
template <typename ...Args>
T const *Vector<T>::emplaceFront(Args &&...args) noexcept {
    /* Check if there are vacancies so that the new element can be put in. */
    if(this->checkFull()) {
        this->reallocate();
    }
    this->emplace(0, std::forward<Args>(args)...);
    return this->first;     //Return the iterator is needed so that code-users can update the iterator that is created by themselves.
}
template <typename T>
template <typename ...Args>
T const *Vector<T>::emplace(unsigned position, Args &&...args) {
    /* Check if there are vacancies so that the new element can be put in. */
    if(position > this->cursor - this->first) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    T *returnPointer {nullptr};     //The pointer that is going to be returned.
    /* Backup the elements to a pointer array. */
    if(this->checkFull()) {
        this->reallocate();
    }
    auto size {this->cursor - this->first};
    T *init {this->backup(this->first, size)};
    /* Reallocate the memory. */
    this->allocate();
    /* Put the element including the element that will be emplaced to the new Vector. */
    auto index {0};
    for(auto i {0}; i < position; ++i) {
        this->array.construct(this->cursor++, init[index++]);
    }
    returnPointer = this->cursor;
    this->array.construct(this->cursor++, std::forward<Args>(args)...);
    for(auto i {index}; i < size; ++i) {
        this->array.construct(this->cursor++, init[index++]);
    }
    return returnPointer;       //Return the iterator is needed so that code-users can update the iterator that is created by themselves.
}
template <typename T>
T const *Vector<T>::insert(const T &element, unsigned position, size_t n) {
    if(position > this->cursor - this->first) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    T *returnPointer {nullptr};     //The pointer that is going to be returned.
    /* Check if there are vacancies so that the new element can be put in. */
    if(this->checkFull()) {
        this->reallocate();
    }
    /* Backup the elements to a pointer array. */
    auto size {this->cursor - this->first};
    T *init {this->backup(this->first, size)};
    /* Reallocate the memory. */
    this->allocate();
    /* Put the element including the element that will be inserted to the new Vector. */
    auto index {0};
    for(auto i {0}; i < position; ++i) {
        this->array.construct(this->cursor++, init[index++]);
    }
    returnPointer = this->cursor;
    for(auto i {0}; i < n; ++i) {
        if(checkFull()) {
            this->reallocate();
        }
        this->array.construct(this->cursor++, element);
    }
    for(auto i {index}; i < size; ++i) {
        this->array.construct(this->cursor++, init[index++]);
    }
    return returnPointer;       //Return the iterator is needed so that code-users can update the iterator that is created by themselves.
}
template <typename T>
T const *Vector<T>::insert(T &&element, unsigned position) {
    if(position > this->cursor - this->first) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    T temp {std::move(element)};
    return this->insert(temp, position);
}
template <typename T>
T const *Vector<T>::erase(unsigned position, size_t n) {
    if(position >= this->cursor - this->first) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    /* Backup the elements to a pointer array. */
    auto size {this->cursor - this->first - n};
    T *init {this->backup(this->first, size, true)};
    auto cursor {this->first};
    auto index {0};
    for(auto i {0}; i < position; ++i) {
        init[index++] = *cursor++;
    }
    auto loopCount {size + n};
    cursor += n;
    for(auto i {position + n}; i < loopCount; ++i) {
        init[index++] = *cursor++;
    }
    /* Reallocate the memory. */
    this->free();
    this->allocate();
    /* Put the element except the elements that will be erased to the new Vector. */
    for(auto i {0}; i < index; ++i) {
        this->array.construct(this->cursor++, init[i]);
    }
    return this->first + position;      //Return the iterator is needed so that code-users can update the iterator that is created by themselves.
}
/* WARNING :
 * The next functions is never being tested, if you want to use , please check it whether is work normally or not at first.
 * */
#ifdef OTHER_FUNCTION
template <typename T>
ptrdiff_t Vector<T>::find(const T &element) const {
    auto cursor {this->first};
    while(cursor != this->cursor) {
        if(*cursor++ == element) {
            return static_cast<int>(cursor - this->first);
        }
    }
    return 0;
}
template <typename T>
template <typename ...Args>
bool Vector<T>::find(const T &element, const Args &...args) const {
    if(this->find(element)) {
        return this->find(args...);
    }
    return false;
}
template <typename T>
Vector<T> Vector<T>::get(unsigned position, size_t n) const {
    if(n >= static_cast<unsigned>(this->cursor - this->first) or static_cast<size_t>(position) + n > this->size()) {
        throw std::out_of_range("Error, The array index is out of range!");
    }
    auto start {this->first + position};
    auto end {start + n};
    return Vector<T>(start, end);
}
template <typename T>
void Vector<T>::resize(size_t n, bool shrinkToFitCalling) {
    if(n < this->allocateSize and !shrinkToFitCalling) {
        return;
    }
    this->allocateSize = n;
    /* Use the array of pointer to save the elements. */
    auto size {this->cursor - this->first};
    T *init {this->backup(this->first, size)};
    /* Reallocate the memory. */
    this->allocate();
    /* Put the backup elements to new Vector. */
    for(auto i {0}; i < size; ++i) {
        this->array.construct(this->cursor++, init[i]);
    }
    delete[] init;
    init = nullptr;
}
template <typename T>
ptrdiff_t Vector<T>::reserve() const {
    return this->end - this->cursor;
}
template <typename T>
ptrdiff_t Vector<T>::capacity() const {
    return this->end - this->first;
}
template <typename T>
void Vector<T>::shrinkToFit() {
    this->resize(this->cursor - this->first, true);
}
#endif
#ifdef DEBUG_DATA_STRUCTURE_FOR_VECTOR
template <typename T>
std::allocator<T> *Vector<T>::getInwardAllocator() const {
    return &this->array;
}
template <typename T>
T *Vector<T>::getInwardFirst() const {
    return this->first;
}
template <typename T>
T *Vector<T>::getInwardCursor() const {
    return this->cursor;
}
template <typename T>
T *Vector<T>::getInwardEnd() const {
    return this->end;
}
#endif
