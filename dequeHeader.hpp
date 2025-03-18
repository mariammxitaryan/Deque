#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>
 
template <typename T, size_t BLOCK_SIZE = 4>
class Deque {
private:
    T** map;
    size_t mapSize;
    size_t frontIndex; 
    size_t backIndex; 
    size_t frontOffset; 
    size_t backOffset; 

public:
    class iterator {
    private:
        Deque* deque;
        size_t blockIndex;
        size_t offset;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

        iterator(Deque*, size_t, size_t);
        reference operator*() const;
        iterator& operator++();
        iterator operator++(int);
        iterator operator--();
        iterator operator--(int);
        iterator& operator+=(difference_type);
        iterator operator+(difference_type n) const;
        iterator& operator-=(difference_type  n);
        iterator operator-(difference_type n) const;
        difference_type operator-(const iterator&) const;
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool operator<(const iterator&) const;
        bool operator>(const iterator&) const;
        bool operator<=(const iterator&) const;
        bool operator>=(const iterator&) const;
    };
    
    class const_iterator {
    private:
        const Deque* deque;
        size_t blockIndex;
        size_t offset;
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

        const_iterator(const Deque*, size_t, size_t);
        reference operator*() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator operator--();
        const_iterator operator--(int);
        const_iterator& operator+=(difference_type);
        const_iterator operator+(difference_type n) const;
        const_iterator& operator-=(difference_type  n);
        const_iterator operator-(difference_type n) const;
        difference_type operator-(const const_iterator&) const;
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        bool operator<(const const_iterator&) const;
        bool operator>(const const_iterator&) const;
        bool operator<=(const const_iterator&) const;
        bool operator>=(const const_iterator&) const;
    };

    Deque(size_t initialSize = 4);
    ~Deque();
    bool empty() const;
    void push_front(const T&);
    void push_back(const T&);
    T& operator[](size_t);
    T& at(size_t);    
    size_t size() const;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    void initializeMap(size_t);
    void allocateBlock(size_t);
    void deallocateBlock(size_t);
    void growMap();
};

#include "dequeImplementation.tpp" 

#endif