// source file: prog/fn.s1
import 'package:script1/script1.dart';
void main() {
num inc([x])                                       // (1) 
{                                                  // (1) 
    return (x+1);                                  // (1) 
}                                                  // (1) 
dynamic add=([x,y])=>(x+y);                        // (3) 
log('inc(2)=',inc(2));                             // (5) 
log('add(2,3)=',add(2,3));                         // (6) 
}
