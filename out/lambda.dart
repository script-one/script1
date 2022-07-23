// source file: prog/lambda.s1
import 'package:script1/script1.dart';
void main() {
dynamic inc([x])                                   // (1) 
{                                                  // (1) 
    return (x+1);                                  // (1) 
}                                                  // (1) 
dynamic a=[1,2,3];                                 // (3) 
dynamic b=map(a,([x])=>(x*x));                     // (4) 
dynamic c=map(a,inc);                              // (5) 
log('a=',a);                                       // (7) 
log('b=',b);                                       // (8) 
log('c=',c);                                       // (9) 
}
