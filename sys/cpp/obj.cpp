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
    enum { NONE, FLOAT, STRING, ARRAY, MAP } type;
    union {
        double f;
        string *pstr;
        vector<Obj*> *parray;
        map<string, Obj*> *pmap;
    };

    Obj() {
        type = NONE;
    }
/*
    Obj(const Obj &o) {
        this = &o;
    }
*/
    Obj(double f1) {
        type = FLOAT;
        f = f1;
    }

    Obj(string str1) {
        type = STRING;
        pstr = &str1;
    }

    Obj(vector<Obj*> *a1) {
        type = ARRAY;
        parray = a1;
    }
    
    Obj(map<string, Obj*> *m1) {
        type = MAP;
        pmap = m1;
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
            string s = *a.pstr+*b.pstr;
            return Obj(s);
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
        else if (o.type == ARRAY) {
            os << "[";
            vector<Obj*> *v = o.parray;
            int len = v->size();
            for (int i=0; i<len; i++) {
                Obj *o = (*v)[i];
                os << *o;
                if (i < len-1) os << ",";
            }
            os << "]";
        }
        else if (o.type == MAP) {
            os << "{";
            for(map<string,Obj*>::iterator i = o.pmap->begin(); i != o.pmap->end(); ++i)
            {
                string key = i->first;
                Obj* obj = i->second;
                os << key << ":" << *obj;
                if (next(i) != o.pmap->end()) os << ",";
            }
            os << "}";
        }
        else os << "(obj:type error)";
        return os;
    }

    ~Obj() {
        // 
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
    vector<Obj*> c = {&cat};
    auto x = Obj(&c);
    cout << "&c=" << &c << endl;
    cout << "x=" << x << endl;
    vector<Obj*> a1 = {&a, &dog, &x};
    a1.push_back(&cat);
    auto a1o = Obj(&a1);
    cout << a1o << endl;
    map<string, Obj*> m1 = {{"a", &a}, {"dog", &dog}, {"cat", &cat}};
    auto m1o = Obj(&m1);
    a1.push_back(&m1o);
    cout << a1o << endl;
    // cout << e.v[2] << endl;
    // e.v.push_back(oc);
    // cout << e.v[2] << endl;
    // Array e=Array{Obj("a"), "dog", "chase", "a", "cat"};
    // Map e2c={{"dog","狗"},{"cat","貓"},{"a","一隻"},{"the","這隻"},{"chase","追"},{"bite","吃"}}; // (1) 
}

int main() {
    obj_test();
    array_test();
}
