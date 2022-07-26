// source file: prog/sum_t.s1
#include <s1.cpp>

int sum(int n)                                     // (1) 
{                                                  // (1) 
    auto s=0;                                      // (2) 
    for (auto i:range(1,(n+1))) s=(s+i);           // (3) 
                                                   // (3) 
    return s;                                      // (4) 
}                                                  // (1) 
int main()                                         // (7) 
{                                                  // (7) 
    log("sum(10)=",str(sum(10)));                  // (8) 
}                                                  // (7) 

