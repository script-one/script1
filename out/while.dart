// source file: prog/while.s1
import '../sys/s1.dart';
void main() {
int sum(n)                                         // (1) 
{                                                  // (1) 
  var i=1;                                         // (2) 
  var s=0;                                         // (3) 
  while (i<=n)                                     // (4) 
  {                                                // (4) 
    s=(s+i);                                       // (5) 
    i=(i+1);                                       // (6) 
  };                                               // (4) 
                                                   // (4) 
  return s;                                        // (8) 
}                                                  // (1) 
log('sum(10)=',sum(10));                           // (11) 
}
