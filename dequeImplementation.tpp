#include "dequeHeader.hpp"

/**************************************************************************************************
 * @brief Constructs an iterator for the deque.
 * 
 * @param d Pointer to the deque object.
 * @param bIdx Starting block index in the deque's map.
 * @param off  Starting offset within the block.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::iterator::iterator(Deque<T, BLOCK_SIZE>* d, size_t bIdx, size_t off)
    : deque(d), blockIndex(bIdx), offset(off) {}

/**************************************************************************************************
 * @brief Dereferences the iterator to access the element.
 * 
 * @return Reference to the element at the current iterator position.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator::reference 
Deque<T, BLOCK_SIZE>::iterator::operator*() const {
    return deque->map[blockIndex][offset];
}

/**************************************************************************************************
 * @brief Pre-increment operator.
 * 
 * Moves the iterator forward by one element. If the offset reaches BLOCK_SIZE,
 * it resets the offset to 0 and increments the block index.
 * 
 * @return Reference to the updated iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& 
Deque<T, BLOCK_SIZE>::iterator::operator++() {
    if (++offset == BLOCK_SIZE) {
        offset = 0;
        ++blockIndex;
    }
    return *this;
}

/**************************************************************************************************
 * @brief Post-increment operator.
 * 
 * Returns the iterator state before incrementing. The iterator is then advanced by one element.
 * 
 * @return A copy of the iterator before it was incremented.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator 
Deque<T, BLOCK_SIZE>::iterator::operator++(int) {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    ++(*this);
    return temp;
}

/**************************************************************************************************
 * @brief Pre-decrement operator.
 * 
 * Moves the iterator backward by one element. If decrementing the offset makes it zero,
 * the offset is set to BLOCK_SIZE and the block index is decremented.
 * 
 * @return Reference to the updated iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& 
Deque<T, BLOCK_SIZE>::iterator::operator--() {
    if (--offset == 0) {
        offset = BLOCK_SIZE;
        --blockIndex;
    }
    return *this;
}

/**************************************************************************************************
 * @brief Post-decrement operator.
 * 
 * Returns the iterator state before decrementing. The iterator is then moved backward by one element.
 * 
 * @return A copy of the iterator before it was decremented.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator 
Deque<T, BLOCK_SIZE>::iterator::operator--(int) {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    --(*this);
    return temp;
}

/**************************************************************************************************
 * @brief Advances the iterator by a given number of positions.
 * 
 * Uses arithmetic to compute the new block index and offset based on the input displacement.
 * 
 * @param n Number of positions to advance.
 * @return Reference to the updated iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& 
Deque<T, BLOCK_SIZE>::iterator::operator+=(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) {
    blockIndex += (offset + n) / BLOCK_SIZE;
    offset = (offset + n) % BLOCK_SIZE;
    return *this;
}

/**************************************************************************************************
 * @brief Returns an iterator advanced by a given number of positions.
 * 
 * Creates a temporary copy of the iterator, advances it, and returns the copy.
 * 
 * @param n Number of positions to advance.
 * @return Iterator advanced by n positions.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator 
Deque<T, BLOCK_SIZE>::iterator::operator+(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    return temp += n;
}

/**************************************************************************************************
 * @brief Moves the iterator backward by a given number of positions.
 * 
 * This function subtracts positions by adding the negative of n.
 * 
 * @param n Number of positions to move backward.
 * @return Reference to the updated iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& 
Deque<T, BLOCK_SIZE>::iterator::operator-=(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) {
    return *this += -n;
}

/**************************************************************************************************
 * @brief Returns an iterator moved backward by a given number of positions.
 * 
 * Creates a temporary copy of the iterator, moves it backward, and returns the copy.
 * 
 * @param n Number of positions to move backward.
 * @return Iterator moved backward by n positions.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator 
Deque<T, BLOCK_SIZE>::iterator::operator-(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    return temp -= n;
}

/**************************************************************************************************
 * @brief Calculates the distance between two iterators.
 * 
 * Computes the difference based on the block index and offset differences.
 * 
 * @param other The iterator to subtract.
 * @return The difference (number of elements) between this iterator and other.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator::difference_type 
Deque<T, BLOCK_SIZE>::iterator::operator-(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return (blockIndex - other.blockIndex) * BLOCK_SIZE + (offset - other.offset);
}

/**************************************************************************************************
 * @brief Equality comparison for iterators.
 * 
 * Checks if two iterators are at the same block and offset.
 * 
 * @param other The iterator to compare with.
 * @return true if both iterators point to the same position; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator==(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return ((blockIndex == other.blockIndex) && (offset == other.offset));
}

/**************************************************************************************************
 * @brief Inequality comparison for iterators.
 * 
 * Determines if two iterators point to different positions.
 * 
 * @param other The iterator to compare with.
 * @return true if the iterators are not equal; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator!=(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return !(*this == other);
}

/**************************************************************************************************
 * @brief Less-than comparison for iterators.
 * 
 * Determines if the current iterator precedes another based on block index and offset.
 * 
 * @param other The iterator to compare with.
 * @return true if this iterator is before other; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator<(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return blockIndex < other.blockIndex || (blockIndex == other.blockIndex && offset < other.offset);
}

/**************************************************************************************************
 * @brief Greater-than comparison for iterators.
 * 
 * Checks if this iterator comes after the other iterator.
 * 
 * @param other The iterator to compare with.
 * @return true if this iterator is after other; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator>(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return other < *this;
}

/**************************************************************************************************
 * @brief Less-than-or-equal-to comparison for iterators.
 * 
 * Determines if this iterator is before or at the same position as the other.
 * 
 * @param other The iterator to compare with.
 * @return true if this iterator is not after the other; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator<=(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return !(other < *this);
}

/**************************************************************************************************
 * @brief Greater-than-or-equal-to comparison for iterators.
 * 
 * Determines if this iterator is at the same position or comes after the other.
 * 
 * @param other The iterator to compare with.
 * @return true if this iterator is not before the other; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator>=(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return !(*this < other);
}

/**************************************************************************************************
 * @brief Constructs a const_iterator for the deque.
 * 
 * @param d Pointer to the constant deque.
 * @param bIdx Starting block index.
 * @param off  Starting offset within the block.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::const_iterator::const_iterator(const Deque<T, BLOCK_SIZE>* d, size_t bIdx, size_t off)
    : deque(d), blockIndex(bIdx), offset(off) {}

/**************************************************************************************************
 * @brief Dereferences the const_iterator to access the element.
 * 
 * @return Constant reference to the element at the current const_iterator position.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator::reference 
Deque<T, BLOCK_SIZE>::const_iterator::operator*() const { 
    return deque->map[blockIndex][offset]; 
}

/**************************************************************************************************
 * @brief Pre-increment operator for const_iterator.
 * 
 * Advances the const_iterator by one element, adjusting block index and offset as needed.
 * 
 * @return Reference to the updated const_iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& 
Deque<T, BLOCK_SIZE>::const_iterator::operator++() {
    if (++offset == BLOCK_SIZE) {
        offset = 0;
        ++blockIndex;
    }
    return *this;
}

/**************************************************************************************************
 * @brief Post-increment operator for const_iterator.
 * 
 * Returns the state of the const_iterator before advancing it by one element.
 * 
 * @return A copy of the const_iterator before it was incremented.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator 
Deque<T, BLOCK_SIZE>::const_iterator::operator++(int) {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    ++(*this);
    return temp;
}

/**************************************************************************************************
 * @brief Pre-decrement operator for const_iterator.
 * 
 * Moves the const_iterator backward by one element. Adjusts the block index and offset accordingly.
 * 
 * @return Reference to the updated const_iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& 
Deque<T, BLOCK_SIZE>::const_iterator::operator--() {
    if (offset == 0) {
        offset = BLOCK_SIZE;
        --blockIndex;
    }
    --offset;
    return *this;
}

/**************************************************************************************************
 * @brief Post-decrement operator for const_iterator.
 * 
 * Returns the state of the const_iterator before moving it backward by one element.
 * 
 * @return A copy of the const_iterator before it was decremented.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator 
Deque<T, BLOCK_SIZE>::const_iterator::operator--(int) {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    --(*this);
    return temp;
}

/**************************************************************************************************
 * @brief Advances the const_iterator by a given number of positions.
 * 
 * Adjusts the block index and offset using arithmetic to move forward.
 * 
 * @param n Number of positions to advance.
 * @return Reference to the updated const_iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& 
Deque<T, BLOCK_SIZE>::const_iterator::operator+=(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) {
    blockIndex += (offset + n) / BLOCK_SIZE;
    offset = (offset + n) % BLOCK_SIZE;
    return *this;
}

/**************************************************************************************************
 * @brief Returns a const_iterator advanced by a given number of positions.
 * 
 * Creates a temporary copy, advances it, and returns the new const_iterator.
 * 
 * @param n Number of positions to advance.
 * @return const_iterator advanced by n positions.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator 
Deque<T, BLOCK_SIZE>::const_iterator::operator+(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    return temp += n;
}

/**************************************************************************************************
 * @brief Moves the const_iterator backward by a given number of positions.
 * 
 * Utilizes negative advancement to move the iterator backward.
 * 
 * @param n Number of positions to move backward.
 * @return Reference to the updated const_iterator.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& 
Deque<T, BLOCK_SIZE>::const_iterator::operator-=(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) const {
    return *this += -n;
}

/**************************************************************************************************
 * @brief Returns a const_iterator moved backward by a given number of positions.
 * 
 * Creates a temporary copy, moves it backward, and returns it.
 * 
 * @param n Number of positions to move backward.
 * @return const_iterator moved backward by n positions.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator 
Deque<T, BLOCK_SIZE>::const_iterator::operator-(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    return temp -= n;
}

/**************************************************************************************************
 * @brief Calculates the distance between two const_iterators.
 * 
 * Determines the difference in positions based on block index and offset.
 * 
 * @param other The const_iterator to subtract.
 * @return The difference (number of elements) between this iterator and other.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type 
Deque<T, BLOCK_SIZE>::const_iterator::operator-(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return (blockIndex - other.blockIndex) * BLOCK_SIZE + (offset - other.offset);
}

/**************************************************************************************************
 * @brief Equality comparison for const_iterators.
 * 
 * Checks if both const_iterators point to the same block and offset.
 * 
 * @param other The const_iterator to compare with.
 * @return true if they are equal; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator==(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return (blockIndex == other.blockIndex) && (offset == other.offset);
}

/**************************************************************************************************
 * @brief Inequality comparison for const_iterators.
 * 
 * Determines if two const_iterators do not point to the same position.
 * 
 * @param other The const_iterator to compare with.
 * @return true if they differ; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator!=(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return !(*this == other);
}

/**************************************************************************************************
 * @brief Less-than comparison for const_iterators.
 * 
 * Compares two const_iterators to determine ordering based on block and offset.
 * 
 * @param other The const_iterator to compare with.
 * @return true if this const_iterator precedes the other; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator<(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return blockIndex < other.blockIndex || (blockIndex == other.blockIndex && offset < other.offset);
}

/**************************************************************************************************
 * @brief Greater-than comparison for const_iterators.
 * 
 * Checks if this const_iterator comes after the other.
 * 
 * @param other The const_iterator to compare with.
 * @return true if it is greater; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator>(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return other < *this;
}

/**************************************************************************************************
 * @brief Less-than-or-equal-to comparison for const_iterators.
 * 
 * Determines if this const_iterator is not after the other.
 * 
 * @param other The const_iterator to compare with.
 * @return true if it is less than or equal; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator<=(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return !(other < *this);
}

/**************************************************************************************************
 * @brief Greater-than-or-equal-to comparison for const_iterators.
 * 
 * Determines if this const_iterator is not before the other.
 * 
 * @param other The const_iterator to compare with.
 * @return true if it is greater than or equal; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator>=(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return !(*this < other);
}

/**************************************************************************************************
 * @brief Constructs a Deque object.
 * 
 * Initializes the map with the given initial size, positions the front and back indices 
 * in the middle of the map, and allocates the initial block.
 * 
 * @param initialSize The initial size of the map.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::Deque(size_t initialSize) 
    : mapSize(initialSize), frontIndex(initialSize/2), backIndex(initialSize/2),
      frontOffset(0), backOffset(0) {
    initializeMap(initialSize);
    allocateBlock(frontIndex);
}

/**************************************************************************************************
 * @brief Destructor for the Deque.
 * 
 * Deallocates all allocated blocks and deletes the map.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::~Deque() {
    if (!empty()) {
        for (int i = 0; i < mapSize; ++i) {
            deallocateBlock(i);
        }
        delete[] map;
    }
}

/**************************************************************************************************
 * @brief Checks if the deque is empty.
 * 
 * @return true if there are no elements in the deque; otherwise, false.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::empty() const {
    return (frontIndex == backIndex) && (frontOffset == backOffset);
}

/**************************************************************************************************
 * @brief Inserts an element at the front of the deque.
 * 
 * If the front block is exhausted, a new block is allocated.
 * The element is then placed at the proper position.
 * 
 * @param value The element to be inserted.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::push_front(const T& value) {
    if (!frontOffset) {
        if (!frontIndex) {
            growMap(); 
        }
        allocateBlock(--frontIndex);
        frontOffset = BLOCK_SIZE;
    }
    map[frontIndex][--frontOffset] = value;
}

/**************************************************************************************************
 * @brief Inserts an element at the back of the deque.
 * 
 * If the current back block is full, a new block is allocated.
 * The element is then placed at the back position.
 * 
 * @param value The element to be inserted.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::push_back(const T& value) {
    if (backOffset == BLOCK_SIZE) {
        if(backIndex == mapSize - 1) {
            growMap();
        }
        allocateBlock(++backIndex);
        backOffset = 0;
    }
    map[backIndex][backOffset++] = value;
}

/**************************************************************************************************
 * @brief Access operator for the deque.
 * 
 * Provides random access to elements based on a zero-based index.
 * The internal calculation determines the block and offset.
 * 
 * @param index The position of the element.
 * @return Reference to the element at the specified index.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
T& Deque<T, BLOCK_SIZE>::operator[](size_t index) {
    size_t Index = BLOCK_SIZE * frontIndex + frontOffset + index;
    size_t blockIndex = Index / BLOCK_SIZE;
    size_t offset = Index % BLOCK_SIZE;
    return map[blockIndex][offset];
}

/**************************************************************************************************
 * @brief Accesses an element with bounds checking.
 * 
 * Throws a runtime error if the index is out of bounds.
 * 
 * @param index The position of the element.
 * @return Reference to the element at the specified index.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
T& Deque<T, BLOCK_SIZE>::at(size_t index) {
    if (index < 0 || index >= size()) {
        throw std::runtime_error("Invalid index.\n");
    }
    return (*this)[index];
}

/**************************************************************************************************
 * @brief Returns the number of elements in the deque.
 * 
 * Computes the size using the difference between the front and back positions.
 * 
 * @return The total number of elements.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
size_t Deque<T, BLOCK_SIZE>::size() const {
    return (backIndex - frontIndex) * BLOCK_SIZE + (backOffset - frontOffset);
}

/**************************************************************************************************
 * @brief Returns an iterator to the beginning of the deque.
 * 
 * The iterator is positioned at the first element.
 * 
 * @return An iterator to the front of the deque.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator 
Deque<T, BLOCK_SIZE>::begin() {
    return Deque<T, BLOCK_SIZE>::iterator(this, frontIndex, frontOffset);
}

/**************************************************************************************************
 * @brief Returns an iterator to the end of the deque.
 * 
 * The iterator is positioned one element past the last valid element.
 * 
 * @return An iterator to the end of the deque.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator 
Deque<T, BLOCK_SIZE>::end() {
    return Deque<T, BLOCK_SIZE>::iterator(this, backIndex, backOffset);
}

/**************************************************************************************************
 * @brief Returns a constant iterator to the beginning of the deque.
 * 
 * @return A const_iterator to the first element.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator 
Deque<T, BLOCK_SIZE>::cbegin() const { 
    return typename Deque<T, BLOCK_SIZE>::const_iterator(this, frontIndex, frontOffset); 
}

/**************************************************************************************************
 * @brief Returns a constant iterator to the end of the deque.
 * 
 * @return A const_iterator one past the last element.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator 
Deque<T, BLOCK_SIZE>::cend() const { 
    return typename Deque<T, BLOCK_SIZE>::const_iterator(this, backIndex, backOffset); 
}

/**************************************************************************************************
 * @brief Initializes the internal map for block pointers.
 * 
 * Allocates an array of pointers and initializes each to nullptr.
 * 
 * @param size The number of block pointers to allocate.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::initializeMap(size_t size) {
    map = new T*[size];
    for (int i = 0; i < size; ++i) {
        map[i] = nullptr;
    }
}

/**************************************************************************************************
 * @brief Allocates a block at a given index.
 * 
 * Checks if the block pointer is nullptr and, if so, allocates a new block.
 * 
 * @param index The index in the map where the block should be allocated.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::allocateBlock(size_t index) {
    if (map[index] == nullptr) {
        map[index] = new T[BLOCK_SIZE];
    }
}

/**************************************************************************************************
 * @brief Deallocates a block at a given index.
 * 
 * Deletes the allocated block if it exists.
 * 
 * @param index The index in the map of the block to deallocate.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::deallocateBlock(size_t index) {
    if (map[index] != nullptr) {
        delete [] map[index];
    }
}

/**************************************************************************************************
 * @brief Expands the internal map when more blocks are needed.
 * 
 * Doubles the map size, copies the existing blocks to the new map with an offset,
 * and initializes the new areas to nullptr.
 **************************************************************************************************/
template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::growMap() {
    size_t newMapSize = mapSize * 2;
    T** newMap = new T*[newMapSize];

    size_t offset = mapSize / 2;
    for (size_t i = 0; i < mapSize; ++i) {
        newMap[i + offset] = map[i];
    }

    for (size_t i = 0; i < offset; ++i) {
        newMap[i] = nullptr;
        newMap[i + mapSize] = nullptr;
    }

    delete[] map;
    map = newMap;
    mapSize = newMapSize;
}
