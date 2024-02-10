#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(string name) {
        m_name = name;
    }
    virtual ~Animal() {}
    string name() const {
        return m_name;
    }
    virtual void speak() const = 0;
    virtual string moveAction() const = 0;
private:
    string m_name;
};

struct Cat : public Animal {
    Cat(string name)
    : Animal(name) {}
    virtual ~Cat() {
        cout << "Destroying " << name() << " " << "the cat" << endl;
    }
    virtual void speak() const {
        cout << "Meow";
    }
    virtual string moveAction() const {
        return "walk";
    }
};

class Pig : public Animal {
public:
    Pig(string name, int weight)
    : Animal(name), m_weight(weight) {}
    virtual ~Pig() {
        cout << "Destroying " << name() << " " << "the pig" << endl;
    }
    virtual void speak() const {
        if(m_weight < 180) cout << "Oink";
        else cout << "Grunt";
    }
    virtual string moveAction() const {
        return "walk";
    }
private:
    int m_weight;
};

struct Duck : public Animal {
    Duck(string name)
    : Animal(name) {}
    virtual ~Duck() {
        cout << "Destroying " << name() << " " << "the duck" << endl;
    }
    virtual void speak() const {
        cout << "Quack";
    }
    virtual string moveAction() const {
        return "swim";
    }
};
