#include <iostream>
#include <string>

class Entity
{
public:
    void Print() const { std::cout << "Hello!" << std::endl;}
};

class ScopedPtr
{
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity* entity)
        : m_Obj(entity)
        {}
    
    ~ScopedPtr()
    {
        delete m_Obj;
    }

    Entity* operator->()
    {
        return m_Obj;
    }
};

struct Vector3
{
    float x,y,z;
};

int main() {
    // Entity e;
    // e.Print();

    // Entity* ptr = &e;
    // // Entity& entity = *ptr;
    // ptr->Print();

    // ScopedPtr entity = new Entity();
    // entity-> Print();

    int offset = (int)&((Vector3*)nullptr)->x;
    std::cout << offset << std::endl;
}