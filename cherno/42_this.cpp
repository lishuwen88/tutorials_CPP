#include <iostream>
#include <string>

class Entity{
    public:
        int x,y;

        Entity(int x, int y){   // instead of usual init, use 'this'
            Entity* e = this;

            e->x = x;
            e->y = y;
        }

        Entity(int x, int y){   // instead of usual init, use 'this'
            this->x = x;
            this->y = y;
        }
};

int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;
}