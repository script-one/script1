// source file: prog/global.s1
import 'package:script1/script1.dart';
void main() {
log('hello 你好!');                              // (1) 
dynamic x=3;                                       // (3) 
glob['x']=5;                                       // (5) 
log('x=',x);                                       // (7) 
log('@x=',glob['x']);                              // (8) 
}
