// source file: prog/global.s1
import '../sys/s1.js'

global.print('hello 你好!')                      // (1) 
let x=3                                            // (3) 
global.x=5                                         // (5) 
print('x=',x)                                      // (7) 
print('@x=',global.x)                              // (8) 

