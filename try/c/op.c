#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define i32(f) (int32_t)floor(f)

int main() {
    double a = 10; double b = 3.14159;
    printf("!a=%d\n", !a);
    printf("-a=%d\n", -a);
    printf("~a=0x%x\n", ~i32(a));
    printf("a+b=%lf\n", a+b);
    printf("a-b=%lf\n", a-b);
    printf("b-a=%lf\n", b-a);
    printf("a*b=%lf\n", a*b);
    printf("a/b=%lf\n", a/b);
    printf("a%%b=%d\n", i32(a)%i32(b));
    printf("a&&b=%d\n", a&&b);
    printf("a||b=%d\n", a||b);
    printf("a&b=%d\n",  i32(a)&i32(b));
    printf("a|b=%d\n",  i32(a)|i32(b));
    printf("a^b=%d\n",  i32(a)^i32(b));
    printf("b<<3=%d\n",  i32(b)<<3);
    printf("a>>3=%d\n",  i32(a)>>3);
    printf("a==b=%d\n",  a==b);
    printf("a!=b=%d\n",  a!=b);
    printf("a<=b=%d\n",  a<=b);
    printf("a>=b=%d\n",  a>=b);
    printf("a<b=%d\n",  a<b);
    printf("a>b=%d\n",  a>b);
}
