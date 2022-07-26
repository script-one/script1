#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <math.h>
#include <stdint.h>
using namespace std;

#define i32(f) (int32_t)floor(f)

class Array;

class Obj {
    public:
    enum { NONE, FLOAT, STRING, OBJECT } type;
    union {
        double f;
        string *pstr;
        Obj *pobj;
    };

    Obj() {
        type = NONE;
    }

    Obj(double f1) {
        type = FLOAT;
        f = f1;
    }

    Obj(string str1) {
        type = STRING;
        pstr = &str1;
    }

    Obj(Obj *pobj1) {
        type = OBJECT;
        pobj = pobj1;
    }
    
    // https://www.tutorialspoint.com/cplusplus/assignment_operators_overloading.htm
    void operator=(const Obj &b) { 
        type = b.type;
        if (type == FLOAT) f = b.f;
        if (type == STRING) pstr = b.pstr;
    }
    void operator=(const double &b) { 
        type = FLOAT;
        f = b;
    }
    void operator=(const string &b) { 
        type = STRING;
        *pstr = b;
    }
    // ref -- https://en.cppreference.com/w/cpp/language/operators
    // binary
    friend Obj operator+(Obj a, const Obj& b) {
        if (a.type == FLOAT && b.type == FLOAT) {
            a.f += b.f;
            return a;
        } else if (a.type == STRING && b.type == STRING) {
            return Obj(*a.pstr+*b.pstr);
        }
        return Obj();
    }
    friend Obj operator-(Obj a, const Obj& b) { a.f -= b.f; return a; }
    friend Obj operator*(Obj a, const Obj& b) { a.f *= b.f; return a; }
    friend Obj operator/(Obj a, const Obj& b) { a.f /= b.f; return a; }
    friend Obj operator%(Obj a, const Obj& b) { a.f = i32(a.f)%i32(b.f); return a; }
    friend Obj operator&(Obj a, const Obj b) { a.f = i32(a.f)&i32(b.f); return a; }
    friend Obj operator|(Obj a, const Obj b) { a.f = i32(a.f)|i32(b.f); return a; }
    friend Obj operator^(Obj a, const Obj b) { a.f = i32(a.f)^i32(b.f); return a; }
    friend Obj operator&&(Obj a, const Obj b) { a.f = i32(a.f)&&i32(b.f); return a; }
    friend Obj operator||(Obj a, const Obj b) { a.f = i32(a.f)||i32(b.f); return a; }
    friend Obj operator<(Obj &a, const Obj &b) { return Obj(a.f < b.f); }
    friend Obj operator>(Obj &a, const Obj &b) { return Obj(a.f > b.f); }
    friend Obj operator<=(Obj &a, const Obj &b) { return Obj(a.f <= b.f); }
    friend Obj operator>=(Obj &a, const Obj &b) { return Obj(a.f >= b.f); }
    friend Obj operator==(Obj &a, const Obj &b) { return Obj(a.f == b.f); }
    friend Obj operator!=(Obj &a, const Obj &b) { return Obj(a.f != b.f); }
    // uniary
    Obj operator-() { return Obj(-f); }
    Obj operator!() { return Obj(!f); }
    Obj operator~() { return Obj(~i32(f)); }

    friend ostream& operator<<(ostream& os, const Obj& o) {
        if (o.type == NONE) os << "(Obj:none)";
        else if (o.type == FLOAT) os << o.f;
        else if (o.type == STRING) os << *o.pstr;
        else if (o.type == OBJECT) os << "(Obj:pobj=" << o.pobj << ":" << *(o.pobj) << ")";
        else os << "(obj:type error)";
        return os;
    }

    ~Obj() {
        // 
    }
};

class Array : public Obj {
    public:
    vector<Obj> v; 

    Array():v() {
        type = OBJECT;
    }
    Array(initializer_list<Obj> a):v(a) {
        type = OBJECT;
        // copy(a.begin(), a.end(), *this);
    }

    friend ostream& operator<<(ostream& os, const Array& a) {
        auto v = a.v;
        int len = v.size();
        os << "[";
        for (int i=0; i<len; i++) {
            os << v[i];
            if (i < len-1) os << ",";
        }
        os << "]";
        return os;
    }
};

void obj_test() {
    // test
    Obj s("Hello");
    Obj a(5.0), b(2.0);
    cout << "s=" << s << endl;
    cout << "s+World=" << s+Obj("World") << endl;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "a+b=" << a+b << endl;
    cout << "a-b=" << a-b << endl;
    cout << "a*b=" << a*b << endl;
    cout << "a/b=" << a/b << endl;
    cout << "a%b=" << a%b << endl;
    cout << "a&b=" << (a&b) << endl;
    cout << "a|b=" << (a|b) << endl;
    cout << "a^b=" << (a^b) << endl;
    cout << "a&&b=" << (a&&b) << endl;
    cout << "a||b=" << (a||b) << endl;
    cout << "a<b=" << (a<b) << endl;
    cout << "a>b=" << (a>b) << endl;
    cout << "a<=b=" << (a<=b) << endl;
    cout << "a>=b=" << (a>=b) << endl;
    cout << "a==b=" << (a==b) << endl;
    cout << "a!=b=" << (a!=b) << endl;
    cout << "-a=" << (-a) << endl;
    cout << "!a=" << (!a) << endl;
    cout << "~a=" << (~a) << endl;
    cout << "a=" << (a) << endl;
    a = 3.14159;
    cout << "a=3.14159" << endl;
    cout << "a=" << (a) << endl;
    a = s;
    cout << "a=s" << endl;
    cout << "a=" << (a) << endl;
    a = "World";
    cout << "a=World" << endl;
    cout << "a=" << (a) << endl;
    cout << "s=" << (s) << endl;
    cout << "a+s=" << (a+s) << endl;
    cout << "b=" << (b) << endl;
    cout << "a+b=" << (a+b) << endl;
}

void array_test() {
    auto a=Obj("a"), dog=Obj("dog"), cat=Obj("cat");
    Array c = {cat};
    cout << c << endl;
    cout << "&c=" << &c << endl;
    Obj oc = Obj(&c);
    Array e = {a, dog, oc};
    // cout << e.v[2] << endl;
    e.v.push_back(oc);
    cout << e.v[2] << endl;
    // Array e=Array{Obj("a"), "dog", "chase", "a", "cat"};
    // Map e2c={{"dog","狗"},{"cat","貓"},{"a","一隻"},{"the","這隻"},{"chase","追"},{"bite","吃"}}; // (1) 
    cout << e << endl;
}

int main() {
    obj_test();
    array_test();
}
