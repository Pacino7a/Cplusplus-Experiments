#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <cassert>
#include <algorithm> // for std::copy_n

// We created our own Array by class template here
template <typename T>
class Array
{
private:
    T *m_arr{nullptr}; // int * xx is not only a pointer to a int value, but also it's the adress of the first int in the array
    int m_length{};

public:
    Array() = default; // for Array arr{};

    Array(const int length)
    :   m_length{length}
    {
        assert(m_length > 0 && "Array Length should be a Positive Integer!");
        m_arr = new T[m_length];
    }

    // after we constructed this thing, we need block copy overloadings and implement list assignments
    Array(std::initializer_list<T> list)
    :   Array(static_cast<int>(list.size())) // delegating constructor (you can't delegate this to self and reduce the redundant)
    {
        std::copy_n(list.begin(), list.size(), m_arr); // we copy values in the list to our object
    }

    Array& operator=(std::initializer_list<T> list)
    {
        int newlength{static_cast<int>(list.size())};
        if(m_length != newlength)
            reAllocate(newlength);
        // list.begin()[2] = 9; // Const int* 
        std::copy_n(list.begin(), list.size(), m_arr);
        return *this;
    }

    T& operator[](const int index)
    {
        assert(index >= 0 && index < m_length);
        return m_arr[index];
    }
    T operator[](const int index) const
    {
        assert(index >= 0 && index < m_length);
        return m_arr[index];
    }

    void earse() // clear the array
    {
        delete[] m_arr;
        m_arr = nullptr;
        m_length = 0;
    }

    int getLength() const { return m_length; }

    void reAllocate(int newLength) // the base of deep copy, (prerequired for deep-copy implementation)
    {
        earse(); // clear the array

        if(newLength <= 0) // if user wants a empty array, we are done here.
            return;

        T *data{new T[static_cast<std::size_t>(newLength)]{}};
        m_arr = data;
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if(newLength == m_length)
            return;

        if(newLength <= 0)
        {
            earse();
            return;
        }

        T *data{new T[static_cast<std::size_t>(newLength)]{}};
        if(m_length > 0) // check whether we have elements in old container copy from
        {
            int ele2Copy{(newLength > m_length) ? m_length : newLength}; // Bucket Effect
            std::copy_n(m_arr, ele2Copy, data); // we should move the elements for optimizing the efficiency
        }
        delete[] m_arr;
        m_arr = data;
        m_length = newLength;
    }

    void insert(int index, T value)
    {
        assert(index >= 0 && index < m_length);

        T *data{new T[static_cast<std::size_t>(m_length + 1)]};
        std::copy_n(m_arr, index, data); // copy the first half (move will be faster)
        data[index] = value; // set the insertion
        std::copy_n(m_arr + index, m_length - index, data + index + 1); // copy the second half
        delete[] m_arr;
        m_arr = data;
        ++m_length;
    }

    void remove(int index)
    {
        assert(index >= 0 && index < m_length);

        if(m_length <= 1)
        {
            earse();
            return;
        }

        T *data{new T[static_cast<std::size_t>(m_length - 1)]};
        std::copy_n(m_arr,index,data); // the first half  (P.S. move will be faster than copy)
        std::copy_n(m_arr + index + 1, m_length - index - 1, data + index); // the second half
        delete[] m_arr;
        m_arr = data;
        --m_length;
    }

    ~Array()
    {
        delete[] m_arr;
    }

    friend std::ostream &operator<<(std::ostream &out, const Array &array) // we don't need <T> inside the class
    {
        for (int i{0}; i < array.m_length ; ++i)
        {
            out << array[i] << ' ';
        }
        return out;
    }

    // Note: we need block shallow copy here to avoid issue that ptr dangling caused.
    // At this point, both the temporary Array's m_arr and array->m_arr point to the same address (due to the shallow copy).
    // when assignment statment ends, array->m_arr will be dangling
    Array(const Array &other) = delete; // block the shallow copy
    Array &operator=(const Array &other) = delete; // block the shallow copy assignment
    

};

#endif
