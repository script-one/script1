// source file: prog/sum.s1
#include <s1.cpp>
int main() {
void sum( n)                                       // (1) 
{                                                  // (1) 
    auto s=0;                                      // (2) 
    for (auto i:range(1,(n+1))) s=(s+i);           // (3) 
                                                   // (3) 
    return s;                                      // (4) 
}                                                  // (1) 
log("sum(10)=",sum(10));                           // (7) 
}
