//
// Created by thorsten on 05.11.2025.
//
// header files are included by cpp files
// cpp files are compiled:
// (gcc snippets.cpp -o main.exe)
//

#include <iostream>
using namespace std;

// prototypes in header
class Entity;
void printEntityPtr(Entity* e);
void printEntityRef(Entity& e);
void printEntityCRef(const Entity& e);
void printEntityRValue(Entity&& e);

// type definitions in header
class Entity {
public:
    // Default Constructor
    Entity() {
        x = 0;
        y = 0;
    };

    Entity(int x, int y) : m_name("Entity") {
        this->x = x;
        this->y = y;    // -> operator for pointers
        (*this).y = y;  // dot operator for objects (dereferenced pointer)
    };

    int x;
    int y;

    string& getName() {return m_name;}
    // const Ref can only call const methods
    const string& getNameConst() const {return m_name;}

    const Entity& getEntity() const {
        const Entity& e = *this;
        return e;
    }

private:
    string m_name;
};

// implementations in cpp-file
// pass-by-value (copy)
void printEntity(Entity e) {
    cout << e.getName() << " (" << e.x << "," << e.y << ")" << endl;
}

// pass-by reference (pointer)
void printEntityPtr(Entity* e) {
    cout << e->getName() << " (" << e->x << "," << e->y << ")" << endl;
}

// pass-by-reference (takes an lvalue)
void printEntityRef(Entity& e) {
    cout << e.getName() << " (" << e.x << "," << e.y << ")" << endl;
}

// pass-by-reference (takes an lvalue or an rvalue as input)
void printEntityCPtr(const Entity& e) {
    cout << e.getNameConst() << " (" << e.x << "," << e.y << ")" << endl;
}

// pass-by-reference (takes an rvalue)
void printEntityRValue(Entity&& e) {
    cout << e.getName() << " (" << e.x << "," << e.y << ")" << endl;
}

// entry point in main.cpp
int main() {

    // object creation (instantiation)
    // ... on the Stack
    Entity e;
    Entity e1(void);
    Entity e2(1, 1);
    Entity e3 = Entity(2, 2);
    // ... on the Heap (raw pointers)
    Entity* e4 = new Entity;
    Entity* e5 = new Entity();  // Java style
    Entity* e6 = (Entity*)malloc(sizeof(Entity));  // raw pointer C-style
    const Entity* e7 = new Entity();
    // smart pointers
    std::unique_ptr<Entity> e8 = std::make_unique<Entity>();
    // lvalue-References
    Entity& e11 = Entity(3, 3);
    // const References
    const Entity& e12 = Entity(3, 3);
    // rvalue-References
    Entity&& e13 = Entity(3, 3);


    // call methods on objects / pointers
    e4->getName();
    e5->getName();
    e6->getName();
    cout << e7->getNameConst() << endl;


    // free memory, delete objects, call destructor
    // avoid memory leaks
    free(e4);  // does not call the destructor; always use delete
    //delete e4;
    delete e5;
    delete e6;
    delete e7;

    return 0;
}
