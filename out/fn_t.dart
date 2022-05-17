// source file: prog/fn_t.s1
import '../sys/s1.dart';

int inc(x) {                                       // (1) 
  return (x+1);                                    // (1) 
}                                                  // (1) 
double add(x,y) {                                  // (3) 
  return (x+y);                                    // (3) 
}                                                  // (3) 
void main() {                                      // (5) 
  log('inc(2)=${inc(2)}');                         // (6) 
  log('add(2.0,3.0)=${add(2.0,3.0)}');             // (7) 
}                                                  // (5) 

