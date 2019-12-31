#include <iostream>
#include <string>
#include <memory>
// #include <stdio.h>
#include <string.h>

class String
{
private:
    char* m_Buffer;
    unsigned int m_Size;
public:
    String(const char* string){
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer,string,m_Size);
        m_Buffer[m_Size] = 0;
    }

    // Copy Constructor for deep copy
    String(const String& other)
        : m_Size(other.m_Size)
    {
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    ~String(){
        delete[] m_Buffer;
    }

    char& operator[](unsigned int index)
    {
        return m_Buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.m_Buffer;
    return stream;
}

int main() {
    String string = "Johnny";
    String second = string;

    second[1] = 'a';

    std::cout << string<< std::endl;
    std::cout << second<< std::endl;


    std::cout << "DONE!!!" << std::endl;
    // std::cin.get();
}