// source file: prog/lib/obj.s1
import '../../sys/s1.dart';

dynamic copy([o])                                  // (1) 
{                                                  // (1) 
  return fromJson(toJson(o));                      // (2) 
}                                                  // (1) 

