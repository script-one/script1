#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <any>
#include <variant>
#include <sstream>
#include <algorithm>
#include <functional>
#include <typeinfo>
using namespace std;

// typedef variant<string> obj;
// typedef string obj;

int main() {
    vector<variant<string, double>> a= {"hello", 3.14159};
    cout << typeid(a[0]).name() << '\n';
    if (typeid(a[0]) == typeid(std::string))
        cout << "a[0] is string" << '\n';
    double x;
    cout << typeid(x).name() << '\n';
    if (typeid(x) == typeid(double))
        cout << "x is double" << '\n';
    any y = "hello";
    cout << typeid(y).name() << '\n';
    auto z = "hello"s;
    cout << typeid(z).name() << '\n';
    // string x = a[0].str();
    // cout << x << '\n';
    // cout << a[0] << "\n";
    // auto k = 3.14159;
    variant<string, double> k = 3.14159;
    stringstream ss;  
    ss<<k;
    string s;  
    ss>>s;
    cout << "s=" << s << '\n';   
}