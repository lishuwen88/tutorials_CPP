#include <iostream>
#include <vector>
#include <functional>
// #include <algorithm>

void HelloWorld(int a)
{
    std::cout << "Hello World! Value: " << a << std::endl;
}

void PrintValue(int value)
{
    std::cout << "Value: " << value << std::endl;
}

void ForEach(std::vector<int>& values, void(*func)(int))
{
    for (int value : values)
        func(value);
}

void ForEach2(std::vector<int>& values, const std::function<void(int)>& func)
{
    for (int value : values)
        func(value);
}

int main() {
    typedef void(*gugubird)(int);

    gugubird func1 = HelloWorld;
    func1(88);
    func1(99);

    int a = 5;

    std::vector<int> values = {1,2,3,4,5};
    ForEach(values, PrintValue);

    ForEach2(values, [a](int value) 
    {
         std::cout << "Lambda: " << value << std::endl; 
    });

    auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
    std::cout << *it << std::endl;

    // std::cout << "Hello Easy C++ project!" << std::endl;
}