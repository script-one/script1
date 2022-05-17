// source file: prog/hello.s1
import '../sys/s1.js'

let name=`script1`;                                // (1) 
log((`hello `+name));                              // (2) 
if (typeof main == 'function') main()
