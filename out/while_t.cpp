// source file: prog/while_t.s1
#include <s1.cpp>

int sum(int n)                                     // (1) 
{                                                  // (1) 
    auto i=1;                                      // (2) 
    auto s=0;                                      // (3) 
    while (i<=n)                                   // (4) 
    {                                              // (4) 
        s=(s+i);                                   // (5) 
        i=(i+1);                                   // (6) 
    };                                             // (4) 
                                                   // (4) 
    return s;                                      // (8) 
}                                                  // (1) 
int main()                                         // (11) 
{                                                  // (11) 
    log("sum(10)=",str(sum(10)));                  // (12) 
}                                                  // (11) 

