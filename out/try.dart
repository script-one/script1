// source file: prog/try.s1
import 'package:script1/script1.dart';
void main() {
try                                                // (1) 
{                                                  // (1) 
    throw error('Error');                          // (2) 
}                                                  // (1) 
 catch (e)                                         // (3) 
{                                                  // (3) 
    log(e);                                        // (4) 
}                                                  // (3) 
                                                   // (1) 
}
