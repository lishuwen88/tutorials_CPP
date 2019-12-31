#include <iostream>
#include <string>

int main() {
    int example[5];
    example[0] = 2;
    example[4] = 4;

    std::cout << example[0] << std::endl;
    std::cout << example << std::endl;

    const char* name = "John";
    std::string name3 = "john3"; 
    std::string namehello = std::string("John ") + "Hello!";
    bool contains = name3.find("on") != std::string::npos; // is-in func
    // name[2] = 'a';
    char name2[5] = {'J', 'o','h','n','2'};
    
    std::cout << name3 << std::endl;

    "John\0";


    std::cin.get();
}