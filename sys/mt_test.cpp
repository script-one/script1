// source file: prog/mt_t.s1
#include <s1.cpp>

map<string,string> e2c={{"dog","狗"},{"cat","貓"},{"a","一隻"},{"the","這隻"},{"chase","追"},{"bite","吃"}}; // (1) 
auto translate(vector<string> ewords={})           // (3) 
{                                                  // (3) 
    vector<string> cwords={};                      // (4) 
    for (auto e:ewords)                            // (5) 
    {                                              // (5) 
        push(cwords,e2c[e]);                // (6) 
    };                                             // (5) 
                                                   // (5) 
    return cwords;                                 // (8) 
}                                                  // (3) 
int main()                                         // (11) 
{                                                  // (11) 
    auto c=translate({"a","dog","chase","a","cat"}); // (12) 
    log(join<string>(c, ","));                                   // (13) 
}       