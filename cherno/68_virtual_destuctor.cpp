#include <iostream>

class Base{
    public:
        Base() {std::cout << "Base Constructor\n";}
        virtual ~Base() {std::cout << "Base Destructor\n";}
};

class Derived: public Base{
    public:
        Derived() {m_Array = new int[5]; std::cout << "Derived Constructor\n";}
        ~Derived() {delete[] m_Array; std::cout << "Derived Destructor\n";}
    private:
        int* m_Array;
};

int main() {
    Base * base = new Base();
    delete base;
    std::cout << "-----------------\n";
    Derived* derived = new Derived();
    delete derived;

    // example for virtual destructor
    std::cout << "-----------------\n";
    Base* poly = new Derived();
    delete poly;

    // std::cout << "Hello Easy C++ project!" << std::endl;
}