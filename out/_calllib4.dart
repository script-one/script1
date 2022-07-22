// source file: prog/_calllib4.s1
import '../sys/s1.dart';

import './lib/rnd.dart' as R;                      // (1) 
dynamic main()                                     // (3) 
{                                                  // (3) 
  log('rUnif(5,10)=',R.rUnif(5,10));               // (4) 
  log('rInt()=',R.rInt(10,20));                    // (6) 
}                                                  // (3) 

