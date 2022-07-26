// source file: prog/for.s1
#include <s1.cpp>
int main() {
auto a={5,4,3,2,1};                                // (1) 
for (auto o:a) log(o);                             // (3) 
                                                   // (3) 
for (auto i:range(1,10,2)) log(i);                 // (5) 
                                                   // (5) 
for (auto i:range(1,10))                           // (7) 
{                                                  // (7) 
    if (i==2)continue;                             // (8) 
                                                   // (8) 
    log(i);                                        // (9) 
    if (i==5)break;                                // (10) 
                                                   // (10) 
}                                                  // (7) 
                                                   // (7) 
}
