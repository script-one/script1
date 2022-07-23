// source file: prog/lib/obj.s1
import 'package:script1/script1.dart';

dynamic copy([o])                                  // (1) 
{                                                  // (1) 
    return fromJson(toJson(o));                    // (2) 
}                                                  // (1) 

