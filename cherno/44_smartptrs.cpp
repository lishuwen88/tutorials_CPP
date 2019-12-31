#include <iostream>
#include <string>
#include <memory>

class Entity{
    public:
        Entity(){
            std::cout << "Created Entity!" << std::endl;
        }

        ~Entity(){
            std::cout << "Destroyed Entity!" << std::endl;
        }

        void Print(){}
};


int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;
    {
        // demo unique pointer
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();

        std::shared_ptr<Entity> entityshared = std::make_shared<Entity>();


        entity->Print();
        entityshared->Print();
    }

    std::cout << "DONE!!!" << std::endl;
    // std::cin.get();
}