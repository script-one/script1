// source file: prog/if.s1
import '../sys/s1.dart';
void main() {
var max=(x,y)=>(x>y)?x:y;                          // (1) 
var min=(x,y)=>(x<y)?x:y;                          // (2) 
log('max(3,5)=',max(3,5));                         // (4) 
log('min(3,5)=',min(3,5));                         // (5) 
}