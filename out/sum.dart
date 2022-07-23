// source file: prog/sum.s1
import 'package:script1/script1.dart';
void main() {
dynamic sum([n])                                   // (1) 
{                                                  // (1) 
    dynamic s=0;                                   // (2) 
    for (var i in range(1,(n+1))) s=(s+i);         // (3) 
                                                   // (3) 
    return s;                                      // (4) 
}                                                  // (1) 
log('sum(10)=',sum(10));                           // (7) 
}
