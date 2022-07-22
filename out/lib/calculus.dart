// source file: prog/lib/calculus.s1
import '../../sys/s1.dart';

dynamic df([f,x,h=0.001])                          // (3) 
{                                                  // (3) 
  dynamic dy=(f((x+h))-f(x));                      // (4) 
  return (dy/h);                                   // (5) 
}                                                  // (3) 
dynamic integral([f,a,b,h=0.001])                  // (9) 
{                                                  // (9) 
  dynamic area=0.0;                                // (10) 
  for (var x in range(a,b,h))                      // (11) 
  {                                                // (11) 
    area=(area+(f(x)*h));                          // (12) 
  };                                               // (11) 
                                                   // (11) 
  return area;                                     // (14) 
}                                                  // (9) 

