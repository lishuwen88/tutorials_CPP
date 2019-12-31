#include <iostream>

struct Entity{
    int x,y;
};

struct Vector2{
    float x,y;
};

struct Vector4{
    union{
        struct{
            float x,y,z,w;
        };
        struct{
            Vector2 a,b;
        };
    };
    
};

void PrintVector2(const Vector2& vector){
    std::cout << vector.x << "," << vector.y << std::endl;
}



int main() {

    int a  = 50;
    double value = *(double*)&a;
    std::cout << value << std::endl;

    Entity e ={5,8};
    int* position = (int*)&e;
    std::cout << position[0] << "," << position[1] << std::endl;

    int y = *(int*)((char*)&e + 4);
    std::cout << y << std::endl;

    struct Union{
        union{
            float a;
            int b;
        };
    };
    Union u;
    u.a = 2.0f;
    std::cout << u.a << "," << u.b << std::endl;
    
    Vector4 vector = {1.0f, 2.0f, 3.0f, 4.0f};
    PrintVector2(vector.a);
    PrintVector2(vector.b);
    vector.z = 500.f;
    std::cout << "---------------------" << std::endl;
    PrintVector2(vector.a);
    PrintVector2(vector.b);

    // implicit casting
    int a = 5;
    double value = a;

    // explicit casting, c-style cast
    int a = (int)value;

    // c++ style
    double s = static_cast<int>(value) +5.34;

}