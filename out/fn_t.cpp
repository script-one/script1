// source file: prog/fn_t.s1
#include <s1.cpp>

auto inc(int x)                                    // (1) 
{                                                  // (1) 
    return (x+1);                                  // (1) 
}                                                  // (1) 
auto add=[](double x,double y){ return (x+y); } ;  // (3) 
int main()                                         // (5) 
{                                                  // (5) 
    log("inc(2)=",str(inc(2)));                    // (6) 
    log("add(2,3)=",str(add(2,3)));                // (7) 
}                                                  // (5) 

