// source file: prog/lib/rnd.s1
import '../../sys/s1.dart';

double rUnif([min=0,max=1])                        // (1) 
{                                                  // (1) 
  return (min+(random()*(max-min)));               // (2) 
}                                                  // (1) 
int rInt([min,max])                                // (5) 
{                                                  // (5) 
  return floor(rUnif(min,max));                    // (6) 
}                                                  // (5) 
dynamic rChoose([a])                               // (9) 
{                                                  // (9) 
  return a[rInt(0,len(a))];                        // (10) 
}                                                  // (9) 

