// source file: prog/lambda.s1
import '../sys/s1.dart';
void main() {
void inc(x)                                        // (1) 
{                                                  // (1) 
  return (x+1);                                    // (1) 
}                                                  // (1) 
var a=[1,2,3];                                     // (3) 
var b=map(a,(x)=>(x*x));                           // (4) 
var c=map(a,inc);                                  // (5) 
log('a=',a);                                       // (7) 
log('b=',b);                                       // (8) 
log('c=',c);                                       // (9) 
}
