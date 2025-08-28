#include <iostream>
#include <cassert>

class IntArray
{
private:
    int *m_arr{nullptr}; // int * xx is not only a pointer to a int value, but also it's the adress of the first int in the array
    int m_length{};

public:
    IntArray(const int length)
    :   m_length{length}
    {
        assert(m_length > 0 && "IntArray Length should be a Positive Integer!");
        m_arr = new int[m_length];
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

    // we need both of them to make sure the deep copy
    // will be implemented
    IntArray(const IntArray& other) //copy constructor (Deep copy) (new object created by copied a existed one)
    :   m_length{other.m_length}
    {
        // we don't need check self-copy here, because IntArray a{a} makes no any sense
        m_arr = new int[m_length];
        for (int i = 0; i < m_length; ++i)
        {
            m_arr[i] = other.m_arr[i];
        }
    }
    IntArray& operator= (const IntArray& other) // deep copy (copy assignment)
    {
        if(this == &other)
            return *this;

        delete[] m_arr;
        m_length = other.m_length;
        m_arr = new int[m_length];
        for (int i = 0; i < m_length; ++i)
        {
            m_arr[i] = other.m_arr[i];
        }
        return *this;
    }
    ~IntArray()
    {
        delete[] m_arr;
    }
    friend std::ostream &operator<<(std::ostream &out, const IntArray &array);
};

std::ostream &operator<<(std::ostream &out, const IntArray &array)
{
    for (int i{0}; i < array.m_length ; ++i)
    {
        out << array[i] << ' ';
    }
    return out;
}

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}
