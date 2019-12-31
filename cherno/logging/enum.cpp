#include <iostream>

enum Example : unsigned char
{
    A = 5, B, C

};

void runEnum()
{
    std::cout << "Enum Output" << std::endl;

    Example value = B;
    if (value ==6)
        {
            std::cout << "Its equal" << std::endl;
        }
    else
    {
        std::cout << "Not Equal" << std::endl;
    }

    // std::cin.get();
    
}