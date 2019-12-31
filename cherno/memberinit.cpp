#include <iostream>

class Entity
{
private:
    std::string m_Name;
    int m_Score;
public:
    // Entity()
    // {
    //     m_Name = "Unknown";
    // }
    Entity()
        : m_Name("unKnown"), m_Score(0) // Member Initializer List
    {                                   // should be in order as defined above
    }

    Entity(const std::string& name, int score) //how to init 2 variables?
        : m_Name(name), m_Score(score)
    {
//        m_Name = name;
    }

    const std::string& GetName() const {return m_Name;}

    void GetFull()
    {
        std::cout << m_Name << m_Score << std::endl;
    }
};

int main() {
    Entity e0("John", 88);
    std::cout << e0.GetName() << std::endl;
    e0.GetFull();

    // Entity e1("John");
    // std::cout << e1.GetName() << std::endl;
}