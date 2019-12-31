#include <iostream>

class Entity
{
public:
    float X, Y;

    Entity()    // Constructor
    {
        X = 0.0f;
        Y = 0.0f;
        std::cout << "Created Entity" << std::endl;
    }

    Entity(float x, float y)    // Overloaded Constructor
    {
        X = x;
        Y = y;
    }

    ~Entity()   // Destructor
    {
        std::cout << "Destroyed Entity" << std::endl;
    }

    // void Init()  // using constructor instead
    // {
    //     X = 0.0f;
    //     Y = 0.0f;
    // }

    void Print()
    {
        std::cout << X << "," << Y << std::endl;
    }

    void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }

    virtual std::string GetName() { return "Entity";}
};

class Player : public Entity    // Inherit from Entity class
{
private:
    std::string m_Name;
public:
    Player(const std::string& name)
        : m_Name(name) {}

    const char* Name;

    std::string GetName() override { return m_Name;}

    void PrintName()
        {
            std::cout << Name << std::endl;
        }
};

// Player::Player(/* args */)
// {
// }

// Player::~Player()
// {
// }

void Function()
{
    Entity e;
    // std::cout << e.X << std::endl;
    e.Print();
}

void PrintName(Entity* entity)
{
    std::cout << entity->GetName() << std::endl;
}

int main() {
    std::cout << "Working C++ project!" << std::endl;
    Function();

    // Player player1;
    // player1.Move(1,2);

    Entity* e = new Entity();
    PrintName(e);

    Player* p = new Player("John");
    PrintName(p);

    std::cin.get();
}