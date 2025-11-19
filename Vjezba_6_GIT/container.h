#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

class Container {
private:
    int* data;
    size_t m_size;
    size_t m_capacity;

public:
    Container(size_t initial_capacity = 0);
    Container(const Container& other);
    Container(Container&& other) noexcept;
    ~Container();

    void push_back(int value);
    size_t size() const;
    size_t capacity() const;
    int at(size_t index) const;
    void clear();
};

#endif
