// source file: prog/if.s1
import 'package:script1/script1.dart';
void main() {
num max([x,y])                                     // (1) 
{                                                  // (1) 
    return (x>y)?x:y;                              // (1) 
}                                                  // (1) 
dynamic min=([x,y])=>(x<y)?x:y;                    // (2) 
log('max(3,5)=',max(3,5));                         // (4) 
log('min(3,5)=',min(3,5));                         // (5) 
}
