#include <iostream>
#include <string>

class Printable
{
    public:
        virtual std::string GetClassName() = 0;
};

class Entity : public Printable
{
    public:
        virtual std::string GetName() {return "Entity";}
        std::string GetClassName() override {return "Entity";}
};

class Player : public Entity//, Printable    // Inherit from Entity class
{
    private:
        std::string m_Name;
    public:
        Player(const std::string& name)
            : m_Name(name) {}

        std::string GetName() override { return m_Name;}
        std::string GetClassName() override {return "Player";}

};

// Player::Player(/* args */)
// {
// }

// Player::~Player()
// {
// }

void PrintName(Entity* entity)
{
    std::cout << entity->GetName() << std::endl;
}

void Print(Printable* obj)
{
    std::cout << obj->GetClassName() << std::endl;
}

class A : public Printable{
    public:
        std::string GetClassName() override { return "A";}
};

int main() {

    Entity* e = new Entity();
    // PrintName(e);

    Player* p = new Player("John");
    // PrintName(p);

    Print(e);
    Print(p);

    A* a = new A();
    Print(a);

    // std::cin.get();
}