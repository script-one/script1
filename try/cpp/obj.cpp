#include <cstdio>

class Object {
public:
};

class Float {
public:
    double value;

    Float(double v) {
      value = v;
    }

    void operator=(const Float& arg)
    {
        value = arg.value;
    }

    // https://prepinsta.com/c-plus-plus-theory/binary-operator-overloading/
    Float operator+(Float& arg)
    {
        Float r(0);
        r.value = value + arg.value;
        return (r);
    } 
};

int main() {
    Float f1(3), f2(5);
    printf("f1.value=%f\n", f1.value);
    f1 = f2;
    printf("f1.value=%f\n", f1.value);
    Float f3(0);
    f3 = f1+f2;
    printf("f3.value=%f\n", f3.value);
}

