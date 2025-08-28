#include <iostream>
#include <string>

class Storage;

class Display
{
private:
    bool m_displayIntFirst{};
public:
    explicit Display(bool displayIntFirst)
        : m_displayIntFirst{displayIntFirst}
    {}

    void displayStorage(const Storage &storage); // compiler needs to know what the Storage is
};

class Storage
{
private:
    int m_nValue{};
    double m_dValue{};
public:
    explicit Storage(int nValue, double dValue)
        : m_nValue{nValue}, m_dValue{dValue}
    {}
    // friend can access all members in this class
    friend void Display::displayStorage(const Storage &storage); // compiler needs to know Full context of class Display, so it should be front of this class
};

void Display::displayStorage(const Storage &storage)
{
    if(m_displayIntFirst)
        std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
    else
        std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}

int main()
{
    Storage s1{5, 6.7};
    Display display_mode{false};
    display_mode.displayStorage(s1);

    return 0;
}
