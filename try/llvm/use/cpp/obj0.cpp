#include <iostream>
using namespace std;

class Person {
   public:
    int age;
    string name;

    void print() {
        cout << "name=" << name << " age=" << age;
    }
};