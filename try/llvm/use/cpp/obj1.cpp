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

int main() {
    Person ccc;
    ccc.age = 52;
    ccc.name = "ccc";
    ccc.print();
    return 0;
}