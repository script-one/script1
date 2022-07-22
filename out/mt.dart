// source file: prog/mt.s1
import '../sys/s1.dart';
void main() {
dynamic e2c={'dog':'狗','cat':'貓','a':'一隻','the':'這隻','chase':'追','bite':'吃'}; // (1) 
List translate([ewords])                           // (3) 
{                                                  // (3) 
    dynamic cwords=[];                             // (4) 
    for (var e in ewords)                          // (5) 
    {                                              // (5) 
        cwords=push(cwords,e2c[e]);                // (6) 
    };                                             // (5) 
                                                   // (5) 
    return cwords;                                 // (8) 
}                                                  // (3) 
dynamic c=translate(['a','dog','chase','a','cat']); // (11) 
log(c);                                            // (12) 
}
