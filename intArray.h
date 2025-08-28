#ifndef INTARRAY_H
#define INTARRAY_H
#include <iostream>
#include <cassert>
#include <algorithm> // for std::copy_n

// We created our own Int Array in this section
class IntArray
{
private:
    int *m_arr{nullptr}; // int * xx is not only a pointer to a int value, but also it's the adress of the first int in the array
    int m_length{};

public:
    IntArray() = default;

    IntArray(const int length)
    :   m_length{length}
    {
        assert(m_length > 0 && "IntArray Length should be a Positive Integer!");
        m_arr = new int[m_length];
    }

    // after we constructed this thing, we need block copy overloadings and implement list assignments
    IntArray(std::initializer_list<int> list)
    :   IntArray(static_cast<int>(list.size())) // delegating constructor (you can't delegate this to self and reduce the redundant)
    {
        std::copy_n(list.begin(), list.size(), m_arr); // we copy values in the list to our object
    }

    IntArray& operator=(std::initializer_list<int> list)
    {
        int newlength{static_cast<int>(list.size())};
        if(m_length != newlength)
            reAllocate(newlength);
        // list.begin()[2] = 9; // Const int* 
        std::copy_n(list.begin(), list.size(), m_arr);
        return *this;
    }

    int& operator[](const int index)
    {
        assert(index >= 0 && index < m_length);
        return m_arr[index];
    }
    int operator[](const int index) const
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

        int *data{new int[static_cast<std::size_t>(newLength)]};
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

        int *data{new int[static_cast<std::size_t>(newLength)]};
        if(m_length > 0) // check whether we have elements in old container copy from
        {
            int ele2Copy{(newLength > m_length) ? m_length : newLength}; // Bucket Effect
            std::copy_n(m_arr, ele2Copy, data); // we should move the elements for optimizing the efficiency
        }
        delete[] m_arr;
        m_arr = data;
        m_length = newLength;
    }

    // we need both of them to make sure the deep copy will be implemented
    // IntArray(const IntArray& other) //copy constructor (Deep copy) (new object created by copied a existed one)
    // :   m_length{other.m_length}
    // {
    //     // we don't need check self-copy here, because IntArray a{a} makes no any sense
    //     m_arr = new int[m_length];
    //     for (int i = 0; i < m_length; ++i)
    //     {
    //         m_arr[i] = other.m_arr[i];
    //     }
    // }

    // COPY HERE --------------------------------
    // IntArray(const IntArray& other)
    //     : IntArray(other.getLength()) // initialize a new obj for copying
    // {
    //     std::copy_n(other.m_arr, m_length, m_arr); // we use STL here, instead of implementing this by ourselves
    //     // move will be faster
    // }
    
    // IntArray& operator= (const IntArray& other) // deep copy (copy assignment)
    // {
    //     if(this == &other)
    //         return *this;

    //     delete[] m_arr;
    //     m_length = other.m_length;
    //     m_arr = new int[m_length];
    //     for (int i = 0; i < m_length; ++i)
    //     {
    //         m_arr[i] = other.m_arr[i];
    //     }
    //     return *this;
    // }
    // --------------------------------------------------------------------------

    // IntArray& operator=(const IntArray& other)
    // {
    //     if(this == &other)
    //         return *this;

    //     reAllocate(other.getLength());
    //     std::copy_n(other.m_arr, m_length, m_arr); // move
    //     return *this;
    // }

    void insertBefore(int index, int value)
    {
        assert(index >= 0 && index < m_length);

        int *data{new int[static_cast<std::size_t>(m_length + 1)]};
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

        int *data{new int[static_cast<std::size_t>(m_length - 1)]};
        std::copy_n(m_arr,index,data); // the first half  (P.S. move will be faster than copy)
        std::copy_n(m_arr + index + 1, m_length - index - 1, data + index); // the second half
        delete[] m_arr;
        m_arr = data;
        --m_length;
    }

    ~IntArray()
    {
        delete[] m_arr;
    }

    friend std::ostream &operator<<(std::ostream &out, const IntArray &array)
    {
        for (int i{0}; i < array.m_length ; ++i)
        {
            out << array[i] << ' ';
        }
        return out;
    }

    // Note: we need block shallow copy here to avoid issue that ptr dangling caused.
    // At this point, both the temporary IntArray's m_arr and array->m_arr point to the same address (due to the shallow copy).
    // when assignment statment ends, array->m_arr will be dangling
    IntArray(const IntArray &other) = delete; // block the shallow copy
    IntArray &operator=(const IntArray &other) = delete; // block the shallow copy assignment
    

};

#endif
