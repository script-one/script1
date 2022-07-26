// source file: prog/fn.s1
#include <s1.cpp>
int main() {
num inc( x)                                        // (1) 
{                                                  // (1) 
    return (x+1);                                  // (1) 
}                                                  // (1) 
auto add=( x, y)=>(x+y);                           // (3) 
log("inc(2)=",inc(2));                             // (5) 
log("add(2,3)=",add(2,3));                         // (6) 
}
