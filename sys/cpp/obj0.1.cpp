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

typedef enum { NONE, FLOAT, STRING, ARRAY, MAP } Type;

class Obj {
    public:
    Type type;
    union {
        double f;
        string *pstr;
        vector<Obj*> *parray;
        map<string, Obj*> *pmap;
    };

    Obj() { type = NONE; }
    Obj(double f1) { type = FLOAT; f = f1; }
    Obj(string str1) { type = STRING; pstr = &str1; }
    Obj(vector<Obj*> *a1) { type = ARRAY; parray = a1; }
    Obj(map<string, Obj*> *m1) { type = MAP; pmap = m1; }
    Obj(const Obj&) = default; // 使用預設的複製建構子
    Obj(Obj&&) = default; // 使用預設的移動建構子
    // Obj(Obj&&) = delete; // 禁止預設的移動建構子，這樣的話
    // return Obj(...), return xxx 就會被禁止使用，然後出現一大堆警告
    // 說 error: use of deleted function 'Obj::Obj(Obj&&)

    // uniary
    Obj operator-() const { return Obj(-f); }
    Obj operator!() const { return Obj(!f); }
    Obj operator~() const { return Obj(~i32(f)); }
    Obj& operator[](size_t i) {
        if (type == ARRAY && i < parray->size()) {
            return *(*parray)[i];
        } else {
            throw "Error: Obj[i] fail!"s;
        }
    }

    Obj& operator[](string key) {
        if (type == MAP) {
            auto it = pmap->find(key);  
            return *it->second;
        } else {
            throw "Error: Obj[key] fail!"s;
        }
    }

    // https://www.tutorialspoint.com/cplusplus/assignment_operators_overloading.htm
    void operator=(const Obj &b) { 
        type = b.type;
        if (type == FLOAT) f = b.f;
        else if (type == STRING) pstr = b.pstr;
        else if (type == ARRAY) parray = b.parray;
        else if (type == MAP) pmap = b.pmap;
        else throw "Error: Obj::= type not supported!";
    }
    void operator=(const double &b) { 
        type = FLOAT;
        f = b;
    }
    void operator=(const string &b) { 
        type = STRING;
        *pstr = b;
    }

    ~Obj() {
        // cout << "desctruct:" << *this << endl;
        cout << "desctruct obj:type=" << this->type << endl;
    }
};

// ref -- https://en.cppreference.com/w/cpp/language/operators
// Obj::binary operator
Obj operator+(Obj a, const Obj& b) {
    if (a.type == FLOAT && b.type == FLOAT) {
        a.f += b.f;
        return a;
    } else if (a.type == STRING && b.type == STRING) {
        string s = *a.pstr+*b.pstr;
        return s;
    }
    throw "Error: Obj a+b fail!"s;
}
Obj operator-(Obj a, const Obj& b) { a.f -= b.f; return a; }
Obj operator*(Obj a, const Obj& b) { a.f *= b.f; return a; }
Obj operator/(Obj a, const Obj& b) { a.f /= b.f; return a; }
Obj operator%(Obj a, const Obj& b) { a.f = i32(a.f)%i32(b.f); return a; }
Obj operator&(Obj a, const Obj b) { a.f = i32(a.f)&i32(b.f); return a; }
Obj operator|(Obj a, const Obj b) { a.f = i32(a.f)|i32(b.f); return a; }
Obj operator^(Obj a, const Obj b) { a.f = i32(a.f)^i32(b.f); return a; }
Obj operator&&(Obj a, const Obj b) { a.f = i32(a.f)&&i32(b.f); return a; }
Obj operator||(Obj a, const Obj b) { a.f = i32(a.f)||i32(b.f); return a; }
Obj operator<(Obj &a, const Obj &b) { return a.f < b.f; }
Obj operator>(Obj &a, const Obj &b) { return a.f > b.f; }
Obj operator<=(Obj &a, const Obj &b) { return a.f <= b.f; }
Obj operator>=(Obj &a, const Obj &b) { return a.f >= b.f; }
Obj operator==(Obj &a, const Obj &b) { return a.f == b.f; }
Obj operator!=(Obj &a, const Obj &b) { return a.f != b.f; }

// output
ostream& operator<<(ostream& os, const Obj& o) {
    if (o.type == NONE) os << "(Obj:none)";
    else if (o.type == FLOAT) os << o.f;
    else if (o.type == STRING) os << "\"" << *o.pstr << "\"";
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
            os << "\"" << key << "\"" << ":" << *obj;
            if (next(i) != o.pmap->end()) os << ",";
        }
        os << "}";
    }
    else os << "(obj:type error)";
    return os;
}

void op_test() {
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
    try {
        cout << "a+b=" << (a+b) << endl;
    } catch (string e) {
        cout << e << endl;
    };
}

static Obj a=Obj("a"), dog=Obj("dog"), cat=Obj("cat"), cat2=Obj(cat);

void json_test() {
    // auto a=Obj("a"), dog=Obj("dog"), cat=Obj("cat"), cat2=Obj(cat);
    cout << "a=" << a << '\n';
    vector<Obj*> c{{&cat}};
    auto x = Obj(&c);
    cout << "&c=" << &c << '\n';
    cout << "x=" << x << endl;
    /*
    vector<Obj*> a1 = {&a, &dog, &x};
    a1.push_back(&cat);
    a1.push_back(&cat2);
    auto a1o = Obj(&a1);
    cout << a1o << endl;
    map<string, Obj*> m1 = {{"a", &a}, {"dog", &dog}, {"cat", &cat}};
    auto m1o = Obj(&m1);
    a1.push_back(&m1o);
    cout << a1o << endl;
    cout << "m1[dog]=" << m1o["dog"] << endl;
    cout << "a1[2]=" << a1o[2] << endl;
    */
}
/*
void mt_test() {
    map<string, Obj*> e2c={{"a",&a},{"dog", &dog},{"cat", &cat}}; // ,,{"the","這隻"},{"chase","追"},{"bite","吃"}}};
    vector<string> ewords={ "a", "dog" };
    vector<string> cwords={};
    for (auto e:ewords)
    {
        auto c = e2c[e];
        cwords.push_back(*c->pstr);
        cout << c;
    }
}
*/
int main() {
    op_test();
    json_test();
    // mt_test();
}
