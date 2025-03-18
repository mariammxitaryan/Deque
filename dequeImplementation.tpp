#include "dequeHeader.hpp"

template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::iterator::iterator(Deque<T, BLOCK_SIZE>* d, size_t bIdx, size_t off) : deque(d), blockIndex(bIdx), offset(off) {}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator::reference Deque<T, BLOCK_SIZE>::iterator::operator*() const {
    return deque->map[blockIndex][offset];
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& Deque<T, BLOCK_SIZE>::iterator::operator++() {
    if (++offset == BLOCK_SIZE) {
        offset = 0;
        ++blockIndex;
    }
    return *this;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::iterator::operator++(int) {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& Deque<T, BLOCK_SIZE>::iterator::operator--() {
    if (--offset == 0) {
        offset = BLOCK_SIZE;
        --blockIndex;
    }
    return *this;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::iterator::operator--(int) {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    --(*this);
    return temp;
}
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& Deque<T, BLOCK_SIZE>::iterator::operator+=(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) {
    blockIndex += (offset + n) / BLOCK_SIZE;
    offset = (offset + n) % BLOCK_SIZE;
    return *this;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::iterator::operator+(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    return temp += n;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator& Deque<T, BLOCK_SIZE>::iterator::operator-=(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) {
    return *this += -n;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::iterator::operator-(typename Deque<T, BLOCK_SIZE>::iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::iterator temp = *this;
    return temp -= n;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator::difference_type Deque<T, BLOCK_SIZE>::iterator::operator-(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return (blockIndex - other.blockIndex) * BLOCK_SIZE  + (offset - other.offset);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator==(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return ((blockIndex ==  other.blockIndex) && (offset == other.offset));
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator!=(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return !(*this == other);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator<(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return  blockIndex < other.blockIndex || (blockIndex == other.blockIndex && offset < other.offset);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator>(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return other < *this;
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator<=(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return !(other < *this);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::iterator::operator>=(const typename Deque<T, BLOCK_SIZE>::iterator& other) const {
    return !(*this < other);
}

template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::const_iterator::const_iterator(const Deque<T, BLOCK_SIZE>* d, size_t bIdx, size_t off) : deque(d), blockIndex(bIdx), offset(off) {}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator::reference Deque<T, BLOCK_SIZE>::const_iterator::operator*() const { 
    return deque->map[blockIndex][offset]; 
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& Deque<T, BLOCK_SIZE>::const_iterator::operator++() {
    if (++offset == BLOCK_SIZE) {
        offset = 0;
        ++blockIndex;
    }
    return *this;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::const_iterator::operator++(int) {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& Deque<T, BLOCK_SIZE>::const_iterator::operator--() {
    if (offset == 0) {
        offset = BLOCK_SIZE;
        --blockIndex;
    }
    --offset;
    return *this;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::const_iterator::operator--(int) {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& Deque<T, BLOCK_SIZE>::const_iterator::operator+=(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) {
    blockIndex += (offset + n) / BLOCK_SIZE;
    offset = (offset + n) % BLOCK_SIZE;
    return *this;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::const_iterator::operator+(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    return temp += n;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator& Deque<T, BLOCK_SIZE>::const_iterator::operator-=(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) const {
    return *this += -n;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::const_iterator::operator-(typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type n) const {
    typename Deque<T, BLOCK_SIZE>::const_iterator temp = *this;
    return temp -= n;
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator::difference_type Deque<T, BLOCK_SIZE>::const_iterator::operator-(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return (blockIndex - other.blockIndex) * BLOCK_SIZE  + (offset - other.offset);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator==(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return (blockIndex == other.blockIndex) && (offset == other.offset);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator!=(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return !(*this == other);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator<(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return blockIndex < other.blockIndex || (blockIndex == other.blockIndex && offset < other.offset);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator>(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return other < *this;
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator<=(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return !(other < *this);
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::const_iterator::operator>=(const typename Deque<T, BLOCK_SIZE>::const_iterator& other) const {
    return !(*this < other);
}

template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::Deque(size_t  initialSize) : mapSize(initialSize), frontIndex(initialSize/2),
backIndex(initialSize/2), frontOffset(0), backOffset(0) {
    initializeMap(initialSize);
    allocateBlock(frontIndex);
}

template <typename T, size_t BLOCK_SIZE>
Deque<T, BLOCK_SIZE>::~Deque() {
    if (!empty()) {
        for (int i = 0; i < mapSize; ++i) {
            deallocateBlock(i);
        }
        delete[] map;
    }
}

template <typename T, size_t BLOCK_SIZE>
bool Deque<T, BLOCK_SIZE>::empty() const {
    return (frontIndex ==  backIndex) && (frontOffset == backOffset);
}

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

template <typename T, size_t BLOCK_SIZE>
T& Deque<T, BLOCK_SIZE>::operator[](size_t index) {
    size_t Index = BLOCK_SIZE * frontIndex + frontOffset + index;
    size_t blockIndex = Index / BLOCK_SIZE;
    size_t offset = Index % BLOCK_SIZE;
    return map[blockIndex][offset];
}

template <typename T, size_t BLOCK_SIZE>
T& Deque<T, BLOCK_SIZE>::at(size_t index) {
    if (index < 0 || index >= size()) {
        throw std::runtime_error("Invalid index.\n");
    }
    return (*this)[index];
}

template <typename T, size_t BLOCK_SIZE>
size_t Deque<T, BLOCK_SIZE>::size() const {
    return (backIndex - frontIndex) * BLOCK_SIZE + (backOffset - frontOffset);
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::begin() {
    return Deque<T, BLOCK_SIZE>::iterator(this, frontIndex, frontOffset);
}
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::iterator Deque<T, BLOCK_SIZE>::end() {
    return Deque<T, BLOCK_SIZE>::iterator(this, backIndex, backOffset);
}

template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::cbegin() const { 
    return typename Deque<T, BLOCK_SIZE>::const_iterator(this, frontIndex, frontOffset); 
}
template <typename T, size_t BLOCK_SIZE>
typename Deque<T, BLOCK_SIZE>::const_iterator Deque<T, BLOCK_SIZE>::cend() const { 
    return typename Deque<T, BLOCK_SIZE>::const_iterator(this, backIndex, backOffset); 
}

template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::initializeMap(size_t size) {
    map = new T*[size];
    for (int i = 0; i < size; ++i) {
        map[i] = nullptr;
    }
}

template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::allocateBlock(size_t index) {
    if (map[index] == nullptr) {
        map[index] = new T[BLOCK_SIZE];
    }
}

template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::deallocateBlock(size_t index) {
    if (map[index] != nullptr) {
        delete []map[index];
    }
}

template <typename T, size_t BLOCK_SIZE>
void Deque<T, BLOCK_SIZE>::growMap() {
    size_t newMapSize = mapSize * 2;
    T** newMap  =  new T*[newMapSize];
    size_t offset = mapSize / 2;
    for (int i = 0; i < mapSize; ++i) {
        newMap[i + offset] = map[i];
    }
    for (int i = 0; i < offset; ++i) {
        newMap[i] = nullptr;
        newMap[i + mapSize + offset] = nullptr;
    }
    frontOffset += offset;
    backOffset += offset;
    delete []map;
    map = newMap;
    mapSize = newMapSize;
}
