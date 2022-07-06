#include <iostream>
using namespace std;

class Person {
   public:
    int age;
    string name;

    string str() {
        return "name="+name+" age="+std::to_string(age);
    }
};

int main() {
    Person ccc;
    ccc.age = 52;
    ccc.name = "ccc";
    cout << ccc.str();
    return 0;
}