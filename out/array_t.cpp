// source file: prog/array_t.s1
#include <s1.cpp>

double mean(vector<double> a)                      // (1) 
{                                                  // (1) 
    auto s=0.0;                                    // (2) 
    for (auto x:a) s=(s+x);                        // (3) 
                                                   // (3) 
    return (s/len(a));                             // (4) 
}                                                  // (1) 
int main()                                         // (7) 
{                                                  // (7) 
    log("mean([1 2 3 4 5])=",str(mean({1.0,2,3,4,5}))); // (8) 
}                                                  // (7) 

