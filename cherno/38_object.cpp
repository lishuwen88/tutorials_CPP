#include <iostream>
#include <string>

using String = std::string;

class Entity
{
    private:
        String m_Name;
        int m_Age;
    public:
        Entity() : m_Name("Unknown"){}
        Entity(const String& name) : m_Name(name) {}

        const String& GetName() const { return m_Name;}
};

int main() {
    Entity entity("JOHNNY DA MAN");  // create object on stack
    std::cout << entity.GetName() << std::endl;

    // create Entity obj on heap with "new", 
    // and return Entity pointer to location, named eptr
    Entity* eptr = new Entity("John Pointer");  
    std::cout << entity.GetName() << std::endl;

    delete eptr;

    int a = 2;  // on the stack
    int* b = new int;   // 4b on the heap, gives a int ptr
    int* c = new int[50];   // 200b on heap, an array

    // std::cin.get();
}