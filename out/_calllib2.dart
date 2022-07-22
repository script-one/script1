// source file: prog/_calllib2.s1
import '../sys/s1.dart';

import './lib/random.dart' as R;                   // (1) 
import './lib/guid.dart' as G;                     // (2) 
dynamic main()                                     // (4) 
{                                                  // (4) 
  log('rUnif(5,10)=',R.rUnif(5,10));               // (5) 
  log('rInt()=',R.rInt(10,20));                    // (6) 
  log('rChoose([a,b,c])=',R.rChoose(['a','b','c'])); // (7) 
  log('guid()=',G.guid());                         // (8) 
}                                                  // (4) 

