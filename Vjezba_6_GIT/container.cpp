#include "container.h"

Container::Container(size_t initial_capacity)
    : data(nullptr), m_size(0), m_capacity(initial_capacity)
{
    std::cout << "Konstruktor (capacity=" << m_capacity << ")\n";
    if (m_capacity > 0)
        data = new int[m_capacity];
}

Container::Container(const Container& other)
    : data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity)
{
    std::cout << "Copy konstruktor\n";
    if (m_capacity > 0) {
        data = new int[m_capacity];
        for (size_t i = 0; i < m_size; i++)
            data[i] = other.data[i];
    }
}

Container::Container(Container&& other) noexcept
    : data(other.data), m_size(other.m_size), m_capacity(other.m_capacity)
{
    std::cout << "Move konstruktor\n";
    other.data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

Container::~Container()
{
    std::cout << "Destruktor (oslobadjam memoriju)\n";
    delete[] data;
}

void Container::push_back(int value)
{
    if (m_size == m_capacity) {
        size_t new_capacity = (m_capacity == 0 ? 1 : m_capacity * 2);
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < m_size; i++)
            new_data[i] = data[i];

        delete[] data;
        data = new_data;
        m_capacity = new_capacity;

        std::cout << "Realokacija, novi capacity=" << new_capacity << "\n";
    }

    data[m_size++] = value;
}

size_t Container::size() const { return m_size; }
size_t Container::capacity() const { return m_capacity; }

int Container::at(size_t index) const
{
    return data[index];
}

void Container::clear()
{
    m_size = 0;
}
