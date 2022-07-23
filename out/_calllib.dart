// source file: prog/_calllib.s1
import 'package:script1/script1.dart';

import './lib/rnd.dart' as R;                      // (1) 
import './lib/file.dart' as F;                     // (2) 
import './lib/guid.dart' as G;                     // (3) 
import './lib/calculus.dart' as C;                 // (4) 
import './lib/vector.dart' as V;                   // (5) 
import './lib/obj.dart' as O;                      // (6) 
dynamic main() async                               // (8) 
{                                                  // (8) 
    log('rUnif(5,10)=',R.rUnif(5,10));             // (9) 
    await F.copyText('data/test.txt','data/test2.txt'); // (10) 
    log('rInt()=',R.rInt(10,20));                  // (11) 
    log('guid()=',G.guid());                       // (12) 
    log('diff(sin, PI/4)=',C.df(sin,(math.PI/4))); // (13) 
    log('dot([1,2,3], [1,1,1])=',V.dot([1,2,3],[1,1,1])); // (14) 
    dynamic obj={'name':'snoopy','age':3};         // (15) 
    dynamic obj2=O.copy(obj);                      // (16) 
    log('obj2=',obj2);                             // (17) 
}                                                  // (8) 

