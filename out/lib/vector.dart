// source file: prog/lib/vector.s1
import 'package:script1/script1.dart';

dynamic map2([a,b,f])                              // (1) 
{                                                  // (1) 
    dynamic alen=len(a);                           // (2) 
    dynamic c=array(alen);                         // (3) 
    for (var i in range(0,alen))                   // (4) 
    {                                              // (4) 
        c[i]=f(a[i],b[i]);                         // (5) 
    };                                             // (4) 
                                                   // (4) 
    return c;                                      // (7) 
}                                                  // (1) 
dynamic dot([a,b])                                 // (10) 
{                                                  // (10) 
    dynamic alen=len(a);                           // (11) 
    dynamic r=0;                                   // (12) 
    for (var i in range(0,alen))                   // (13) 
    {                                              // (13) 
        r=(r+(a[i]*b[i]));                         // (14) 
    };                                             // (13) 
                                                   // (13) 
    return r;                                      // (16) 
}                                                  // (10) 
dynamic neg([a])                                   // (19) 
{                                                  // (19) 
    return map(a,([a])=>- a);                      // (20) 
}                                                  // (19) 
dynamic add([a,b])                                 // (23) 
{                                                  // (23) 
    return map2(a,b,([a,b])=>(a+b));               // (24) 
}                                                  // (23) 

