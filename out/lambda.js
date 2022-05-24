// source file: prog/lambda.s1
import '../sys/s1.js'

let a=[1,2,3];                                     // (1) 
let b=map(a,function (x) { return (x*x) } );       // (2) 
log((`b=`+b));                                     // (4) 
if (typeof main == 'function') main()
