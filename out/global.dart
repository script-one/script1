// source file: prog/global.s1
import '../sys/s1.dart';
void main() {
log('hello 你好!');                              // (1) 
dynamic x=3;                                       // (3) 
global['x']=5;                                     // (5) 
log('x=',x);                                       // (7) 
log('@x=',global['x']);                            // (8) 
}
